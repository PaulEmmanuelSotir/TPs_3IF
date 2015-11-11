#pragma once

#include "capteur_stat.h"
#include "capteur_event.h"
#include "vec.h"
#include "utils.h"

namespace TP2
{
	class ville
	{
	public:
		ville();
		void add_sensor(capteur_event new_event);
		void show_day_traffic_by_hour(capteur_stat::sensor_t d7) const;
		void show_day_traffic(capteur_stat::sensor_t d7) const;
		void show_optimal_timestamp(capteur_stat::sensor_t d7, capteur_stat::sensor_t h_start, capteur_stat::sensor_t h_end, const vec<capteur_stat::sensor_t>& seg_ids);
		capteur_stat* get_sensor_stat_by_id(capteur_stat::sensor_t id);

	private:
		using capteur_stat_with_events = pair<capteur_stat, vec<capteur_event>>;
		using hour_jam_stat = pair<unsigned int, unsigned int>;
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

		/// <summary> Fonction statique rertournant la quantité de minutes correspondant à l'état du traffic donné en paramètre </summary>
		static inline capteur_event::sensor_t travel_duration(traffic state);

		double get_travel_duration(const vec<capteur_stat::sensor_t>& seg_ids, size_t idx, capteur_stat::sensor_t d7, capteur_stat::sensor_t hour, capteur_stat::sensor_t minute);

		// TODO: faire des fonctions statiques vérifiant les ranges des entrées
		
		static const size_t DAYS_COUNT = 7;
		static const size_t HOUR_COUNT = 24;
		static const size_t MIN_COUNT = 60;
		static const size_t MAX_IDS_COUNT = 1'500;
		static const size_t MAX_EVENT_COUNT = 20'000'000;

		vec<capteur_stat_with_events> m_sensor_stats;

		hour_jam_stat m_week_jam_distribution_by_hour[DAYS_COUNT][HOUR_COUNT];
		day_traffic_stat m_week_traffic_distribution_by_day[DAYS_COUNT];

		friend bool operator==(const capteur_stat_with_events& lhs, const capteur_stat_with_events& rhs);
		friend bool operator!=(const capteur_stat_with_events& lhs, const capteur_stat_with_events& rhs);

		friend bool operator<(const capteur_stat_with_events& lhs, const capteur_stat_with_events& rhs);
		friend bool operator>(const capteur_stat_with_events& lhs, const capteur_stat_with_events& rhs);
		friend bool operator<=(const capteur_stat_with_events& lhs, const capteur_stat_with_events& rhs);
		friend bool operator>=(const capteur_stat_with_events& lhs, const capteur_stat_with_events& rhs);
	};
}