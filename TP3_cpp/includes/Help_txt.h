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
			R"help(NAME)help"
			R"help(    log_analyzer)help"
			R"help()help"
			R"help(SYNOPSIS)help"
			R"help(    log_analyzer [options]file_name.log)help"
			R"help()help"
			R"help(DESCRIPTION)help"
			R"help(    log_analyzer is a program for analyzing an apache server log file. )help"
			R"help()help"
			R"help(    The options are as follows:)help"
			R"help()help"
			R"help(		-g -G --graph			Enable the graphics option to create a GraphViz file.)help"
			R"help(		-e -E --excludeMedia	Exclude css, javascript and image files from the result.)help"
			R"help(		-t -T --hour			Ignore all log entries which haven't been added at the given hour.)help"
			R"help(		-h --help				Show this help message.)help";
	}
}

#endif // HELP_TXT_H

