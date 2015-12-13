/*********************************************************************************
						Log_parser  - An apache log parser
						----------------------------------
date                 : 12/2015
copyright            : (C) 2015 by B3311
*********************************************************************************/

//-------------------- Implémentation de la classe Log_parser --------------------

//-------------------------------------------------------------- Includes systèmes
#include <array>
#include <regex>
#include <string>
#include <memory>
#include <utility>
#include <fstream>
#include <iterator>
#include "optional.h"

//------------------------------------------------------------ Includes personnels
#include "Log_parser.h"
#include "Graph.h"
#include "Utils.h"

namespace TP3
{
	//------------------------------------------------------------------- STATIQUE
	//------------------------------------------------------------ Regex statiques

	//! Extentions to ignored if media exclusion filter is enabled
	static const std::string EXCLUDED_EXTENTIONS = "js|css|png|ogg|jpg|jpeg|bmp|raw|tiff|gif|ppm|pgm|pbm|pnm|webp|heif|bpgcd5|deep|ecw|fits|fits|flif|ILBM|IMG|Nrrd|PAM|PCX|PGF|PLBM|SGI|SID|TGA|VICAR";

	//! Regex matching an IP (ipv4 or ipv6)
	static const std::string IP_REGEX = R"regex((?:(?:[0-9]{1,3}\.){3}|^(?:[0-9]{1,3}\.){5})[0-9]{1,3})regex";
	// static const std::string IP_REGEX_WEAK = R"regex((?:(?:[0-9]+.)+))regex";

	//! Regex matching a timestamp (sub-matches hour and GMT+...)
	// TODO: verifier le nombre de charactères d'un mois...
	static const std::string TIMESTAMP_REGEX = R"regex((?:\[[0-9]{1,2}\/[A-Z][a-z]{2,3}\/[0-9]{4}:([0-9]{1,2}):(?:[0-9]{1,2}:?){2} ((?:\+|\-)?[0-9]{4})\]))regex";

