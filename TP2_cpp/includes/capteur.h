#pragma once

#include <iostream>

namespace TP2
{
	struct timestamp
	{
	public:
		using time_t = unsigned int;

		timestamp() = default;
		timestamp(time_t year, time_t month, time_t day, time_t d7, time_t hour, time_t min);

		time_t year = 2015;
		time_t month = 1;
		time_t day = 1;
		time_t d7 = 1;
		time_t hour = 0;
		time_t min = 0;
	};

	std::ostream& operator<<(std::ostream& os, const timestamp& ts)
	{
		os << ts.year << " " << ts.month << " " << ts.day << " " << ts.d7 << " " << ts.hour << " " << ts.min;
		return os;
	}

	std::istream& operator>>(std::istream& is, timestamp& ts)
	{
		is >> ts.year >> " " >> ts.month >> " " >> ts.day >> " " >> ts.d7 >> " " >> ts.hour >> " " >> ts.min;
		return is;
	}

	class capteur
	{
	public:
		using ID_t = unsigned long;

		enum class traffic : char { vert = 'V', rouge = 'J', orange = 'R', noir = 'N' };

		capteur(ID_t id, traffic etat, timestamp t);

		void update(traffic etat, timestamp t);

		void ShowTimeDistribution();
	
		ID_t getID();

	protected:
		ID_t m_id;
		traffic m_traffic;
		timestamp m_lastUpdate;
		unsigned long m_duree_vert = 0;
		unsigned long m_duree_rouge = 0;
		unsigned long m_duree_orange = 0;
		unsigned long m_duree_noir = 0;
	};

	std::istream& operator>>(std::istream& is, capteur::traffic& e)
	{
		auto val = static_cast<char>(capteur::traffic::noir);
		is >> val;
		e = static_cast<capteur::traffic>(val);
		return is;
	}

	std::ostream& operator<<(std::ostream& os, const capteur::traffic& e)
	{
		os << static_cast<char>(e);
		return os;
	}
}
