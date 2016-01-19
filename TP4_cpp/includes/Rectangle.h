/*********************************************************************************
									Rectangle
									---------
*********************************************************************************/

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <ostream>

#include "IShape.h"
#include "Utils.h"

//! \namespace TP4
//! espace de nommage regroupant le code crée pour le TP4 de C++
namespace TP4
{
	class Rectangle : public IShape
	{
	public:
		~Rectangle() override = default;

		void Move(coord_t dx, coord_t dy) override;
		bool Is_contained(const Point& point) const override;

		void Serialize_to(const std::ostream& output_stream) const override;
		void Deserialize_from(const std::istream& input_stream) override;

	protected:
		Point m_top_left_corner = { 0U, 1U };
		Point m_bottom_right_corner = { 1U, 0U };

		Rectangle(std::string&& name, Point&& top_left_corner, Point&& bottom_right_corner);
		friend std::unique_ptr<Rectangle> make_rectangle(std::string name, Point top_left_corner, Point bottom_right_corner);
	};

	std::unique_ptr<Rectangle> make_rectangle(std::string name, Point top_left_corner, Point bottom_right_corner);
}

#endif // RECTANGLE_H
