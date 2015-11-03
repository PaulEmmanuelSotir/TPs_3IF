/********************************************************************************************
main.cpp
--------
date                 : 10/2015
copyright            : (C) 2015 by B3311
********************************************************************************************/

//----------------------------------------------------------------------------------- INCLUDE
//--------------------------------------------------------------------------- Include système
#include <iostream>
#include <string>

//------------------------------------------------------------------------- Include personnel
#include "capteur.h"
#include "ville.h"

//-------------------------------------------------------------------------------------- MAIN

int main()
{
	TP2::ville lyon;

	while (1)
	{
		std::string input;
		std::getline(std::cin, input);

		if (input == "ADD")
		{
			TP2::capteur::ID_t id;
			TP2::capteur::traffic etat;
			TP2::timestamp t;

			std::cin >> id >> t >> etat;

			lyon.ajouter_capteur(TP2::capteur(id, etat, t));
		}
		else if (input == "STATS_C")
		{
			TP2::capteur::ID_t id;
			std::cin >> id;

			lyon.getSensorById(id).ShowTimeDistribution();
		}
		else if (input == "JAM_DH")
		{
			TP2::timestamp::time_t d7;
			std::cin >> d7;

	//		lyon.
		}
		else if (input == "STATS_D7")
		{

		}
		else if (input == "OPT")
		{

		}
		else if (input == "EXIT")
			break;
		else
			printf("Invalid input");
	}

	return EXIT_SUCCESS;
}
