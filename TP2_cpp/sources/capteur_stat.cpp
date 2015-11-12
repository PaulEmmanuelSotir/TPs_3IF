/********************************************************************************************
										capteur_stat.cpp
										----------------
date                 : 10/2015
copyright            : (C) 2015 by B3311
********************************************************************************************/

//--------------------------------------------------------------------------- Include systeme
#include <iostream>

//------------------------------------------------------------------------- Include personnel
#include "capteur_stat.h"
#include "utils.h"

namespace TP2
{
	//------------------------------------------------------------------------- Constructeurs

	capteur_stat::capteur_stat(capteur_event initial_event)
		: capteur_stat()
	{
#ifdef MAP
		cout << "Appel au constructeur 'capteur_stat::capteur_stat(capteur_event)'" << endl;
#endif
		m_stat_timestamp = initial_event;
		update(initial_event);
	}

	capteur_stat::capteur_stat(const capteur_stat& other)
	{
#ifdef MAP
		cout << "Appel au constructeur de copie 'capteur_stat::capteur_stat(const capteur_stat&)'" << endl;
#endif
		reinterpret_cast<sensor_t&>(m_stat_timestamp) = reinterpret_cast<const sensor_t&>(other.m_stat_timestamp);

		m_taffic_counts[0] = other.m_taffic_counts[0];
		m_taffic_counts[1] = other.m_taffic_counts[1];
		m_taffic_counts[2] = other.m_taffic_counts[2];
		m_taffic_counts[3] = other.m_taffic_counts[3];
	}

	capteur_stat::capteur_stat(capteur_stat&& other) noexcept
	{
#ifdef MAP
		cout << "Appel au move-constructeur 'capteur_stat::capteur_stat(capteur_stat&&)'" << endl;
#endif
		swap(*this, other);
	}

	capteur_stat::~capteur_stat()
	{
#ifdef MAP
		cout << "Appel au destructeur '~capteur_stat::capteur_stat()'" << endl;
#endif
	}

	//-------------------------------------------------------------------- Méthodes publiques

	void capteur_stat::update(capteur_event new_event)
	{
		if (m_stat_timestamp.id == new_event.id)
		{
			m_stat_timestamp = new_event;
			m_taffic_counts[new_event.traff]++;
		}
	}

	void capteur_stat::show_time_distribution() const
	{
		unsigned int total = 0;
		for (size_t i = 0; i < capteur_event::TRAFFIC_CARDINALITY; ++i)
			total += m_taffic_counts[i];

		if (total != 0)
			std::cout << traffic::vert << " " << static_cast<int>((100.0 * m_taffic_counts[to_taffic_count_idx(traffic::vert)]) / total + 0.5) << "%" << std::endl
			<< traffic::rouge << " " << static_cast<int>((100.0 * m_taffic_counts[to_taffic_count_idx(traffic::rouge)]) / total + 0.5) << "%" << std::endl
			<< traffic::orange << " " << static_cast<int>((100.0 * m_taffic_counts[to_taffic_count_idx(traffic::orange)]) / total + 0.5) << "%" << std::endl
			<< traffic::noir << " " << static_cast<int>((100.0 * m_taffic_counts[to_taffic_count_idx(traffic::noir)]) / total + 0.5) << "%" << std::endl;
		else
			std::cout << traffic::vert << " 0%" << std::endl
			<< traffic::rouge << " 0%" << std::endl
			<< traffic::orange << " 0%" << std::endl
			<< traffic::noir << " 0%" << std::endl;
	}

	capteur_stat::sensor_t capteur_stat::get_id() const { return m_stat_timestamp.id; }
	capteur_stat::sensor_t capteur_stat::get_d7() const { return m_stat_timestamp.d7; }
	capteur_stat::sensor_t capteur_stat::get_hour() const { return m_stat_timestamp.hour; }
	capteur_stat::sensor_t capteur_stat::get_min() const { return m_stat_timestamp.min; }

	//---------------------------------------------------------------------- Méthodes privées

	inline size_t capteur_stat::to_taffic_count_idx(traffic state)
	{
		switch (state)
		{
		case traffic::vert: return 0;
		case traffic::rouge: return 1;
		case traffic::orange: return 2;
		case traffic::noir: return 3;
		}
		return 0; // impossible
	}

	//---------------------------------------------------------------- Surchages d'opérateurs

	void swap(capteur_stat& lhs, capteur_stat& rhs) noexcept
	{
		// if one of the following swap calls isn't noexcept, we raise a static_assert
		// Commenté car is_nothrow_swappable ne fonctionne pas avec gcc installé en IF
		//		static_assert(is_nothrow_swappable<capteur_stat::sensor_t*, capteur_event>(), "Swap function could throw and let 'capteur_stat' objects in incoherant state!");

		// enable ADL (following lines will use custom implementation of swap or std::swap if there isn't custom implementation)
		using std::swap;

		swap(lhs.m_stat_timestamp, rhs.m_stat_timestamp);
		swap(lhs.m_taffic_counts, rhs.m_taffic_counts);
	}

	const capteur_stat& capteur_stat::operator=(capteur_stat other)
	{
		// Copy and swap idiom
		swap(*this, other);
		return *this;
	}

	bool operator==(const capteur_stat& lhs, const capteur_stat& rhs) { return lhs.m_stat_timestamp == rhs.m_stat_timestamp; }
	bool operator!=(const capteur_stat& lhs, const capteur_stat& rhs) { return !(lhs == rhs); }

	bool operator<(const capteur_stat& lhs, const capteur_stat& rhs) { return lhs.m_stat_timestamp < rhs.m_stat_timestamp; }
	bool operator>(const capteur_stat& lhs, const capteur_stat& rhs) { return rhs < lhs; }
	bool operator<=(const capteur_stat& lhs, const capteur_stat& rhs) { return !(rhs < lhs); }
	bool operator>=(const capteur_stat& lhs, const capteur_stat& rhs) { return !(lhs < rhs); }
}
