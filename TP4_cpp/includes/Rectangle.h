/*********************************************************************************
									Rectangle
									---------
*********************************************************************************/

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <ostream>

#include "Forme.h"
#include "Utils.h"

//! \namespace TP4
//! espace de nommage regroupant le code crée pour le TP4 de C++
namespace TP4
{
	struct Rectangle : Forme
	{
		Rectangle() = default;
		Rectangle(std::string name, Point top_left_corner, Point bottom_right_corner);
		virtual ~Rectangle() = default;

		void SerializeTo(const std::ostream& output_stream) override;
		void DeserializeFrom(const std::ostream& output_stream) override;

		Point top_left_corner;
		Point bottom_right_corner;
	};
}

#endif // RECTANGLE_H
