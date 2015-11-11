#include <iostream>

#include "ville.h"
#include "capteur_stat.h"
#include "capteur_event.h"

namespace TP2
{
	ville::ville()
		: m_sensor_stats(32, MAX_IDS_COUNT)
	{
		for (size_t i = 0; i < DAYS_COUNT; i++)
			for (size_t j = 0; j < HOUR_COUNT; j++)
				m_week_jam_distribution_by_hour[i][j] = pair<unsigned int, unsigned int>(0, 0);
	}

	void ville::add_sensor(capteur_event new_event)
	{
		// Find if this sensor (id) have already been added
		auto sensor_stats_to_find = capteur_stat_with_events(capteur_stat(new_event), vec<capteur_event>(2, MAX_EVENT_COUNT)); // sensor stats with empty (capacity = 2) event vector
		auto id_idx = m_sensor_stats.find(sensor_stats_to_find);

		if (id_idx <= m_sensor_stats.MAX_ALLOCATION_SIZE)	// TODO: LIKELY
		// We already know this sensor, we update its statistics...
		{
			auto& sens_stat_with_events = m_sensor_stats[id_idx];

			// Update sensor's global statistics
			sens_stat_with_events.first.update(new_event);

			// Add event to sensor's event vector
			sens_stat_with_events.second.add(new_event);
		}
		else
			// We have a new sensor ID
		{
			// Add new/first event to sensor's event vector
			sensor_stats_to_find.second.add(new_event);

			m_sensor_stats.add(sensor_stats_to_find);
			m_sensor_stats.sort(); // sort m_sensor_stats vector using ids
		}

		// Update town's global statistics
		update_global_week_stats(new_event);
	}

	void ville::show_day_traffic_by_hour(capteur_stat::sensor_t d7) const
	{
		for (size_t i = 0; i < HOUR_COUNT; i++)
		{
			const auto& stat = m_week_jam_distribution_by_hour[d7][i];
			std::cout
				<< d7 << " "
				<< i << " "
				<< (stat.second == 0 ? 0 : static_cast<unsigned int>((100.0 * stat.first) / stat.second + 0.5)) << "%" << std::endl;
		}
	}

	void ville::show_day_traffic(capteur_stat::sensor_t d7) const
	{
		const auto& stat = m_week_traffic_distribution_by_day[d7];

		if (stat.total_count != 0)
			std::cout
			<< traffic::vert << " " << static_cast<int>((100.0 * stat.green_count) / stat.total_count + 0.5) << "%" << std::endl
			<< traffic::rouge << " " << static_cast<int>((100.0 * stat.red_count) / stat.total_count + 0.5) << "%" << std::endl
			<< traffic::orange << " " << static_cast<int>((100.0 * stat.orange_count) / stat.total_count + 0.5) << "%" << std::endl
			<< traffic::noir << " " << static_cast<int>((100.0 * stat.dark_count) / stat.total_count + 0.5) << "%" << std::endl;
		else
			std::cout
			<< traffic::vert << " 0%" << std::endl
			<< traffic::rouge << " 0%" << std::endl
			<< traffic::orange << " 0%" << std::endl
			<< traffic::noir << " 0%" << std::endl;
	}

	inline capteur_event::sensor_t ville::travel_duration(traffic state)
	{
		switch (state)
		{
		case traffic::vert: return 1;
		case traffic::rouge: return 2;
		case traffic::orange: return 4;
		case traffic::noir: return 10;
		}
		return 0; // impossible
	};

	inline capteur_event findNextRegisteredEvent()
	{
		return capteur_event();
	}

	inline ville::capteur_stat_with_events* ville::get_sensor_stat_with_events_by_id(capteur_stat::sensor_t id)
	{
		// Create dummy 'capteur_stat_with_events' object with specified id
		capteur_event dummy_sens_event;
		dummy_sens_event.id = id;
		auto dummy_sensor_stat_to_find = capteur_stat_with_events(capteur_stat(dummy_sens_event), vec<capteur_event>());

		// find it in 'm_sensor_stats'
		auto sensor_stat_idx = m_sensor_stats.find(dummy_sensor_stat_to_find);

		if (sensor_stat_idx > m_sensor_stats.MAX_ALLOCATION_SIZE)
			return nullptr; // Specified sensor id haven't been added

		auto& sensor_stat = m_sensor_stats[sensor_stat_idx];
		return &sensor_stat;
	}

