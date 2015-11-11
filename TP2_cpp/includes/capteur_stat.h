#pragma once

#include "capteur_event.h"

namespace TP2
{
	struct capteur_stat
	{
	public:
		using sensor_t = capteur_event::sensor_t;

		capteur_stat() = default;
		capteur_stat(capteur_event initial_event);
		capteur_stat(const capteur_stat& other);
		capteur_stat(capteur_stat&& other) noexcept;

		void update(capteur_event new_event);
		void show_time_distribution() const;
		sensor_t get_id() const;
		sensor_t get_d7() const;
		sensor_t get_hour() const;
		sensor_t get_min() const;

	private:
		sensor_t m_taffic_counts[capteur_event::TRAFFIC_CARDINALITY] = { 0, 0, 0, 0 };
		capteur_event m_stat_timestamp;

		static inline size_t to_taffic_count_idx(traffic state);
		//----...
	public:
		const capteur_stat& operator=(capteur_stat other);

		friend bool operator==(const capteur_stat& lhs, const capteur_stat& rhs);
		friend bool operator!=(const capteur_stat& lhs, const capteur_stat& rhs);

		friend bool operator<(const capteur_stat& lhs, const capteur_stat& rhs);
		friend bool operator>(const capteur_stat& lhs, const capteur_stat& rhs);
		friend bool operator<=(const capteur_stat& lhs, const capteur_stat& rhs);
		friend bool operator>=(const capteur_stat& lhs, const capteur_stat& rhs);

		friend void swap(capteur_stat& lhs, capteur_stat& rhs) noexcept;
	};
}
