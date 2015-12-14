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
		static tags_t<3> get_option_tags() noexcept { return tags_t<3>{{ "-g", "-G", "--graph" }}; } // pour les versions plus récentes de gcc on peut ecrire simplement "return { "-g", "-G", "--graph" };"
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
	{ static tags_t<2> get_option_tags() noexcept { return tags_t<2>{ { "-g", "--help" }}; } };

	using std::experimental::optional;

	//----------------------------------------------------------- STATIC FUNCTIONS

	//! Fonction créant un fichier GraphViz à partir d'un objet de type Graph<std::string>
	static void serialize_graph(const std::string& output_filename, std::unique_ptr<Graph<std::string>> graph)
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
	auto main_binding = TP3::make_typed_main_binding(&TP3::typed_main);

	try
	{
		main_binding.exec(argc, argv);
	}
	catch (std::invalid_argument e) { std::cout << "ERROR: " << e.what() << std::endl; }
	catch (std::out_of_range e) { std::cout << "ERROR: " << e.what() << std::endl; }

	return EXIT_SUCCESS;
}