	void ville::show_optimal_timestamp(capteur_stat::sensor_t d7, capteur_stat::sensor_t h_start, capteur_stat::sensor_t h_end, const vec<capteur_stat::sensor_t>& seg_ids)
	{
	/*	double travel_duration = 0.0;
		double minimal_travel_duration = std::numeric_limits<double>::max();
		capteur_event minimal_travel_start_timestamp;

		using ts_t = capteur_stat::sensor_t;
		if (seg_ids.length() > 0)
		{
			// Find first segment in m_sensor_stats
			capteur_stat_with_events* segment = get_sensor_stat_with_events_by_id(seg_ids[0]);
			if (segment == nullptr)
				return; // Specified sensor id haven't been added

			// TODO: sort all segment_events vectors
			// Sort all events of this sensors (sort by their week timestamp)
			auto& segment_events = segment->second;
			segment_events.sort();

			// For each minutes in specified interval, we get the travel duration and find the minimal one
			for (ts_t hour = h_start; hour <= h_end; ++hour)
			{
				for (ts_t minute = 0; minute < MIN_COUNT; ++minute)
				{
					// Recurse over segments to find travel duration if we start from this minute
					double travel_duration = get_travel_duration(seg_ids, 0, d7, hour, minute);

					// Record best travel duration and start timestamp
					if (travel_duration < minimal_travel_duration)
					{
						minimal_travel_duration = travel_duration;
						minimal_travel_start_timestamp = capteur_event(segment->first.get_id(), d7, hour, minute);
					}
				}
			}
		}

		// Print results
		std::cout 
			<< d7 << " "
			<< minimal_travel_start_timestamp.hour << " "
			<< minimal_travel_start_timestamp.min << " "
			<< static_cast<unsigned int>(minimal_travel_duration + 0.5) << std::endl;*/
	}



	double ville::get_travel_duration(const vec<capteur_stat::sensor_t>& seg_ids, size_t idx, capteur_stat::sensor_t d7, capteur_stat::sensor_t hour, capteur_stat::sensor_t minute)
	{
	/*	if (idx >= seg_ids.length())
			return 0; // end of recursion

		// Correct minute and hour counts if nescessary
		hour += static_cast<unsigned int>(minute / MIN_COUNT);
		minute %= MIN_COUNT;
		d7 += static_cast<unsigned int>(hour / HOUR_COUNT);
		hour %= HOUR_COUNT;
		d7 = (d7 - 1) % DAYS_COUNT + 1;

		double travel_duration = 0.0;

		// TODO: find the first one
		// Find if we have events for this minute
		auto event_idx = segment_events.find(capteur_event(seg_ids[idx], d7, hour, minute));

		if (event_idx <= segment_events.MAX_ALLOCATION_SIZE)
		{
			capteur_event seg_event = segment_events[event_idx];

			if (segment_events.length() > ++event_idx)
			{
				// Get the travel duration mean of all events of this minute
				unsigned int count = 1;
				double duration_mean = 0;
				auto next_seg_event = segment_events[++event_idx];
				while (next_seg_event == seg_event) // while next events in segment_events are in the same minute
				{
					duration_mean += static_cast<double>(travel_duration(next_seg_event.get_traffic()));
					count++;
					if (segment_events.length() > ++event_idx)
						next_seg_event = segment_events[event_idx];
				}
				travel_duration += duration_mean / count;
			}
			else
				travel_duration += static_cast<double>(travel_duration(seg_event.get_traffic()));
		}
		else
			travel_duration += travel_duration(traffic::noir); // we suppose unkown traffic to be 'traffic::noir'

		return travel_duration + get_remaining_travel_duration(seg_ids, idx + 1, d7, hour, minute + travel_duration);*/
		return 0;
	}

	capteur_stat* ville::get_sensor_stat_by_id(capteur_stat::sensor_t id)
	{
		capteur_stat_with_events* stats_with_events = get_sensor_stat_with_events_by_id(id);
		
		return (stats_with_events == nullptr ? nullptr : &stats_with_events->first);
	}

	// TODO:
	//----op...

	bool operator==(const ville::capteur_stat_with_events& lhs, const ville::capteur_stat_with_events& rhs) { return lhs.first.get_id() == rhs.first.get_id(); }
	bool operator!=(const ville::capteur_stat_with_events& lhs, const ville::capteur_stat_with_events& rhs) { return !(lhs == rhs); }

	bool operator<(const ville::capteur_stat_with_events& lhs, const ville::capteur_stat_with_events& rhs) { return lhs.first.get_id() < rhs.first.get_id(); }

	bool operator>(const ville::capteur_stat_with_events& lhs, const ville::capteur_stat_with_events& rhs) { return rhs < lhs; }
	bool operator<=(const ville::capteur_stat_with_events& lhs, const ville::capteur_stat_with_events& rhs) { return !(rhs < lhs); }
	bool operator>=(const ville::capteur_stat_with_events& lhs, const ville::capteur_stat_with_events& rhs) { return !(lhs < rhs); }

	// TODO:
	//----prive...

	void ville::update_global_week_stats(capteur_event new_event)
	{
		auto& jam_stat = m_week_jam_distribution_by_hour[new_event.d7][new_event.hour];
		jam_stat.second++;

		auto& stat = m_week_traffic_distribution_by_day[new_event.d7];
		stat.total_count++;

		switch (new_event.get_traffic())
		{
		case traffic::noir:
			jam_stat.first++;
			stat.dark_count++;
			break;
		case traffic::orange:
			jam_stat.first++;
			stat.orange_count++;
			break;
		case traffic::rouge:
			stat.red_count++;
			break;
		case traffic::vert:
			stat.green_count++;
			break;
		}
	}
}