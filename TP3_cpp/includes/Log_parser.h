#ifndef LOG_PARSER_H
#define LOG_PARSER_H

#include <memory>
#include <string>
#include "optional.h"

#include "Graph.h"

namespace TP3
{
	class Log_parser
	{
	public:
		using hour_t = unsigned int;
		using URL_t = std::string;
		using graph_t = Graph<URL_t>;
		using urls_scores_t = std::unordered_multimap<URL_t, unsigned int>;

		void enable_hour_filter(hour_t hour);
		void disable_hour_filter();
		void enable_exclusion() noexcept;
		void disable_exclusion() noexcept;

		//! ...
		//! @throws std::invalid_argument if specified log file couldn't be read
		std::unique_ptr<urls_scores_t> parse_toplist(const std::string& log_file_name) const;

		//! ...
		//! @throws std::invalid_argument if specified log file couldn't be read
		std::unique_ptr<graph_t> parse_graph(const std::string& log_file_name) const;

	private:
		void for_each_log_line(const std::string& log_file_name, const std::function<void(URL_t, URL_t)>& parsing_func) const;

		bool m_is_exclusion_filter_enabled = false;
		std::experimental::optional<hour_t> m_filter_hour = 0;
	};
}

#endif // LOG_PARSER_H

