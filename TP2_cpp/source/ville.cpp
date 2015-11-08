#include <iostream>

#include "ville.h"
#include "capteur.h"

namespace TP2
{
	ville::ville()
	{
		for (size_t i = 0; i < DAYS_COUNT; i++)
			for (size_t j = 0; j < HOUR_COUNT; j++)
				m_week_jam_distribution[i][j] = pair<unsigned int, unsigned int>(0, 0);
	}

	void ville::add_sensor(unsigned int id, capteur::sens_t d7, capteur::sens_t hour, capteur::sens_t min, capteur::traffic state)
	{
		auto& sens = m_sensor_lookup_table[id];
		sens.update(id, d7, hour, min, state);
		update_week_stats(sens, state);
	}

	void ville::show_day_traffic_by_hour(capteur::sens_t d7) const
	{
		for (size_t i = 0; i < HOUR_COUNT; i++)
		{
			const auto& stat = m_week_jam_distribution[d7][i];
			std::cout << d7 << " "
				<< i << " "
				<< (stat.second == 0 ? 0 : static_cast<unsigned int>(100 * stat.first / stat.second)) << "%" << std::endl;
		}
	}

	void ville::show_day_traffic(capteur::sens_t d7) const
	{
		const auto& stat = m_week_traffic_distribution[d7];
		std::cout << capteur::traffic::vert << " " << static_cast<int>(100 * stat.green_count / stat.total_count) << "%";
		std::cout << capteur::traffic::rouge << " " << static_cast<int>(100 * stat.red_count / stat.total_count) << "%";
		std::cout << capteur::traffic::orange << " " << static_cast<int>(100 * stat.orange_count / stat.total_count) << "%";
		std::cout << capteur::traffic::noir << " " << static_cast<int>(100 * stat.dark_count / stat.total_count) << "%";
	}

	void ville::show_optimal_timestamp(capteur::sens_t d7, capteur::sens_t h_start, capteur::sens_t h_end, capteur::sens_t seg_ids[], size_t seg_ids_size) const
	{

	}

	nullable<capteur> ville::get_sensor_by_id(size_t id) const
	{
		nullable<capteur> nullable_sensor(m_sensor_lookup_table[id]);
		return nullable_sensor;
	}

	//----prive...

	void ville::update_week_stats(const capteur& sensor, capteur::traffic state)
	{
		auto& jam_stat = m_week_jam_distribution[sensor.get_d7()][sensor.get_hour()];
		jam_stat.second++;

		auto& stat = m_week_traffic_distribution[sensor.get_d7()];
		stat.total_count++;

		switch (state)
		{
		case capteur::traffic::noir:
			jam_stat.first++;
			stat.dark_count++;
			break;
		case capteur::traffic::orange:
			jam_stat.first++;
			stat.orange_count++;
			break;
		case capteur::traffic::rouge:
			stat.red_count++;
			break;
		case capteur::traffic::vert:
			stat.green_count++;
			break;
		}
	}
}