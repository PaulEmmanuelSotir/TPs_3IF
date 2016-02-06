#include "rectangle.h"

#include <string>

#include "Utils.h"
#include "optional.h"

namespace TP4
{
	std::experimental::optional<Rectangle> make_rectangle(const Point top_left_corner, const Point bottom_right_corner)
	{
		if (top_left_corner.first >= bottom_right_corner.first || top_left_corner.second <= bottom_right_corner.second)
			return std::experimental::nullopt;
		return std::experimental::optional<Rectangle>(Rectangle(std::move(top_left_corner), std::move(bottom_right_corner)));
	}

	Rectangle Move(const Rectangle& shape, coord_t dx, coord_t dy)
	{
		const Point top_left{ shape.top_left_corner.first + dx, shape.top_left_corner.second + dy };
		const Point bottom_right{ shape.bottom_right_corner.first + dx,  shape.bottom_right_corner.second + dy };

		return Rectangle(std::move(top_left), std::move(bottom_right));
	}

	bool Is_contained(const Rectangle& shape, Point point)
	{
		auto x = point.first;
		auto y = point.second;

		return x >= shape.Get_top_left_corner().first 
			&& x <= shape.Get_bottom_right_corner().first
			&& y <= shape.Get_top_left_corner().second
			&& y >= shape.Get_bottom_right_corner().second;
	}

	std::ostream& operator<<(std::ostream& flux, const Rectangle& rect)
	{
		flux << "{ (" << rect.top_left_corner.first << ", " << rect.top_left_corner.first << "); (" << rect.bottom_right_corner.first << ", " << rect.bottom_right_corner.second << ") }";
		return flux;
	}

	Rectangle::Rectangle(const Point&& top_left_corner, const Point&& bottom_right_corner)
		: top_left_corner(std::move(top_left_corner)), bottom_right_corner(std::move(bottom_right_corner))
	{ }
}
