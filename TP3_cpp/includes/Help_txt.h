/*********************************************************************************
									Help text
									---------
date                 : 12/2015
copyright            : (C) 2015 by B3311
*********************************************************************************/

#ifndef HELP_TXT_H
#define HELP_TXT_H

//! \namespace TP3
//! espace de nommage regroupant le code crée pour le TP3 de C++
namespace TP3
{
	//! Retourne le texte d'aide du programme
	constexpr const char* Help_txt() noexcept
	{
		return
			R"help(NAME)help" "\n"
			R"help(	log_analyzer - Analyze Apache Log)help" "\n"
			R"help()help" "\n"
			R"help(SYNOPSIS)help" "\n"
			R"help(	log_analyzer LOG_FILE [OPTION]...)help" "\n"
			R"help()help" "\n"
			R"help(DESCRIPTION)help" "\n"
			R"help(	Analyzes a given apache server LOG_FILE to output a 'get' request graph or a list of most used URLs.)help" "\n"
			R"help()help" "\n"
			R"help(	-g, -G, --graph)help" "\n"
			R"help(		Creates a graph in which each node is a URL, and each link is a successfull)help" "\n"
			R"help(		GET request between these nodes. Outputs GraphViz text file using specfied filename.)help" "\n"
			R"help(		If this option isn't specified, the program will only output a list of most used URLs.)help" "\n"
			R"help(	-l, -L, --listCount)help" "\n"
			R"help(		Specifies the maximum number of URLs in the outputed list of most used URLs.)help" "\n"
			R"help(		Must be greater than 1 (10 by default).)help" "\n"
			R"help(	-e, -E, --excludeMedia)help" "\n"
			R"help(		Excludes css, javascript and image files from the result.)help" "\n"
			R"help(	-t, -T, --hour)help" "\n"
			R"help(		Ignore all log entries which haven't been added at the specfied hour.)help" "\n"
			R"help(	-h, --help)help" "\n"
			R"help(		Show this documentation)help" "\n"
			R"help()help" "\n"
			R"help(EXAMPLES)help" "\n"
			R"help(	log_analyzer mylog.log --hour 12 -e)help" "\n"
			R"help(	Get top ten list of URLs used at 12th hour and which aren't images, css nor javascript files)help" "\n"
			R"help()help" "\n"
			R"help(	log_analyzer mylog.log -e -g graph.dot)help" "\n"
			R"help(	Get GET request graph of URLs which aren't images, css nor javascript files)help" "\n"
			R"help()help" "\n"
			R"help(	log_analyzer mylog.log -t 2 -l 20)help" "\n"
			R"help(	Get top 20 list of URLs used at 2th hour)help" "\n"
			R"help()help" "\n"
			R"help(REPORTING BUGS)help" "\n"
			R"help(	You didn't saw any bugs.)help" "\n\n";
	}
}

#endif // HELP_TXT_H

