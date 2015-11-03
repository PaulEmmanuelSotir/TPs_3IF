#include <iostream>

#include "capteur.h"

namespace TP2
{
	timestamp::timestamp(time_t year, time_t month, time_t day, time_t d7, time_t hour, time_t min)
	{
		this->year = year;
		this->month = month;
		this->day = day;
		this->d7 = d7;
		this->hour = hour;
		this->min = min;
	}

	capteur::capteur(ID_t id, traffic etat, timestamp t) : m_id(id)
	{
		update(etat, t);
	}

	void capteur::update(traffic etat, timestamp t)
	{
		//TODO: implement == op 4 timestamps  
		switch (etat)
		{
		case traffic::noir:
			m_duree_noir++;
			break;
		case traffic::orange:
			m_duree_orange++;
			break;
		case traffic::rouge:
			m_duree_rouge++;
			break;
		case traffic::vert:
			m_duree_vert++;
			break;
		}

		m_lastUpdate = t;
	}

	void capteur::update(const capteur& sens)
	{
		update(sens.m_traffic, sens.m_lastUpdate);
	}

	void capteur::ShowTimeDistribution() const
	{
		auto total = m_duree_noir + m_duree_orange + m_duree_rouge + m_duree_vert;
		std::cout << traffic::vert << " " << static_cast<int>(100 * m_duree_vert / total) << "%";
		std::cout << traffic::rouge << " " << static_cast<int>(100 * m_duree_rouge / total) << "%";
		std::cout << traffic::orange << " " << static_cast<int>(100 * m_duree_orange / total) << "%";
		std::cout << traffic::noir << " " << static_cast<int>(100 * m_duree_noir / total) << "%";
	}

	capteur::traffic capteur::getTraffic() const
	{
		return m_traffic;
	}

	capteur::ID_t capteur::getID() const
	{
		return m_id;
	}

	timestamp capteur::getLastTimestamp() const
	{
		return m_lastUpdate;
	}

	inline bool operator==(const timestamp& lhs, const timestamp& rhs)
	{
		return lhs.year == rhs.year &&
			lhs.month == rhs.month &&
			lhs.day == rhs.day &&
			lhs.d7 == rhs.d7 &&
			lhs.hour == rhs.hour &&
			lhs.min == rhs.min;
		//return std::make_tuple(lhs.year, lhs.month, lhs.day, lhs.d7, lhs.hour, lhs.min) == std::make_tuple(rhs.year, rhs.month, rhs.day, rhs.d7, rhs.hour, rhs.min);
	}

	inline bool operator!=(const timestamp& lhs, const timestamp& rhs) { return !(lhs == rhs); }

	inline std::ostream& operator<<(std::ostream& os, const timestamp& ts)
	{
		os << ts.year << " " << ts.month << " " << ts.day << " " << ts.d7 << " " << ts.hour << " " << ts.min;
		return os;
	}

	inline std::istream& operator>>(std::istream& is, timestamp& ts)
	{
		is >> ts.year >> ts.month >> ts.day >> ts.d7 >> ts.hour >> ts.min;
		return is;
	}

	inline std::istream& operator>>(std::istream& is, capteur::traffic& e)
	{
		auto val = static_cast<char>(capteur::traffic::noir);
		is >> val;
		e = static_cast<capteur::traffic>(val);
		return is;
	}

	inline std::ostream& operator<<(std::ostream& os, const capteur::traffic& e)
	{
		os << static_cast<char>(e);
		return os;
	}
}

