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
	public:
		ville();
		void ajouter_capteur(const capteur& sensor);
		capteur getSensorById(capteur::ID_t id);

	private:
		static const size_t DAYS_COUNT = 7;
		static const size_t HOUR_COUNT = 24;

		// TODO: changer ça !
		capteur m_capteurs[1500];
		size_t m_size = 0;

		pair<unsigned int, unsigned int> m_weekTrafficDistribution [DAYS_COUNT][HOUR_COUNT];
	};
}