	//! Regex matching an absolute URL (submatches insa intranet domain name if any) (based on regex of 'stephenhay' in link bellow)
	//! @link https://mathiasbynens.be/demo/url-regex
	static const std::string ABSOLUTE_URL_REGEX = R"regex("((?:((?:https?|ftp):\/\/intranet-if\.insa-lyon\.fr)|(?:(?:https?|ftp):\/\/[^\s/$.?#].))[^\s]*)")regex";

	//! Regex matching a GET request (submatches relative URL)
	static const std::string GET_REGEX = R"regex("GET\s+(\/[^\s]*)\s+HTTPS?\/[0-9]+.[0-9]+")regex";
	static const std::string GET_REGEX_E = R"regex("GET\s+(\/[^\s]*\.(?:(?!)regex" + EXCLUDED_EXTENTIONS + R"regex(|\s).)*)\s+HTTPS?\/[0-9]+.[0-9]+")regex";

	//! Regex matching data size number
	static const std::string SIZE_REGEX = R"regex([0-9]+)regex";

	//! Regex matching an apache log line with GET and 200 as status code (hour and URLs can be extracted (submatches))
	// C++14: utiliser les string literals "..."s
	static const std::regex LOG_LINE_REGEX = std::regex(
		  R"r(^\s*)r" + IP_REGEX + R"regex(\s+-\s+-)regex" // <IP> - -
		+ R"r(\s+)r" + TIMESTAMP_REGEX
		+ R"r(\s+)r" + GET_REGEX
		+ R"regex(\s+200\s+[0-9]+)regex" // status code = 200 followed by data size number
		+ R"r(\s+)r" + ABSOLUTE_URL_REGEX
		+ R"r(\s+)r" + R"regex(\".+\"$)regex", std::regex::icase | std::regex::optimize); // use '/i' flag in order to ignore case

	//! Regex matching an apache log line with GET and 200 as status code (hour and URLs can be extracted (submatches))
	static const std::regex LOG_LINE_REGEX_E = std::regex(
		  R"r(^\s*)r" + IP_REGEX + R"regex(\s+-\s+-)regex" // <IP> - -
		+ R"r(\s+)r" + TIMESTAMP_REGEX
		+ R"r(\s+)r" + GET_REGEX_E
		+ R"regex(\s+200\s+[0-9]+)regex" // status code = 200 followed by data size number
		+ R"r(\s+)r" + ABSOLUTE_URL_REGEX
		+ R"regex(\s+)regex" + R"regex(\".+\"$)regex", std::regex::icase | std::regex::optimize); // use '/i' flag in order to ignore case

	static const size_t LINE_MATCH_NUM = 0;
	static const size_t HOUR_MATCH_NUM = 1;
	static const size_t TIMEZONE_MATCH_NUM = 2;
	static const size_t GET_URL_MATCH_NUM = 3;
	static const size_t REFERER_MATCH_NUM = 4;
	static const size_t INSA_INTRANET_MATCH_NUM = 5;

	//--------------------------------------------------------------------- PUBLIC
	//--------------------------------------------------------- Méthodes publiques

	void Log_parser::enable_hour_filter(hour_t hour) { m_filter_hour = hour; }
	void Log_parser::disable_hour_filter() { m_filter_hour = std::experimental::nullopt; }

	void Log_parser::enable_exclusion() noexcept { m_is_exclusion_filter_enabled = true; }
	void Log_parser::disable_exclusion() noexcept { m_is_exclusion_filter_enabled = false; }

	std::unique_ptr<Log_parser::urls_scores_t> Log_parser::parse_urllist(const std::string& log_file_name) const
	{
		// Multimap storing documents URLs with their occurrence number 
		auto urls = std::unique_ptr<urls_scores_t>(new urls_scores_t()); // C++14: std::make_unique<urls_scores_t>();
			
		for_each_log_line(std::move(log_file_name), [this, &urls](URL_t doc_url, URL_t referer_url)
		{
			auto url_it = urls->find(doc_url);
			if (url_it != std::end(*urls))
				url_it->second++;
			else
				urls->emplace(std::move(doc_url), 1);
		});

		return urls;
	}

	std::unique_ptr<Log_parser::graph_t> Log_parser::parse_graph(const std::string& log_file_name) const
	{
		auto log_graph = std::unique_ptr<graph_t>(new graph_t()); // C++14: std::make_unique<graph_t>();

		for_each_log_line(std::move(log_file_name), [this, &log_graph](URL_t doc_url, URL_t referer_url)
		{
			log_graph->add_link(std::move(referer_url), std::move(doc_url));
		});

		return log_graph;
	}


	//---------------------------------------------------------------------- PRIVE
	//----------------------------------------------------------- Méthodes privées

	void Log_parser::for_each_log_line(const std::string& log_file_name, const std::function<void(URL_t, URL_t)>& parsing_func) const
	{
		std::string line;
		std::ifstream infile(log_file_name);

		if (!infile.is_open())
			throw std::invalid_argument("Invalid log file name or don't have reading right (can't open log)");

		while (std::getline(infile, line))
		{
			std::smatch matches;
			if (std::regex_search(line, matches, (m_is_exclusion_filter_enabled ? LOG_LINE_REGEX_E : LOG_LINE_REGEX)))
			{
				if (m_filter_hour)
					if (*m_filter_hour != static_cast<hour_t>(parse<hour_t>(matches[HOUR_MATCH_NUM].str()) - parse<int>(matches[TIMEZONE_MATCH_NUM].str())/100)) // hour - timezone/100
						continue;

				auto doc_url = matches[GET_URL_MATCH_NUM].str();
				const auto& intranet_match = matches[INSA_INTRANET_MATCH_NUM];

				if (intranet_match.matched)
				{
					auto referer_url = matches[REFERER_MATCH_NUM].str().substr(intranet_match.str().size());
					parsing_func(std::move(doc_url), referer_url);
				}
				else
					parsing_func(std::move(doc_url), matches[REFERER_MATCH_NUM].str());
			}
		}

		if (infile.bad())
			throw std::invalid_argument("Error while reading log file");

		infile.close();
	}

}

