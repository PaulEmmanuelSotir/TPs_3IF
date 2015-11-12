/**************************************************************************************
					ville  -  A town with sensors at each road segments
					---------------------------------------------------
date                 : 11/2015
copyright            : (C) 2015 by B3311
**************************************************************************************/

//------------------------- Interface de la classe ville ------------------------------
#pragma once

//------------------------------------------------------------------ Includes personels
#include "capteur_stat.h"
#include "capteur_event.h"
#include "vec.h"
#include "utils.h"

namespace TP2
{
	class ville
	{
		//---------------------------------------------------------------------- PUBLIC
	public:
		//-------------------------------------------------- Constructeurs destructeurs
		ville();

		//------------------------------------------------------------- Methodes public

		/// <summary> mets a jour la ville avec un evenement donn� en parametre (commande ADD) </summary>
		///	<param name='new_event'> Nouveau evenement </param>
		void add_sensor(capteur_event new_event);

		/// <summary> affiche les statistiques sur les embouteillage par heure pour le jour donn� en parametre (commande JAM_DH) </summary>
		///	<param name='d7'> Jour de la semaine </param>
		void show_day_traffic_by_hour(capteur_stat::sensor_t d7) const;

		/// <summary> affiche les statistiques de trafic pour un jour de la semaine donn� (commande STATS_D7) </summary>
		///	<param name='d7'> Jour de la semaine </param>
		void show_day_traffic(capteur_stat::sensor_t d7) const;

		/// <summary> affiche le moment de depart optimal et le temps de parcourt estim� pour un trajet et un interval de temps donn� (commande OPT) </summary>
		///	<param name='d7'> Jour de la semaine </param>
		///	<param name='h_start'> Heure de d�but de l'interval </param>
		///	<param name='h_end'> Heure de fin de l'interval </param>
		///	<param name='seg_ids'> vecteur contenant l'id de chaque segment/capteur qui constitue le trajet </param>
		void show_optimal_timestamp(capteur_stat::sensor_t d7, capteur_stat::sensor_t h_start, capteur_stat::sensor_t h_end, const vec<capteur_stat::sensor_t>& seg_ids);

		/// <summary> Recherxhe les statistiques d'un capteur dont l'id est donn� en param�tre (commande STATS_C) </summary>
		///	<param name='id'> Identifiant du capteur � rechercher </param>
		/// <returns> Retourne un pointeur vers les statistiques d'un capteur ou nullptr si le capteur n'a pas �t� trouv� </returns>
		capteur_stat* get_sensor_stat_by_id(capteur_stat::sensor_t id);

		//----------------------------------------------------------------------- PRIVE
	private:
		//--------------------------------------------------------------- Usings priv�s
		using capteur_stat_with_events = pair<capteur_stat, vec<capteur_event>>;
		using hour_jam_stat = pair<unsigned int, unsigned int>;

		//---------------------------------------------------------- Structures priv�es
		/// <summary> Structure repr�sentant les statistiques du traffic d'une journ�e � l'�chelle de la ville </summary>
		struct day_traffic_stat
		{
			using stat_t = unsigned int;

			day_traffic_stat() = default;

			stat_t total_count = 0;
			stat_t green_count = 0;
			stat_t red_count = 0;
			stat_t orange_count = 0;
			stat_t dark_count = 0;
		};

		void update_global_week_stats(capteur_event new_event);

		inline capteur_stat_with_events* get_sensor_stat_with_events_by_id(capteur_stat::sensor_t id);

		/// <summary> Fonction statique rertournant la quantit� de minutes correspondant � l'�tat du traffic donn� en param�tre </summary>
		static inline capteur_event::sensor_t travel_duration_of_traffic(traffic state);

		double get_travel_duration(const vec<vec<capteur_event>>& segments_events, const vec<capteur_stat::sensor_t>& seg_ids, size_t seg_events_idx, capteur_stat::sensor_t d7, capteur_stat::sensor_t hour, capteur_stat::sensor_t minute);

		// TODO: faire des fonctions statiques v�rifiant les ranges des entr�es (minutes, secondes, heures)

		static const size_t DAYS_COUNT = 7;
		static const size_t HOUR_COUNT = 24;
		static const size_t MIN_COUNT = 60;
		static const size_t MAX_IDS_COUNT = 1500;
		static const size_t MAX_EVENT_COUNT = 20000000;

		vec<capteur_stat_with_events> m_sensor_stats;

		hour_jam_stat m_week_jam_distribution_by_hour[DAYS_COUNT][HOUR_COUNT];
		day_traffic_stat m_week_traffic_distribution_by_day[DAYS_COUNT];
	};
}