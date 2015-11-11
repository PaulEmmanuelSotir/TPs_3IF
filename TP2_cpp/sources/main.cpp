/********************************************************************************************
										main.cpp
										--------
date                 : 10/2015
copyright            : (C) 2015 by B3311
********************************************************************************************/

//----------------------------------------------------------------------------------- INCLUDE
//--------------------------------------------------------------------------- Include syst�me
#include <iostream>
#include <string>
#include <type_traits>	// std::underlying_type
#include <limits>		// std::numeric_limits
#include <stdexcept>	// std::range_error

//------------------------------------------------------------------------- Include personnel
#include "capteur_event.h"
#include "capteur_stat.h"
#include "ville.h"

//------------------------------------------------------------------------------------ Usings
using namespace std::string_literals; // enables s-suffix for std::string literals

//----------------------------------------------------------------- Enum�ration des commandes
// Equivalent � 'enum class cmd : std::string {...};' (underlying type non int�gral)
enum class cmd { ADD, STATS_C, JAM_DH, STATS_D7, OPT, EXIT };
namespace { // Namespace anonyme permettant de rendre 'CMDS' et 'cmd_ut' locals
	using cmd_ut = std::underlying_type<cmd>::type;
	const std::string CMDS[] = { "ADD"s, "STATS_C"s, "JAM_DH"s, "STATS_D7"s, "OPT"s, "EXIT"s };
}
std::string underlying(cmd command) { return CMDS[static_cast<cmd_ut>(command)]; }
cmd overlying(const std::string& name) {
	for (cmd_ut i = 0; i <= static_cast<cmd_ut>(cmd::EXIT); ++i)
		if (name == CMDS[i])
			return static_cast<cmd>(i);
	throw std::range_error("Given string out of 'cmd' enumeration range.");
}

/// <summary> Trouve le premier mots d'une chaine de charact�res </summary>
/// <param name='str'> Chaine de charact�res </param>
/// <param name='begin_pos'> position � partir de la quelle faire la recherche </param>
/// <param name='sep'> Charact�re utilis� comme s�parateur entre les mots </param>
/// <returns> Le mots trouv� </returns>
static inline std::string find_first_word(const std::string &str, size_t begin_pos)
{
	size_t word_end_pos = str.find_first_of(" \n", begin_pos);
	return str.substr(begin_pos, word_end_pos - begin_pos);
}

static inline TP2::capteur_stat::sensor_t read_integer_from_buffer(const std::string& buffer, size_t& begin_pos)
{
	auto word = find_first_word(buffer, begin_pos);
	begin_pos += word.length() + 1;
	return static_cast<TP2::capteur_stat::sensor_t>(std::stoi(word));
}

static inline void next_buffer_word(const std::string& buffer, size_t& begin_pos)
{
	auto word = find_first_word(buffer, begin_pos);
	begin_pos += word.length() + 1;
}

