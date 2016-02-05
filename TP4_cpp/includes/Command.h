/*********************************************************************************
									Command
									-------
*********************************************************************************/

#ifndef COMMAND_H
#define COMMAND_H

#include <tuple>
#include <string>
#include <unordered_set>

#include "Utils.h"

//! \namespace TP4
//! espace de nommage regroupant le code crée pour le TP4 de C++
namespace TP4
{
	//----------------------------------------- Enumération des types de commandes
	enum class command_type { ADD_SEGMENT, ADD_RECTANGLE, ADD_POLYGON, UNION, INTER, HIT, DELETE, MOVE, LIST, UNDO, REDO, LOAD, SAVE, CLEAR, ENABLE_ERROR_MESSAGES, DISABLE_ERROR_MESSAGES, EXIT };
	std::string underlying(command_type command);
	command_type overlying(const std::string& name);

	using name_t = std::string;
	using coord_t = int;
	using Point = std::pair<coord_t, coord_t>;

	template<typename String>
	inline coord_t move_str_to_coord_t(String&& str)
	{
		return std::stoi(static_cast<std::string&&>((str)));
	}
}

#endif // !COMMAND_H
