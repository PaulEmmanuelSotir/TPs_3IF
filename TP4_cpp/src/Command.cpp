#include "Command.h"

#include <string>
#include <tuple>

namespace TP4
{
	namespace
	{
		using cmd_ut = std::underlying_type<command_type>::type;
		const std::string CMDS[] = { std::string("S"), std::string("R"), std::string("PC"), std::string("OR"), std::string("OI"), std::string("HIT"), std::string("DELETE"), std::string("MOVE"),
									 std::string("LIST"), std::string("UNDO"), std::string("REDO"), std::string("LOAD"), std::string("SAVE"), std::string("CLEAR"), std::string("EN_ERROR_MESS"),
									 std::string("DIS_ERROR_MESS"), std::string("BENCHMARK"), std::string("EXIT") };
	}

	std::string underlying(command_type command)
	{
		return CMDS[static_cast<cmd_ut>(command)];
	}

	command_type overlying(const std::string& name)
	{
		for (cmd_ut i = 0; i <= static_cast<cmd_ut>(command_type::EXIT); ++i)
			if (name == CMDS[i])
				return static_cast<command_type>(i);
		throw std::range_error("Given string out of 'cmd' enumeration range.");
	}
}
