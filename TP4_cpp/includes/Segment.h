#ifndef SEGMENT_H
#define SEGMENT_H

#include <ostream>
#include <string>

#include "Utils.h"
#include "Forme.h"

namespace TP4 
{

	struct Segment : Forme
	{	
		
		Segment() = default;
		Segment(std::string name, Point first_point, Point second_point);
		virtual ~Segment() = default;

		void Move(double dx, double dy) override;
		bool IsContained(double x, double y) override;

		void SerializeTo(const std::ostream& output_stream) override;
		void DeserializeFrom(const std::ostream& output_stream) override;

		std::string name;
		Point first_point;
		Point second_point;
		
	
	};



}

#endif //SEGMENT_H
