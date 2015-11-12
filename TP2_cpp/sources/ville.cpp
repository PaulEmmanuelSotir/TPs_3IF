/********************************************************************************************
										ville.cpp
										---------
date                 : 11/2015
copyright            : (C) 2015 by B3311
********************************************************************************************/

//--------------------------------------------------------------------------- Include systeme
#include <iostream>

//------------------------------------------------------------------------- Include personnel
#include "ville.h"
#include "capteur_stat.h"
#include "capteur_event.h"

namespace TP2
{
	//------------------------------------------------------------------------- Constructeurs
	
	ville::ville()
		: m_sensor_stats(32, MAX_IDS_COUNT,
			[](const capteur_stat_with_events& a, const capteur_stat_with_events& b) { return a.first.get_id() == b.first.get_id(); },
			[](const capteur_stat_with_events& a, const capteur_stat_with_events& b) { return a.first.get_id() < b.first.get_id(); })
	{
		for (size_t i = 0; i < DAYS_COUNT; i++)
			for (size_t j = 0; j < HOUR_COUNT; j++)
				m_week_jam_distribution_by_hour[i][j] = pair<unsigned int, unsigned int>(0, 0);
	}

	//-------------------------------------------------------------------- Méthodes publiques

	void ville::add_sensor(capteur_event new_event)
	{
		// Find if this sensor (id) have already been added
		auto sensor_stats_to_find = capteur_stat_with_events(capteur_stat(new_event), vec<capteur_event>(2, MAX_EVENT_COUNT, 
			[](const capteur_event& a, const capteur_event& b) { return a == b; },
			[](const capteur_event& a, const capteur_event& b) { return a < b; } )); // sensor stats with empty (capacity = 2) event vector
		auto id_idx = m_sensor_stats.find(sensor_stats_to_find);

		if (LIKELY(id_idx <= m_sensor_stats.MAX_ALLOCATION_SIZE))
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

	void ville::show_optimal_timestamp(capteur_stat::sensor_t d7, capteur_stat::sensor_t h_start, capteur_stat::sensor_t h_end, const vec<capteur_stat::sensor_t>& seg_ids)
	{
		double minimal_travel_duration = std::numeric_limits<double>::max();
		capteur_stat::sensor_t minimal_travel_start_minute = 0;
		capteur_stat::sensor_t minimal_travel_start_hour = 0;

		vec<vec<capteur_event>> segments_events; // vector of each specified segment's event vector

		if (seg_ids.length() > 0)
		{
			// For each specified segment/sensor, we find and sort its events vector
			for (size_t seg_it = 0; seg_it < seg_ids.length(); ++seg_it)
			{
				// Find find 'capteur_stat_with_events' pair representing the <seg_it>-th segment of the travel
				capteur_stat_with_events* segment = get_sensor_stat_with_events_by_id(seg_ids[seg_it]);
				if (segment == nullptr)
					return; // Specified sensor id haven't been added

				// Sort all events of this segment (sort by their week timestamp)
				auto& seg_events = segment->second;
				seg_events.sort();

				// Add segment's events vector to 'segments_events' vector (to avoid searching them again)
				segments_events.add(seg_events);
			}

			// For each minutes in specified interval, we get the travel duration and find the minimal one
			for (capteur_stat::sensor_t hour = h_start; hour <= h_end; ++hour)
			{
				for (capteur_stat::sensor_t minute = 0; minute < MIN_COUNT; ++minute)
				{
					// Recurse over segments to find travel duration if we start from this minute
					double travel_duration = get_travel_duration(segments_events, seg_ids, 0, d7, hour, minute);

					// Record best travel duration and start timestamp
					if (travel_duration < minimal_travel_duration)
					{
						minimal_travel_duration = travel_duration;
						minimal_travel_start_hour = hour;
						minimal_travel_start_minute = minute;
					}
				}
			}
		}

		// Print results
		std::cout
			<< d7 << " "
			<< minimal_travel_start_hour << " "
			<< minimal_travel_start_minute << " "
			<< static_cast<unsigned int>(minimal_travel_duration + 0.5) << std::endl;
	}

	capteur_stat* ville::get_sensor_stat_by_id(capteur_stat::sensor_t id)
	{
		capteur_stat_with_events* stats_with_events = get_sensor_stat_with_events_by_id(id);

		return (stats_with_events == nullptr ? nullptr : &stats_with_events->first);
	}

	//---------------------------------------------------------------------- Méthodes privées

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

	inline capteur_event::sensor_t ville::travel_duration_of_traffic(traffic state)
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

	double ville::get_travel_duration(const vec<vec<capteur_event>>& segments_events, const vec<capteur_stat::sensor_t>& seg_ids, size_t seg_idx, capteur_stat::sensor_t d7, capteur_stat::sensor_t hour, capteur_stat::sensor_t minute)
	{
		if (seg_idx >= segments_events.length())
			return 0; // end of recursion

		// Correct minute and hour counts if nescessary
		hour += static_cast<unsigned int>(minute / MIN_COUNT);
		minute %= MIN_COUNT;
		d7 += static_cast<unsigned int>(hour / HOUR_COUNT);
		hour %= HOUR_COUNT;
		d7 = (d7 - 1) % DAYS_COUNT + 1;

		double travel_duration = 0.0;
		const vec<capteur_event>& seg_events = segments_events[seg_idx]; // current segement's events

		// TODO: find the first one
		// Find if we have events for this minute
		auto event_idx = seg_events.find(capteur_event(seg_ids[seg_idx], d7, hour, minute));

		if (event_idx <= seg_events.MAX_ALLOCATION_SIZE)
			// Find travel duration by taking the mean of all events traffic with the same d7, hour and minute (and id)
		{
			unsigned int count = 0;
			double duration_mean = 0;
			capteur_event event = seg_events[event_idx];
			capteur_event previous_event;
			do
			{
				// add event's travel duration to the mean
				duration_mean += static_cast<double>(travel_duration_of_traffic(event.get_traffic()));
				count++;

				if (UNLIKELY(++event_idx >= seg_events.length()))
					break; // no more events in segment events vector

				event = seg_events[event_idx];
				previous_event = event;
			} while (event == previous_event); // while next events in segment_events are in the same minute

			travel_duration += duration_mean / count;
		}
		else
			travel_duration += travel_duration_of_traffic(traffic::noir); // we suppose unkown traffic to be 'traffic::noir'

		return travel_duration + get_travel_duration(segments_events, seg_ids, seg_idx + 1, d7, hour, minute + static_cast<capteur_stat::sensor_t>(travel_duration + 0.5));
	}
}