#pragma once

#include <iostream>

namespace TP2
{
	struct capteur
	{
	public:
		using sens_t = uint32_t;
		enum class traffic : char { vert = 'V', rouge = 'J', orange = 'R', noir = 'N' };

	private:
		struct state_count
		{
			state_count() : count(0) { };
			sens_t count : 25;	// (0 - 33 554 432)	// There is a maximum of 20 000 000 events 
		};

	public:
		capteur();
		capteur(sens_t id, sens_t d7, sens_t hour, sens_t min, traffic state);

		void update(sens_t id, sens_t d7, sens_t hour, sens_t min, traffic state);
		void show_time_distribution() const;
		sens_t get_id() const;
		sens_t get_d7() const;
		sens_t get_hour() const;
		sens_t get_min() const;

	private:
		static inline size_t capteur::to_size_t(traffic state);

		static const size_t TRAFFIC_CARDINALITY = 4;

		sens_t m_id : 18;	// (0 - 262144)
		sens_t m_d7 : 3;	// (0 - 7)
		sens_t m_hour : 5;	// (0 - 31)
		sens_t m_min : 6;	// (0 - 63)

		state_count m_taffic_counts[TRAFFIC_CARDINALITY];

		//----...

		friend bool operator==(const capteur& lhs, const capteur& rhs);
		friend bool operator!=(const capteur& lhs, const capteur& rhs);
		friend bool operator<(const capteur& lhs, const capteur& rhs);
		friend bool operator>(const capteur& lhs, const capteur& rhs);
		friend bool operator<=(const capteur& lhs, const capteur& rhs);
		friend bool operator>=(const capteur& lhs, const capteur& rhs);
	};

	std::ostream& operator<<(std::ostream& os, const capteur::traffic& state);
	std::istream& operator>>(std::istream& is, capteur::traffic& state);
}
