#pragma once

#include "capteur.h"

namespace TP2
{
	template<typename T1, typename T2>
	struct pair
	{
		pair() = default;
		pair(T1 f, T2 s) : first(f), second(s) { }

		T1 first;
		T2 second;
	};

	class ville
	{
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

	public:
		ville();
		void ajouter_capteur(const capteur& sensor);
		capteur* getSensorById(capteur::ID_t id);
		void ShowDayTrafficByHour(timestamp::time_t d7);
		void ShowDayTraffic(timestamp::time_t d7);

	private:
		void updateWeekStats(const capteur & sensor);

		static const size_t DAYS_COUNT = 7;
		static const size_t HOUR_COUNT = 24;

		// TODO: changer ça !
		capteur m_capteurs[1500];
		size_t m_size = 0;

		pair<unsigned int, unsigned int> m_weekTrafficJamDistribution[DAYS_COUNT][HOUR_COUNT];
		stat m_weekTrafficDistribution[DAYS_COUNT];
	};
}