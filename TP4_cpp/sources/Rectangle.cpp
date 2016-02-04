#include "rectangle.h"

#include <string>
#include <iostream>

#include "Polygon.h"

namespace TP4
{
	std::unique_ptr<Rectangle> make_rectangle(name_t name, Point top_left_corner, Point bottom_right_corner)
	{
		if (name.empty() || top_left_corner.first >= bottom_right_corner.first || top_left_corner.second <= bottom_right_corner.second)
			return nullptr;
		return std::unique_ptr<Rectangle>(new Rectangle(std::move(name), std::move(top_left_corner), std::move(bottom_right_corner)));
	}

	void Rectangle::Move(coord_t dx, coord_t dy)
	{
		m_top_left_corner.first += dx;
		m_top_left_corner.second += dy;

		m_bottom_right_corner.first += dx;
		m_bottom_right_corner.second += dy;
	}

	bool Rectangle::Is_contained(const Point& point) const
	{
		auto x = point.first;
		auto y = point.second;

		return (x >= m_top_left_corner.first && x <= m_bottom_right_corner.first && y <= m_top_left_corner.second && y >= m_bottom_right_corner.second);
	}

	Rectangle::Rectangle(std::string&& name, Point&& top_left_corner, Point&& bottom_right_corner)
		: IShape(std::move(name)), m_top_left_corner(std::move(top_left_corner)), m_bottom_right_corner(std::move(bottom_right_corner))
	{ }
}
