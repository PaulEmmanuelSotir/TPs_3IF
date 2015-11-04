
#include "ville.h"
#include "capteur.h"

namespace TP2
{
	ville::ville() : m_capteurs()
	{
		//TODO: init m_capteurs

		for (size_t i = 0; i < DAYS_COUNT; i++)
			for (size_t j = 0; j < HOUR_COUNT; j++)
				m_weekTrafficJamDistribution[i][j] = pair<unsigned int, unsigned int>(0, 0);
	}

	void ville::ajouter_capteur(const capteur & sensor)
	{
		auto sensor_ptr = getSensorById(sensor.getID());

		if (sensor_ptr == nullptr)
			m_capteurs[m_size++] = sensor;
		else
			sensor_ptr->update(sensor);
	}

	void ville::updateWeekStats(const capteur & sensor)
	{
		auto time = sensor.getLastTimestamp();
		auto& jam_stat = m_weekTrafficJamDistribution[time.d7][time.hour];
		jam_stat.second++;

		auto& stat = m_weekTrafficDistribution[time.d7];
		stat.total_count++;

		switch (sensor.getTraffic())
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

	capteur* ville::getSensorById(capteur::ID_t id)
	{
		for (size_t i = 0; i < m_size; i++)
		{
			auto& capt = m_capteurs[i];
			if (capt.getID() == id)
				return &capt;
		}

		return nullptr;
	}

	void ville::ShowDayTrafficByHour(timestamp::time_t d7)
	{
		for (size_t i = 0; i < HOUR_COUNT; i++)
		{
			const auto& stat = m_weekTrafficJamDistribution[d7][i];
			std::cout << d7 << " "
				<< i << " "
				<< (stat.second == 0 ? 0 : static_cast<unsigned int>(100 * stat.first / stat.second)) << "%" << std::endl;
		}
	}

	void ville::ShowDayTraffic(timestamp::time_t d7)
	{
		unsigned int total_count = 0;
		unsigned int badtraffic_count = 0;

		const auto& stat = m_weekTrafficDistribution[d7];
		std::cout << capteur::traffic::vert << " " << static_cast<int>(100 * stat.green_count / stat.total_count) << "%";
		std::cout << capteur::traffic::rouge << " " << static_cast<int>(100 * stat.red_count / stat.total_count) << "%";
		std::cout << capteur::traffic::orange << " " << static_cast<int>(100 * stat.orange_count / stat.total_count) << "%";
		std::cout << capteur::traffic::noir << " " << static_cast<int>(100 * stat.dark_count / stat.total_count) << "%";
	}
}