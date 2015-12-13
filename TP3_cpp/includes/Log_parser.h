/*********************************************************************************
						Log_parser  - An apache log parser
						----------------------------------
date                 : 12/2015
copyright            : (C) 2015 by B3311
*********************************************************************************/

//----------------------- Interface de la classe Log_parser ----------------------
#ifndef LOG_PARSER_H
#define LOG_PARSER_H

//-------------------------------------------------------------- Includes systèmes
#include <memory>
#include <string>
#include "optional.h"

//----------------------------------------------------------- Interfaces utilisées
#include "Graph.h"

//! \namespace TP3
//! espace de nommage regroupant le code crée pour le TP3 de C++
namespace TP3
{
	//---------------------------------------------------------------------- Types

	//! Classe permettant de parser un log apache et d'en déduire, soit un graphe
	//! des requettes GET soit la liste des URLs utilisés dans ces requêtes
	class Log_parser
	{
		//----------------------------------------------------------------- PUBLIC
	public:
		//----------------------------------------------- Types et alias publiques
		using hour_t = unsigned short;
		using URL_t = std::string;
		using graph_t = Graph<URL_t>;
		using urls_scores_t = std::unordered_multimap<URL_t, unsigned int>;

		//----------------------------------------------------- Méthodes publiques

		void enable_hour_filter(hour_t hour);
		void disable_hour_filter();
		void enable_exclusion() noexcept;
		void disable_exclusion() noexcept;

		//! Parse le log donné en parametre pour trouver la liste des URLs utlisés
		//! lors de requêtes GET valides associés à leur nombre d'occurrences.
		//! @remarks
		//!		- Si 'enable_hour_filter(hour_t)' a été appellé, les résultat ne comprendra
		//!		que les requettes faites à l'heure spécifiée.
		//!		- Si enable_exclusion() a été appellé, les résultat ne comprendra que les
		//!		requettes qui ne concernent pas des fichier css, javascript ou des images.
		//! @throws std::invalid_argument if specified log file couldn't be read
		std::unique_ptr<urls_scores_t> parse_urllist(const std::string& log_file_name) const;

		//! Parse le log donné en parametre pour en déduire le graphe des requêtes
		//! GET valides.
		//! @remarks
		//!		- Si 'enable_hour_filter(hour_t)' a été appellé, les résultat ne comprendra
		//!		que les requettes faites à l'heure spécifiée.
		//!		- Si enable_exclusion() a été appellé, les résultat ne comprendra que les
		//!		requettes qui ne concernent pas des fichier css, javascript ou des images.
		//! @throws std::invalid_argument if specified log file couldn't be read
		std::unique_ptr<graph_t> parse_graph(const std::string& log_file_name) const;

		//------------------------------------------------------------------ PRIVE
	private:
		//------------------------------------------------------- Méthodes privées

		//! Fonction aidant à la lecture d'un log apache ligne par ligne
		void for_each_log_line(const std::string& log_file_name, const std::function<void(URL_t, URL_t)>& parsing_func) const;

		//------------------------------------------------------- Attributs privés

		bool m_is_exclusion_filter_enabled = false;
		std::experimental::optional<hour_t> m_filter_hour = std::experimental::nullopt;
	};
}

#endif // LOG_PARSER_H