/// <summary> Parse et execute la commande donn�e en entr�e </summary>
/// <param name='town'> Commande � executer </param>
/// <param name='command'> Commande � executer </param>
/// <returns> Un bool�en indiquant si la commande 'cmd::EXIT' a �t� re�ue </returns>
// TODO: v�rifier les entr�es (range)
#include <type_traits>	// 'std::declval()' et 'std::forward()'
#include <utility>		// std::declval
#include "utils.h"
static inline bool process_command(TP2::ville& town, const std::string& buffer, size_t begin_pos, size_t end_pos)
{
	// Determine la commande re�ue
	auto word = find_first_word(buffer, begin_pos);
	cmd command = overlying(word);
	begin_pos += word.length() + 1;

	switch (command)
	{
	case cmd::ADD:
	{
		// Id
		auto id = read_integer_from_buffer(buffer, begin_pos); // hour

		// Timestamp
		next_buffer_word(buffer, begin_pos); // year (ignored)
		next_buffer_word(buffer, begin_pos); // month (ignored)
		next_buffer_word(buffer, begin_pos); // day (ignored)
		auto hour = read_integer_from_buffer(buffer, begin_pos); // hour
		auto min = read_integer_from_buffer(buffer, begin_pos); // minute
		auto d7 = read_integer_from_buffer(buffer, begin_pos); // day of week

		// Traffic
		TP2::traffic state = static_cast<TP2::traffic>(buffer[begin_pos]);

		town.add_sensor(TP2::capteur_event(id, d7, hour, min, state));
	}
	break;
	case cmd::STATS_C:
	{
		auto id = read_integer_from_buffer(buffer, begin_pos); // Id

		auto sens = town.get_sensor_stat_by_id(id);
		if (sens != nullptr)
			sens->show_time_distribution();
	}
	break;
	case cmd::JAM_DH:
	{
		auto d7 = read_integer_from_buffer(buffer, begin_pos); // d7
		town.show_day_traffic_by_hour(d7);
	}
	break;
	case cmd::STATS_D7:
	{
		auto d7 = read_integer_from_buffer(buffer, begin_pos); // d7
		town.show_day_traffic(d7);
	}
	break;
	case cmd::OPT:
	{
		auto d7 = read_integer_from_buffer(buffer, begin_pos); // d7
		auto h_start = read_integer_from_buffer(buffer, begin_pos); // H start
		auto h_end = read_integer_from_buffer(buffer, begin_pos); // H end
		size_t seg_count = static_cast<size_t>(read_integer_from_buffer(buffer, begin_pos)); // Seg count

		// Segments/Capteurs IDs
		TP2::vec<TP2::capteur_stat::sensor_t> seg_ids(seg_count, seg_count);
		for (size_t i = 0; i < seg_count; ++i)
			seg_ids[i] = read_integer_from_buffer(buffer, begin_pos);

		town.show_optimal_timestamp(d7, h_start, h_end, seg_ids);
	}
		break;
	case cmd::EXIT:
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------- MAIN
int main()
{
	TP2::ville lyon;

	// Buffer contenant une partie de l'entr�e issue de stdin
	const size_t BUFFER_SIZE = 2*2*2*131072;
	std::string buffer(BUFFER_SIZE, ' ');

	// Positions de d�but et fin d'une commande dans le buffer
	size_t cmd_begin_pos = 0;
	size_t cmd_end_pos = 0;

	// Lit l'entr�e par blocks en utlisant stdin pour des raisons de performances
	size_t buffer_used_size = std::numeric_limits<size_t>::max();
	auto cut_cmd_beg = ""s; // String contenant le d�but des commandes � cheval entre deux buffers
	while (buffer_used_size >= BUFFER_SIZE)
	{
		// Lie une block issu de stdin
		buffer_used_size = fread(&buffer[0], sizeof(char), BUFFER_SIZE, stdin);

		// G�re le cas des commandes � cheval entre deux buffers
		if (cmd_end_pos == std::string::npos)
		{
			// Recompose la commande
			cmd_end_pos = buffer.find_first_of('\n', 0);
			cut_cmd_beg = cut_cmd_beg + buffer.substr(0, cmd_end_pos);

			// Parse et execute la commande
			if (process_command(lyon, cut_cmd_beg, 0, cut_cmd_beg.length()))
				return EXIT_SUCCESS; // Commande 'EXIT' re�ue

			cmd_begin_pos = cmd_end_pos + 1;
		}
		else
			cmd_begin_pos = 0;

		cmd_end_pos = 0;
		while (cmd_end_pos != std::string::npos && cmd_begin_pos < buffer_used_size)
		{
			// Determine la position de fin de la commande dans le buffer
			cmd_end_pos = buffer.find_first_of('\n', cmd_begin_pos);

			// Si la commande est enti�rement contenue dans le buffer...
			if (cmd_end_pos != std::string::npos)
			{
				// Parse et execute la commande
				if (process_command(lyon, buffer, cmd_begin_pos, cmd_end_pos))
					return EXIT_SUCCESS; // Commande 'EXIT' re�ue

				// Determine la position de d�but de la prochaine commande dans le buffer
				cmd_begin_pos = cmd_end_pos + 1;
			}
			else
				// On retient le d�but de la commande � cheval entre deux buffers
				cut_cmd_beg = buffer.substr(cmd_begin_pos, buffer_used_size - cmd_begin_pos);
		}
	}

	return EXIT_SUCCESS;
}
