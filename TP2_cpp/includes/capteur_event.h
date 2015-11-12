/***************************************************************************************
					capteur_event  -  A sensor event structure
					------------------------------------------
date                 : 11/2015
copyright            : (C) 2015 by B3311
***************************************************************************************/

//-------------------- Interface de la structure capteur_event -------------------------
#pragma once

//------------------------------------------------------------------ Includes personnels
#include "utils.h"

namespace TP2
{
	//----------------------------------------------------------------------------------
	/// <summary> Enumération typée représenatant un niveau de traffic </summary>
	//----------------------------------------------------------------------------------
	enum class traffic : char { vert = 'V', rouge = 'J', orange = 'R', noir = 'N' };

	//----------------------------------------------------------------------------------
	/// <summary> Structure représentant un évémenement 'ADD' (id, timestamp et traffic)
	///		C'est une structure dont la taille est de 32 bits ce qui permet d'en stocker un grand
	///		nombre en mémoire et faire des opérations de comparaison et copie plus rapide </summary> 
	//----------------------------------------------------------------------------------
	struct capteur_event
	{
		//----------------------------------------------------------------------- PUBLIC
	public:
		//----------------------------------------------------------------------- Usings
		using sensor_t = uint32_t; // alignement sur 32 bits

		//---------------------------------------------------------------- Constructeurs
		/// <summary> Constructeur de la structure 'capteur_event' </summary>
		///	<param name='id'> Identifiant du capteur ayant produit cet évenement </param>
		///	<param name='d7'> Jour de la semaine </param>
		///	<param name='hour'> Heure de l'événement </param>
		///	<param name='min'> Minute de l'événement </param>
		///	<param name='state'> Etat du capteur (traffique) </param>
		capteur_event(sensor_t id = 0, sensor_t d7 = 1, sensor_t hour = 0, sensor_t min = 0, traffic state = traffic::vert);

		//-------------------------------------------------------------------- Attributs

		/// Identifiant du capteur ayant produit cet évenement
		sensor_t id : 16;		// (0 - 65536)
		/// Jour de la semaine
		sensor_t d7 : 3;		// (0 - 7)
		///  Heure de l'événement 
		sensor_t hour : 5;		// (0 - 31)
		/// Minute de l'événement
		sensor_t min : 6;		// (0 - 63)
		//------------------------------------------------------------------------ PRIVE
	private:
		/// Etat du capteur (traffique)
		sensor_t traff : 2;		// (0 - 3)	// private car il faut préfèrer la représentation typée d'un traffic (enum class)

		//----------------------------------------------------------- Méthodes publiques

		//----------------------------------------------------------------------- PUBLIC
	public:
		void set_traffic(traffic state);
		traffic get_traffic() const;

		//--------------------------------------------------------- Constantes statiques

		/// Nombre de valeurs différentes dans l'énumération 'traffic'
		static const size_t TRAFFIC_CARDINALITY = 4;

		//------------------------------------------------------------------------ PRIVE
	private:
		/// Masque permettant d'ignorer l'attribut traff lors de la comparaison d'objets 'capteur_event'
		static const sensor_t COMPARISION_MASK = 0xFFFFFFFC; // enlève les deux dernier bits

		//------------------------------------------------------ Surcharges d'opérateurs

		friend void swap(capteur_event& lhs, capteur_event& rhs) noexcept;

		friend bool operator==(const capteur_event& lhs, const capteur_event& rhs);
		friend bool operator!=(const capteur_event& lhs, const capteur_event& rhs);

		friend bool operator<(const capteur_event& lhs, const capteur_event& rhs);
		friend bool operator>(const capteur_event& lhs, const capteur_event& rhs);
		friend bool operator<=(const capteur_event& lhs, const capteur_event& rhs);
		friend bool operator>=(const capteur_event& lhs, const capteur_event& rhs);

		// Permet à 'capteur_stat' d'accèder à 'traff' plus rappidement
		friend struct capteur_stat;
	};

	// On s'assure que la structure fait bien 32 bits
	static_assert(sizeof(capteur_event) == 4, "La structure 'capteur_event' doit avoir une taille de 4 octets.");

	//---------------------------------------------------------- Surcharges d'opérateurs

	/// <summary> Surcharge de l'opérateur ostream pour le type traffic </summary>
	std::ostream& operator<<(std::ostream& os, const traffic& state);

	/// <summary> Surcharge de l'opérateur istream pour le type traffic </summary>
	std::istream& operator>>(std::istream& is, traffic& state);
}