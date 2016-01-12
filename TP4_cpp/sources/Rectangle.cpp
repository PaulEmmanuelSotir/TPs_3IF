
#include "rectangle.h"

TP4::Rectangle::Rectangle(std::string name, Point top_left_corner, Point bottom_right_corner)
	: top_left_corner(top_left_corner), bottom_right_corner(bottom_right_corner)
{ }

void TP4::Rectangle::SerializeTo(const std::ostream& output_stream)
{
	// TODO: generate JSON
}

void TP4::Rectangle::DeserializeFrom(const std::ostream& output_stream)
{
	// TODO: parse JSON
}
