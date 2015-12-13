
#include <set>
#include <array>
#include <string>
#include <fstream>
#include <utility>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <unordered_map>

#include "Graph.h"
#include "Help_txt.h"
#include "Log_parser.h"
#include "Typed_main_binding.h"

namespace TP3
{
	//! structure validant le concept de ...
	struct input_log_file_option
	{ std::string value; };

	//! structure validant le concept de ...
	struct output_graph_file_option
	{
		std::string value;

		static std::array<std::string, 3> get_option_tags() noexcept { return{ "-g", "-G", "--graph" }; }
	};

	//! structure validant le concept de ...
	struct hour_option
	{
		unsigned short value;

		static std::array<std::string, 3> get_option_tags() noexcept { return{ "-t", "-T", "--hour" }; }
	};

	//! structure validant le concept de ...
	struct exclusion_option
	{ static std::array<std::string, 3> get_option_tags() noexcept { return{ "-e", "-E", "--excludeMedias" }; } };

	//! structure validant le concept de ...
	struct help_option
	{ static std::array<std::string, 2> get_option_tags() noexcept { return{ "-g", "--help" }; } };

	using std::experimental::optional;

	void serialize_graph(const std::string& output_filename,std::unique_ptr<Graph<std::string>> graph)
	{
		std::string line;
		std::ofstream outfile(output_filename, std::ios::trunc);

		if (!outfile.is_open())
			throw std::invalid_argument("Invalid output file path or don't have modification right");

		outfile << "digraph {" << std::endl;

		// Write nodes
		for (const auto& node : graph->get_nodes())
			outfile << "node" << node.second << " [label=\"" << node.first << "\"];" << std::endl;

		// Write links
		for (const auto& link : graph->get_links())
			outfile << "node" << link.first << " -> " << "node" << link.second.destination << " [label=\"" << link.second.occurrence << "\"];" << std::endl;

		outfile << "}" << std::endl;

		outfile.close();
	}

	void typed_main(optional<input_log_file_option> input_log,
					optional<output_graph_file_option> output_graph,
					optional<hour_option> hour_opt,
					optional<exclusion_option> excl_opt,
					optional<help_option> help)
	{
		// Tagless option are mandatory for now (see TP::make_typed_main_binding<...>) (no need for following commented lines)
		//if (!input_log)
		//	throw std::invalid_argument("No input log file have been specified");

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
				// Parse and serialize graph
				serialize_graph(output_graph->value, parser.parse_graph(input_log->value));
			else
			{
				// Parse log to obtain the URLs with their respective occurrence number (unordered_multimap)
				auto urls = parser.parse_toplist(input_log->value);

				// Get and display top 10 URLS from unordered multimap (partial sort by URL occurrence number)
				using url_score_t = std::pair<std::string, unsigned int>;
				std::vector<url_score_t> topten(std::min(static_cast<size_t>(10), urls->size()));
				std::partial_sort_copy(std::cbegin(*urls), std::cend(*urls), std::begin(topten), std::end(topten), [](const url_score_t& a, const url_score_t& b)
				{ return b.second < a.second; });

				// Display the URLs top 10
				for (const auto& score : topten)
					std::cout << '"' << score.first << "\" : " << score.second << std::endl;
			}
		}
		else
			std::cout << Help_txt();
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

