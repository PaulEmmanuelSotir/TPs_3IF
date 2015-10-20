/********************************************************************************************
										main.cpp
										--------
date                 : 10/2015
copyright            : (C) 2015 by B3311
********************************************************************************************/

//----------------------------------------------------------------------------------- INCLUDE
//--------------------------------------------------------------------------- Include système
#include <iostream>

//------------------------------------------------------------------------- Include personnel
#include "collection.h"
#include "tests.h"

//-------------------------------------------------------------------------------------- MAIN

int main()
{
	std::cout
		<< R"(			 _________ ___    _____  __    __ )" << std::endl
		<< R"(			/_  __/ _ <  /   / ___/_/ /___/ /_)" << std::endl
		<< R"(			 / / / ___/ /   / /__/_  __/_  __/)" << std::endl
		<< R"(			/_/ /_/  /_/    \___/ /_/   /_/   )" << std::endl << std::endl;

	std::cout << "### TESTING COLLECTION CLASS (no dogs will be harmed during this test) ###";

	test(test_lifetime, "OBJECT LIFETIME");
	test(test_afficher, "AFFICHER");
	test(test_ajouter, "AJOUTER");
	test(test_retirer, "RETIRER");
	test(test_ajuster, "AJUSTER");
	test(test_reunir, "REUNIR");

	std::cout << std::endl << std::endl << "Press ENTER to exit...";
	std::cin.get();

	return EXIT_SUCCESS;
}
