/*********************************************************************************
									main.cpp
									--------
date                 : 12/2015
copyright            : (C) 2015 by B3311
*********************************************************************************/

//----------------------------------------------------------------------- INCLUDES
//-------------------------------------------------------------- Includes systèmes
#include <array>
#include <string>
#include <fstream>
#include <utility>
#include <iterator>
#include <iostream>
#include <algorithm>

//------------------------------------------------------------ Includes personnels
#include "Graph.h"
#include "Help_txt.h"
#include "Log_parser.h"
#include "Typed_main_binding.h"

//! \namespace TP3
//! espace de nommage regroupant le code crée pour le TP3 de C++
namespace TP3
{
	//------------------------------------------------------------ COMMAND OPTIONS

	//! @remarks valide le concept de 'option_with_value'
	struct input_log_file_option
	{ std::string value; };

	//! @remarks valide le concept de 'option_with_tags' et 'option_with_value'
	struct output_graph_file_option
	{
		std::string value;
		static tags_t<3> get_option_tags() noexcept { return tags_t<3>{{ "-g", "-G", "--graph" }}; /* C++11/14: "return { "-g", "-G", "--graph" };" */ } 
	};

	//! @remarks valide le concept de 'option_with_tags' et 'option_with_value'
	struct hour_option
	{
		unsigned short value;
		static tags_t<3> get_option_tags() noexcept { return tags_t<3>{{ "-t", "-T", "--hour" }}; }
	};

	//! @remarks valide le concept de 'option_with_tags' et 'option_with_value'
	struct list_option
	{
		size_t value;
		static const size_t default_value = 10;
		static tags_t<3> get_option_tags() noexcept { return tags_t<3>{ { "-l", "-L", "--listCount" }}; }
	};

	//! @remarks valide le concept de 'option_with_tags'
	struct exclusion_option
	{ static tags_t<3> get_option_tags() noexcept { return tags_t<3>{ { "-e", "-E", "--excludeMedias"}}; } };

	//! @remarks valide le concept de 'option_with_tags'
	struct help_option
	{ static tags_t<1> get_option_tags() noexcept { return tags_t<1>{ { "-h" }}; } };

	using std::experimental::optional;

	//----------------------------------------------------------- STATIC FUNCTIONS

	//! "Main typé" appellé par un objet de type 'Typed_main_binding<Args...>'
	static void typed_main(optional<input_log_file_option> input_log, // input_log is actually mandatory (tagless option)
					optional<output_graph_file_option> output_graph,
					optional<hour_option> hour_opt,
					optional<list_option> list_count_opt,
					optional<exclusion_option> excl_opt,
					optional<help_option> help)
	{
		if (!help)
		{
			Log_parser parser;

			if (hour_opt)
			{
				if (hour_opt->value < 0 || hour_opt->value >= 24)
					throw std::out_of_range("Hour must be in [[0,23]]");
				parser.enable_hour_filter(hour_opt->value);
			}
			if (excl_opt)
				parser.enable_exclusion();

			if (output_graph)
			{
				// Parse and serialize graph
				serialize_graph(output_graph->value, parser.parse_graph(input_log->value));
				std::cout << "Dot-file " << output_graph->value << " generated." << std::endl;
			}
			else
			{
				// Parse log to obtain the URLs with their respective occurrence number (unordered_multimap)
				auto urls = parser.parse_urllist(input_log->value);

				// Determine URLs toplist size
				auto toplist_count = list_count_opt ? list_count_opt->value : list_option::default_value;
				if (toplist_count < 1)
					throw std::out_of_range("URLs toplist size must be greater than 0");

				// Get top URL listS from unordered multimap '*urls' (partial sort by URL occurrence number)
				using url_score_t = std::pair<std::string, unsigned int>;
				std::vector<url_score_t> topten(std::min(toplist_count, urls->size()));
				std::partial_sort_copy(std::begin(*urls), std::end(*urls), std::begin(topten), std::end(topten), [](const url_score_t& a, const url_score_t& b)
				{ return b.second < a.second; });

				// Display the URLs top 10
				for (const auto& score : topten)
					std::cout << '"' << score.first << "\" :\t" << score.second << " occurrences" << std::endl;
			}
		}
		else
			std::cout << Help_txt();
	}
}


//--------------------------------------------------------------------------- MAIN

//! Fonction main utilisant simplement un binding vers le main typé
int main(int argc, char* argv[])
{
	// On traite le cas où seul '-h' est spécifié à part car le binding considère le nom du fichier log comme obligatoire
	if (argc == 2)
		if (argv[1] == std::string("-h")/* C++14: "-h"s*/)
		{
			std::cout << TP3::Help_txt();
			return EXIT_SUCCESS;
		}

	auto main_binding = TP3::make_typed_main_binding(&TP3::typed_main);

	try
	{
		main_binding.exec(argc, argv);
	}
	catch (std::invalid_argument e) { std::cout << "ERROR: " << e.what() << std::endl; }
	catch (std::out_of_range e) { std::cout << "ERROR: " << e.what() << std::endl; }

	return EXIT_SUCCESS;
}

