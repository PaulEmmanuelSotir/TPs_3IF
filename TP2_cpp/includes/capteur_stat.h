/*********************************************************************************************
					capteur_stat  -  A struture of sensor's statistics
					--------------------------------------------------
date                 : 11/2015
copyright            : (C) 2015 by B3311
**********************************************************************************************/

//-------------------------- Interface de la structure capteur_stat ---------------------------
#pragma once

//----------------------------------------------------------------------- Includes personnels
#include "capteur_event.h"

namespace TP2
{
	struct capteur_stat
	{
		//---------------------------------------------------------------------------- PUBLIC
	public:
		//---------------------------------------------------------------------------- Usings
		using sensor_t = capteur_event::sensor_t;
		//-------------------------------------------------------- Constructeurs destructeurs
		capteur_stat() = default;
		capteur_stat(capteur_event initial_event);
		capteur_stat(const capteur_stat& other);
		capteur_stat(capteur_stat&& other) noexcept;
		~capteur_stat();

		//---------------------------------------------------------------- Méthodes publiques

		void update(capteur_event new_event);
		/// <summary> calcul les ctatistique de trafic pour un capteur </summary>
		void show_time_distribution() const;

		sensor_t get_id() const;
		sensor_t get_d7() const;
		sensor_t get_hour() const;
		sensor_t get_min() const;

		//----------------------------------------------------------------------------- PRIVE
	private:
		sensor_t m_taffic_counts[capteur_event::TRAFFIC_CARDINALITY] = { 0, 0, 0, 0 };
		capteur_event m_stat_timestamp;

		static inline size_t to_taffic_count_idx(traffic state);

		//----------------------------------------------------------- Surcharges d'opérateurs
	public:
		const capteur_stat& operator=(capteur_stat other);

		friend bool operator==(const capteur_stat& lhs, const capteur_stat& rhs);
		friend bool operator!=(const capteur_stat& lhs, const capteur_stat& rhs);

		friend bool operator<(const capteur_stat& lhs, const capteur_stat& rhs);
		friend bool operator>(const capteur_stat& lhs, const capteur_stat& rhs);
		friend bool operator<=(const capteur_stat& lhs, const capteur_stat& rhs);
		friend bool operator>=(const capteur_stat& lhs, const capteur_stat& rhs);

		friend void swap(capteur_stat& lhs, capteur_stat& rhs) noexcept;
	};
}
