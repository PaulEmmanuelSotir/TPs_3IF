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

	void capteur::ShowTimeDistribution()
	{
		auto total = m_duree_noir + m_duree_orange + m_duree_rouge + m_duree_vert;
		std::cout << static_cast<char>(traffic::vert) << " " << static_cast<int>(100 * m_duree_vert / total) << "%";
		std::cout << static_cast<char>(traffic::rouge) << " " << static_cast<int>(100 * m_duree_rouge / total) << "%";
		std::cout << static_cast<char>(traffic::orange) << " " << static_cast<int>(100 * m_duree_orange / total) << "%";
		std::cout << static_cast<char>(traffic::noir) << " " << static_cast<int>(100 * m_duree_noir / total) << "%";
	}

	capteur::ID_t capteur::getID()
	{
		return m_id;
	}
}

