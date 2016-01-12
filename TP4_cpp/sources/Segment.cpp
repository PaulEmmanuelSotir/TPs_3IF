#include <string>

#include "Utils.h"
#include "Segment.h"


TP4::Segment::Segment(std::string name, Point first_point, Point second_point)
	:name(name),first_point(first_point), second_point(second_point){}

void TP4::Segment::Move(double dx, double dy)
{
	this->first_point.first += dx;
	this->first_point.second += dy;	
	
	this->second_point.first += dx;
	this->second_point.second += dy;		
}

bool TP4::Segment::IsContained(double x, double y)
{
	bool is_contained = false;
	double cross_product = (second_point.first-first_point.first)*(y-first_point.second)-(x-first_point.first)*(second_point.second-first_point.second);

	if (cross_product == 0)
	{
		double produit_scalaire_un = (second_point.first-first_point.first)*(x-first_point.first) + (second_point.second-first_point.second)*(y-first_point.second);
		double produit_scalaire_deux = (second_point.first-first_point.first)*(second_point.first-first_point.first) + (second_point.second-first_point.second)*(second_point.second-first_point.second);

		if (produit_scalaire_un >=0 && produit_scalaire_un < produit_scalaire_deux)
		{
			is_contained = true;
		}
	}

	return is_contained;
}

void TP4::Segment::SerializeTo(const std::ostream& output_stream)
{

}

void TP4::Segment::DeserializeFrom(const std::ostream& output_stream)
{

}

