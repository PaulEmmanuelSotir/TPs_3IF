#include "Segment.h"

#include <string>

#include "Utils.h"
#include "Command.h"
#include "optional.h"

namespace TP4
{
	std::experimental::optional<Segment> make_segment(const Point first_point, const Point second_point)
	{
		if (first_point == second_point)
			return std::experimental::nullopt;
		return std::experimental::optional<Segment>(Segment(std::move(first_point), std::move(second_point)));
	}

	Segment Move(const Segment& shape, coord_t dx, coord_t dy)
	{
		const Point first_point{ shape.first_point.first + dx, shape.first_point.second + dy };
		const Point second_point{ shape.second_point.first + dx,  shape.second_point.second + dy };

		return Segment(std::move(first_point), std::move(second_point));
	}

	bool Is_contained(const Segment& shape, Point point)
	{
		// TODO: definir ces opérations dans utils (produit vectoriel et scalaire) ?
		double cross_product =	(shape.second_point.first - shape.first_point.first) * (point.second - shape.first_point.second)
							 -	(point.first - shape.first_point.first) * (shape.second_point.second - shape.first_point.second);

		if (cross_product == 0)
		{
			double scalar_product1 =	(shape.second_point.first - shape.first_point.first) * (point.first - shape.first_point.first)
								   +	(shape.second_point.second - shape.first_point.second) * (point.second - shape.first_point.second);
			
			double scalar_product2 =	(shape.second_point.first - shape.first_point.first) * (shape.second_point.first - shape.first_point.first)
								   +	(shape.second_point.second - shape.first_point.second) * (shape.second_point.second - shape.first_point.second);

			if (scalar_product1 >= 0 && scalar_product1 < scalar_product2)
				return true;
		}

		return false;
	}

	std::ostream& operator<<(std::ostream& flux, const Segment& seg)
	{
		flux << "{ (" << seg.first_point.first << ", " << seg.second_point.first << "); (" << seg.second_point.first << ", " << seg.second_point.second << ") }";
		return flux;
	}

	Segment::Segment(const Point&& first_point, const Point&& second_point)
		: first_point(std::move(first_point)), second_point(std::move(second_point))
	{ }
}
