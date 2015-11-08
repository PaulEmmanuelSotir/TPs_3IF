#include <iostream>

#include "capteur.h"

namespace TP2
{
	capteur::capteur() : m_d7(1), m_hour(0), m_min(0) { }

	capteur::capteur(sens_t id, sens_t d7, sens_t hour, sens_t min, traffic state)
		: capteur()
	{
		update(id, d7, hour, min, state);
	}

	inline size_t capteur::to_size_t(capteur::traffic state)
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

	void capteur::update(sens_t id, sens_t d7, sens_t hour, sens_t min, traffic state)
	{
		m_id = id;
		m_d7 = d7;
		m_hour = hour;
		m_min = min;
		m_taffic_counts[to_size_t(state)].count++;
	}

	void capteur::show_time_distribution() const
	{
		unsigned int total = 0;
		for (size_t i = 0; i < capteur::TRAFFIC_CARDINALITY; ++i)
			total += m_taffic_counts[i].count;

		std::cout << traffic::vert << " " << static_cast<int>(100 * m_taffic_counts[to_size_t(traffic::vert)].count / total) << "%" << std::endl;
		std::cout << traffic::rouge << " " << static_cast<int>(100 * m_taffic_counts[to_size_t(traffic::rouge)].count / total) << "%" << std::endl;
		std::cout << traffic::orange << " " << static_cast<int>(100 * m_taffic_counts[to_size_t(traffic::orange)].count / total) << "%" << std::endl;
		std::cout << traffic::noir << " " << static_cast<int>(100 * m_taffic_counts[to_size_t(traffic::noir)].count / total) << "%" << std::endl;
	}

	capteur::sens_t capteur::get_id() const { return m_id; }
	capteur::sens_t capteur::get_d7() const { return m_d7; }
	capteur::sens_t capteur::get_hour() const { return m_hour; }
	capteur::sens_t capteur::get_min() const { return m_min; }

	bool operator==(const capteur& lhs, const capteur& rhs) { return lhs.m_id == rhs.m_id; }
	bool operator!=(const capteur& lhs, const capteur& rhs) { return !(lhs == rhs); }
	bool operator<(const capteur& lhs, const capteur& rhs) { return lhs.m_id < rhs.m_id; }
	bool operator>(const capteur& lhs, const capteur& rhs) { return rhs < lhs; }
	bool operator<=(const capteur& lhs, const capteur& rhs) { return !(rhs < lhs); }
	bool operator>=(const capteur& lhs, const capteur& rhs) { return !(lhs < rhs); }

	std::ostream& operator<<(std::ostream& os, const capteur::traffic& state)
	{
		os << static_cast<char>(state);
		return os;
	}

	std::istream& operator>>(std::istream& is, capteur::traffic& state)
	{
		auto c = static_cast<char>(capteur::traffic::noir);
		is >> c;
		state = static_cast<capteur::traffic>(c);
		return is;
	}
}
