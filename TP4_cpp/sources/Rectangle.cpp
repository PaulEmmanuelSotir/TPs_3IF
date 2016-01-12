
#include "rectangle.h"

TP4::Rectangle::Rectangle(std::string name, Point top_left_corner, Point bottom_right_corner)
	: name(name), top_left_corner(top_left_corner), bottom_right_corner(bottom_right_corner)
{ }

void TP4::Rectangle::Move(double dx, double dy)
{
	this->top_left_corner.first += dx;
	this->top_left_corner.second += dy;	
	
	this->bottom_right_corner.first += dx;
	this->bottom_right_corner.second += dy;		
}

bool TP4::Rectangle::IsContained(double x, double y)
{
    bool is_contained = false;
    
    if (x>=top_left_corner.first && x<=bottom_right_corner.first && y<=top_left_corner.second && y>=bottom_right_corner.second)
    {
        is_contained = true;
    }
    
    return is_contained;
}

void TP4::Rectangle::SerializeTo(const std::ostream& output_stream)
{
	// TODO: generate JSON
}

void TP4::Rectangle::DeserializeFrom(const std::ostream& output_stream)
{
	// TODO: parse JSON
}
