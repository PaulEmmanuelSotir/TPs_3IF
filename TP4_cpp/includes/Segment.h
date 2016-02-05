/*********************************************************************************
									Segment
									-------
*********************************************************************************/

#ifndef SEGMENT_H
#define SEGMENT_H

#include <string>

#include "Utils.h"
#include "Command.h"
#include "optional.h"

//! \namespace TP4
//! espace de nommage regroupant le code crée pour le TP4 de C++
namespace TP4
{

	//----------------------------------------------------------------------------
	//! Structure représentant un segment constitué de deux points distincts.
	//! La structure est serialisable grâce à boost::serialization.
	//----------------------------------------------------------------------------
	struct Segment
	{
		Segment() = default;

		Point Get_first_point() const
		{
			return first_point;
		}

		Point Get_second_point() const
		{
			return second_point;
		}

	private:
		Segment(const Point&& first_point, const Point&& second_point);

		Point first_point;
		Point second_point;

		friend std::experimental::optional<Segment> make_segment(const Point first_point, const Point second_point);

		friend Segment Move(const Segment& shape, coord_t dx, coord_t dy);
		friend bool Is_contained(const Segment& shape, Point point);

		friend class boost::serialization::access;

		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::make_nvp("first_point", first_point)
				& boost::serialization::make_nvp("second_point", second_point);
		}
	};

	Segment Move(const Segment& shape, coord_t dx, coord_t dy);
	bool Is_contained(const Segment& shape, Point point);

	std::experimental::optional<Segment> make_segment(const Point first_point, const Point second_point);
}

#endif //SEGMENT_H
