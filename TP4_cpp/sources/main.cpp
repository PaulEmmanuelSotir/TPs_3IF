/*********************************************************************************
									main.cpp
									--------
*********************************************************************************/

#include <iostream>
#include <rectangle.h>
#include <string>

#include "Utils.h"

//----------------------------------------------------------------- Enumération des commandes
// Equivalent à 'enum class cmd : std::string {...};' (underlying type non intégral)
enum class cmd { ADD_SEGMENT, ADD_RECTANGLE, ADD_POLYGON, UNION, INTER, HIT, DELETE, MOVE, LIST, UNDO, REDO, LOAD, SAVE, CLEAR, EXIT };
namespace { // Namespace anonyme permettant de rendre 'CMDS' et 'cmd_ut' locals
	using cmd_ut = std::underlying_type<cmd>::type;
	const std::string CMDS[] = {	std::string("S"), std::string("R"), std::string("PC"), std::string("OR"), std::string("OI"), std::string("HIT"), std::string("DELETE"), std::string("MOVE"), 
									std::string("LIST"), std::string("UNDO"), std::string("REDO"), std::string("LOAD"), std::string("SAVE"), std::string("CLEAR") , std::string("EXIT") };
}
std::string underlying(cmd command) { return CMDS[static_cast<cmd_ut>(command)]; }
cmd overlying(const std::string& name) {
	for (cmd_ut i = 0; i <= static_cast<cmd_ut>(cmd::EXIT); ++i)
	{
		if (name == CMDS[i])
			return static_cast<cmd>(i);
	}
	throw std::range_error("Given string out of 'cmd' enumeration range.");
}

int main()
{
	while(true)
	{
		std::string line;
		std::getline(std::cin, line);

		auto words = TP4::split(line, ' ');

		if(words.size() > 0)
		{
			switch (overlying(words[0]))
			{
			case cmd::ADD_SEGMENT: break;
			case cmd::ADD_RECTANGLE: break;
			case cmd::ADD_POLYGON: break;
			case cmd::UNION: break;
			case cmd::INTER: break;
			case cmd::HIT: break;
			case cmd::DELETE: break;
			case cmd::MOVE: break;
			case cmd::LIST: break;
			case cmd::UNDO: break;
			case cmd::REDO: break;
			case cmd::LOAD: break;
			case cmd::SAVE: break;
			case cmd::CLEAR: break;
			case cmd::EXIT:
				return EXIT_SUCCESS;;
			default: break;
			}
		}
	}
}
