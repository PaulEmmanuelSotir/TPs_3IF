/*********************************************************************************
									Command
									-------
*********************************************************************************/

#ifndef COMMAND_H
#define COMMAND_H

#include <tuple>
#include <string>
#include <vector>
#include <memory>
#include <unordered_set>

#include "Utils.h"

//! \namespace TP4
//! espace de nommage regroupant le code cr�e pour le TP4 de C++
namespace TP4
{
	//----------------------------------------- Enum�ration des types de commandes
	enum class command_type { ADD_SEGMENT, ADD_RECTANGLE, ADD_POLYGON, UNION, INTER, HIT, DELETE, MOVE, LIST, UNDO, REDO, LOAD, SAVE, CLEAR, EXIT };
	std::string underlying(command_type command);
	command_type overlying(const std::string& name);


	//! Classe abstraite repr�sentant une commande (permet le polymorphisme sur n'importe quel type de commandes)
	class Command
	{
	public:
		virtual ~Command() = 0;
	};
	inline Command::~Command() = default; // Un destructeur virtuel pur doit quand m�me avoir une impl�mentation

	//! Classe template
	template<command_type type, typename... Args>
	class Command_spec : public Command
	{
	public:
		explicit Command_spec(Args... arguments);
		~Command_spec() override = default;

		static const size_t args_count = sizeof...(Args);
		static const command_type command_type = type;
	private:
		std::tuple<Args...> m_command_arguments;
	};

	template<command_type type, typename... Args>
	Command_spec<type, Args...>::Command_spec(Args... arguments)
		: m_command_arguments(std::make_tuple(arguments...))
	{ }

	using name_t = std::string;
	using coord_t = int;

	template<typename String>
	inline coord_t move_str_to_coord_t(String&& str)
	{
		return std::stoi(static_cast<std::string&&>((str)));
	}

	//! Type de la commande correspondant � ADD_SEGMENT
	using Add_segment_cmd = Command_spec<command_type::ADD_SEGMENT, name_t, Point, Point>;
	//! Type de la commande correspondant � ADD_RECTANGLE
	using Add_rectangle_cmd = Command_spec<command_type::ADD_RECTANGLE, name_t, Point, Point>;
	//! Type de la commande correspondant � ADD_POLYGON
	using Add_polygon_cmd = Command_spec<command_type::ADD_POLYGON, name_t, std::vector<Point>>;
	//! Type de la commande correspondant � INTER
	using Inter_cmd = Command_spec<command_type::INTER, name_t, std::unordered_set<name_t>>;
	//! Type de la commande correspondant � UNION
	using Union_cmd = Command_spec<command_type::UNION, name_t, std::unordered_set<name_t>>;
	//! Type de la commande correspondant � HIT
	using Hit_cmd = Command_spec<command_type::HIT, name_t, Point>;
	//! Type de la commande correspondant � DELETE
	using Delete_cmd = Command_spec<command_type::DELETE, std::vector<name_t>>;
	//! Type de la commande correspondant � MOVE
	using Move_cmd = Command_spec<command_type::MOVE, name_t, coord_t, coord_t>;
	//! Type de la commande correspondant � LIST
	using List_cmd = Command_spec<command_type::LIST>;
	//! Type de la commande correspondant � UNDO
	using Undo_cmd = Command_spec<command_type::UNDO>;
	//! Type de la commande correspondant � REDO
	using Redo_cmd = Command_spec<command_type::REDO>;
	//! Type de la commande correspondant � LOAD
	using Load_cmd = Command_spec<command_type::LOAD, name_t>;
	//! Type de la commande correspondant � SAVE
	using Save_cmd = Command_spec<command_type::SAVE, name_t>;
	//! Type de la commande correspondant � CLEAR
	using Clear_cmd = Command_spec<command_type::CLEAR>;
	//! Type de la commande correspondant � EXIT
	using Exit_cmd = Command_spec<command_type::EXIT>;
}

#endif // COMMAND_H
