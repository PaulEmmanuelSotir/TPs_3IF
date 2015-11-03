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

		time_t year = 0;
		time_t month = 1;
		time_t day = 1;
		time_t d7 = 1;
		time_t hour = 0;
		time_t min = 0;
	};
	const timestamp JESUS_BIRTH_DATE = TP2::timestamp();

	class capteur
	{
	public:
		using ID_t = unsigned long;

		enum class traffic : char { vert = 'V', rouge = 'J', orange = 'R', noir = 'N' };

		capteur() = default;
		capteur(ID_t id, traffic etat, timestamp t);

		void update(traffic etat, timestamp t);
		void update(const capteur& sens);

		void ShowTimeDistribution() const;

		traffic getTraffic() const;
		ID_t getID() const;
		timestamp getLastTimestamp() const;

	protected:
		ID_t m_id = 0;
		traffic m_traffic = traffic::vert;
		timestamp m_lastUpdate = JESUS_BIRTH_DATE;
		unsigned long m_duree_vert = 0;
		unsigned long m_duree_rouge = 0;
		unsigned long m_duree_orange = 0;
		unsigned long m_duree_noir = 0;
	};

	bool operator==(const timestamp& lhs, const timestamp& rhs);
	bool operator!=(const timestamp& lhs, const timestamp& rhs);
	std::ostream& operator<<(std::ostream& os, const timestamp& ts);
	std::istream& operator>>(std::istream& is, timestamp& ts);
	std::istream& operator>>(std::istream& is, capteur::traffic& e);
	std::ostream& operator<<(std::ostream& os, const capteur::traffic& e);
}
