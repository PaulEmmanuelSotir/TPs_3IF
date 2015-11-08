#pragma once

#include "capteur.h"
#include "collection.h"
#include "utils.h"

namespace TP2
{
	class ville
	{
	public:
		ville();
		void add_sensor(unsigned int id, capteur::sens_t hour, capteur::sens_t min, capteur::sens_t d7, capteur::traffic state);
		void show_day_traffic_by_hour(capteur::sens_t d7) const;
		void show_day_traffic(capteur::sens_t d7) const;
		void show_optimal_timestamp(capteur::sens_t d7, capteur::sens_t h_start, capteur::sens_t h_end, capteur::sens_t seg_ids[], size_t seg_ids_size) const;
		nullable<capteur> get_sensor_by_id(size_t id) const;

	private:
		struct stat
		{
			using stat_t = unsigned int;

			stat() = default;

			stat_t total_count = 0;
			stat_t green_count = 0;
			stat_t red_count = 0;
			stat_t orange_count = 0;
			stat_t dark_count = 0;
		};

		void update_week_stats(const capteur& sensor, capteur::traffic state);

		static const size_t DAYS_COUNT = 7;
		static const size_t HOUR_COUNT = 24;

		capteur m_sensor_lookup_table[1500];
		size_t m_size = 0;

		pair<unsigned int, unsigned int> m_week_jam_distribution[DAYS_COUNT][HOUR_COUNT];
		stat m_week_traffic_distribution[DAYS_COUNT];
	};
}
