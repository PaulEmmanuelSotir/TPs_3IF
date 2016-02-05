/*********************************************************************************
									main.cpp
									--------
*********************************************************************************/

#include <functional>
#include <iostream>
#include <fstream>
#include <string>

#include <boost/config.hpp>
#include <boost/archive/archive_exception.hpp>

#include "Utils.h"
#include "Scene.h"
#include "Command.h"

namespace
{
	inline void check_size(const std::vector<std::string>& words, size_t arg_count, bool is_inequality = false, bool additionnal_condition = true)
	{
		if ((is_inequality ? (words.size() < arg_count + 1) : (words.size() != arg_count + 1)) || !additionnal_condition)
			throw std::invalid_argument("Wrong number of arguments");
	}
}

int main()
{
	using TP4::move_str_to_coord_t;

	TP4::Scene geometry_scene;
	std::string line;
	auto is_error_message_enabled = false;

	while (true)
	{
		std::cin.sync_with_stdio(false);
		std::getline(std::cin, line);
		auto words = TP4::split(line, ' ');

		if (words.size() > 0)
		{
			try
			{
				switch (TP4::overlying(words[0]))
				{
				case TP4::command_type::ADD_SEGMENT:
					check_size(words, 5U);
					geometry_scene.Add_segment(std::move(words[1]), { move_str_to_coord_t(words[2]), move_str_to_coord_t(words[3]) }, { move_str_to_coord_t(words[4]), move_str_to_coord_t(words[5]) });
					std::cout << "OK" << std::endl;
					break;
				case TP4::command_type::ADD_RECTANGLE:
					check_size(words, 5U);
					geometry_scene.Add_rectangle(std::move(words[1]), { move_str_to_coord_t(words[2]), move_str_to_coord_t(words[3]) }, { move_str_to_coord_t(words[4]), move_str_to_coord_t(words[5]) });
					std::cout << "OK" << std::endl;
					break;
				case TP4::command_type::ADD_POLYGON:
				{
					check_size(words, 1U + 2U * 3, true, ((words.size() - 2U) % 2U) == 0);
					std::vector<TP4::Point> points;
					for (size_t i = 2; i < words.size(); i += 2)
						points.emplace_back(move_str_to_coord_t(words[i]), move_str_to_coord_t(words[i + 1]));
					geometry_scene.Add_polygon(std::move(words[1]), points);
					std::cout << "OK" << std::endl;
					break;
				}
				case TP4::command_type::UNION:
				{
					check_size(words, TP4::Union_cmd::args_count + 1, true);
					std::unordered_set<TP4::name_t> shape_names;
					for (size_t i = 2; i < words.size(); ++i)
						if (!shape_names.insert(std::move(words[i])).second)
							throw std::invalid_argument("Can't create union from duplicate shapes");

					geometry_scene.Union(std::move(words[1]), shape_names);
					std::cout << "OK" << std::endl;
					break;
				}
				case TP4::command_type::INTER:
				{
					check_size(words, TP4::Inter_cmd::args_count + 1, true);
					std::unordered_set<TP4::name_t> shape_names;
					for (size_t i = 2; i < words.size(); ++i)
						if (!shape_names.insert(std::move(words[i])).second)
							throw std::invalid_argument("Can't create union from duplicate shapes");

					geometry_scene.Intersect(std::move(words[1]), shape_names);
					std::cout << "OK" << std::endl;
					break;
				}
				case TP4::command_type::HIT:
					check_size(words, 3U);
					if (geometry_scene.Is_point_contained_by({ move_str_to_coord_t(words[2]), move_str_to_coord_t(words[3]) }, std::move(words[1])))
						std::cout << "YES" << std::endl;
					else
						std::cout << "NO" << std::endl;
					break;
				case TP4::command_type::DELETE:
				{
					check_size(words, 1U, true);
					std::vector<TP4::name_t> shape_names;
					for (size_t i = 1; i < words.size(); ++i)
						shape_names.push_back(std::move(words[i]));
					geometry_scene.Delete(shape_names);
					std::cout << "OK" << std::endl;
					break;
				}
				case TP4::command_type::MOVE:
					check_size(words, TP4::Move_cmd::args_count);
					geometry_scene.Move_shape(std::move(words[1]), move_str_to_coord_t(words[2]), move_str_to_coord_t(words[3]));
					std::cout << "OK" << std::endl;
					break;
				case TP4::command_type::LIST:
				{
					check_size(words, TP4::List_cmd::args_count);
					geometry_scene.List();
					break;
				}
				case TP4::command_type::UNDO:
					check_size(words, TP4::Undo_cmd::args_count);
					geometry_scene.Undo();
					std::cout << "OK" << std::endl;
					break;
				case TP4::command_type::REDO:
					check_size(words, TP4::Redo_cmd::args_count);
					geometry_scene.Redo();
					std::cout << "OK" << std::endl;
					break;
				case TP4::command_type::LOAD:
				{
					check_size(words, TP4::Load_cmd::args_count);
					geometry_scene.Load(std::move(words[1]));
					std::cout << "OK" << std::endl;
					break;
				}
				case TP4::command_type::SAVE:
				{
					check_size(words, TP4::Save_cmd::args_count);
					geometry_scene.Save(std::move(words[1]));
					std::cout << "OK" << std::endl;
					break;
				}
				case TP4::command_type::CLEAR:
					check_size(words, TP4::Clear_cmd::args_count);
					geometry_scene.Clear();
					std::cout << "OK" << std::endl;
					break;
				case TP4::command_type::EXIT:
					check_size(words, TP4::Exit_cmd::args_count);
					return EXIT_SUCCESS;
				case TP4::command_type::ENABLE_ERROR_MESSAGES:
					is_error_message_enabled = true;
					std::cout << "OK" << std::endl;
					break;
				case TP4::command_type::DISABLE_ERROR_MESSAGES:
					is_error_message_enabled = false;
					std::cout << "OK" << std::endl;
					break;
				}
			}
			catch (const std::range_error&)
			{
				if (is_error_message_enabled)
					std::cout << "Error: Invalid command" << std::endl;
				else
					std::cout << "ERR" << std::endl;
			}
			catch (const std::logic_error& e)
			{
				if (is_error_message_enabled)
					std::cout << "Error: " << e.what() << std::endl;
				else
					std::cout << "ERR" << std::endl;
			}
			catch (const boost::archive::archive_exception& e)
			{
				if (is_error_message_enabled)
					std::cout << "Error during (de)serialization: " << e.what() << std::endl;
				else
					std::cout << "ERR" << std::endl;
			}
		}
	}
}
