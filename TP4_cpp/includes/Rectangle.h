/*********************************************************************************
									Rectangle
									---------
*********************************************************************************/

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <string>

#include "Utils.h"
#include "Command.h"
#include "optional.h"

//! \namespace TP4
//! espace de nommage regroupant le code crée pour le TP4 de C++
namespace TP4
{
	//----------------------------------------------------------------------------
	//! Structure représentant un rectangle définit à partir de son coin superieur 
	//! gauche et de son coin inferieur bas. La structure est serialisable grâce à 
	//! boost::serialization.
	//----------------------------------------------------------------------------
	struct Rectangle
	{
		Rectangle() = default;

		Point Get_top_left_corner() const
		{
			return top_left_corner;
		}

		Point Get_bottom_right_corner() const
		{
			return bottom_right_corner;
		}

	private:
		Rectangle(const Point&& top_left_corner, const Point&& bottom_right_corner);

		Point top_left_corner;
		Point bottom_right_corner;

		friend std::experimental::optional<Rectangle> make_rectangle(const Point top_left_corner, const Point bottom_right_corner);
		
		friend Rectangle Move(const Rectangle& shape, coord_t dx, coord_t dy);

		friend class boost::serialization::access;

		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::make_nvp("top_left_corner", top_left_corner)
				& boost::serialization::make_nvp("bottom_right_corner", bottom_right_corner);
		}
	};

	Rectangle Move(const Rectangle& shape, coord_t dx, coord_t dy);
	bool Is_contained(const Rectangle& shape, Point point);

	std::experimental::optional<Rectangle> make_rectangle(const Point top_left_corner, const Point bottom_right_corner);
}

#endif // !RECTANGLE_H
