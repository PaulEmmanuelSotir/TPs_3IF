#include <array>
#include <string>
#include <iostream>
#include <algorithm>

#include "Graph.h"
#include "Typed_main_binding.h"

namespace TP3
{
	//! structure validant le concept de ...
	struct hour_option
	{
		unsigned short value;

		static std::array<std::string, 1> get_option_tags() noexcept { return{ "-t" }; }
	};

	//! structure validant le concept de ...
	struct exclusion_option
	{
		static std::array<std::string, 1> get_option_tags() noexcept { return{ "-e" }; }
	};

	//! structure validant le concept de ...
	struct output_graph_file_option
	{
		std::string value;

		static std::array<std::string, 1> get_option_tags() noexcept { return{ "-g" }; }
	};

	//! structure validant le concept de ...
	struct input_log_file_option
	{
		std::string value;
	};

	using std::experimental::optional;

	void typed_main(optional<input_log_file_option> input_log,
					optional<hour_option> hour_opt,
					optional<exclusion_option> excl_opt,
					optional<output_graph_file_option> output_graph)
	{
		if (!input_log)
			throw std::invalid_argument("No input log file have been specified");

	//	Log_parser parser;

		if (hour_opt)
		{ /* enable hour option... */ }
	//		parser.enable_hour_filter(hour_opt->value);
		if (excl_opt)
		{ /* enable exclusion option... */ }
	//		parser.enable_exclusion();

		if (output_graph)
		{
			// Parse graph
			//		auto graph = parser.parse_graph(input_log->value);

			// Serialize graph...
		}
		else
		{
			// Parse log to obtain the URLs with their respective occurrence number (unordered_multimap)
			//		auto topdocs = parser.parse_toplist(input_log->value);

			// Sort the unordered multimap by URL occurrence number
			/*std::sort(std::begin(*topdocs), std::end(*topdocs), [](const std::pair<std::string, unsigned int>& a, const std::pair<std::string, unsigned int>& b)
			{
			return b.second < a.second;
			});*/

			// Display the URLs top 10
			//...
		}
	}
}

int main(int argc, char* argv[])
{
	auto main_binding = TP3::make_typed_main_binding(&TP3::typed_main);

	try
	{
		main_binding.exec(argc, argv);
	}
	catch (std::invalid_argument e) { std::cout << "ERROR: " << e.what() << std::endl; }
	catch (std::out_of_range e) { std::cout << "ERROR: " << e.what() << std::endl; }

	return EXIT_SUCCESS;
}

