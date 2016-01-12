#ifndef SEGMENT_H
#define SEGMENT_H

#include <ostream>
#include <String>

#include "Utils.h"
#include "Forme.h"

namespace TP4 
{

	struct Segment : Forme
	{	
		
		Segment() = default;
		Segment(String name, Point first_point, Point second_point);
		virtual ~Segment() = default;

		void SerializeTo(const std::ostream& output_stream) override;
		void DeserializeFrom(const std::ostream& output_stream) override;

		Point first_point;
		Point second_point;
		String name;
	
	};



}

#endif //SEGMENT_H
