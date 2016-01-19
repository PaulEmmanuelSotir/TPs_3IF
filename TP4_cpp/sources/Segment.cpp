#include <string>

#include "Utils.h"
#include "Segment.h"
#include <Command.h>

namespace TP4
{
	std::unique_ptr<Segment> make_segment(std::string name, Point first_point, Point second_point)
	{
		if (name.empty() || first_point == second_point)
			return nullptr;
		return std::unique_ptr<Segment>(new Segment(std::move(name), std::move(first_point), std::move(second_point)));
	}

	void Segment::Move(coord_t dx, coord_t dy)
	{
		this->m_first_point.first += dx;
		this->m_first_point.second += dy;

		this->m_second_point.first += dx;
		this->m_second_point.second += dy;
	}

	bool Segment::Is_contained(const Point& point) const
	{
		double cross_product = (m_second_point.first - m_first_point.first)*(point.second - m_first_point.second) - (point.first - m_first_point.first)*(m_second_point.second - m_first_point.second);

		if (cross_product == 0)
		{
			double produit_scalaire_un = (m_second_point.first - m_first_point.first)*(point.first - m_first_point.first) + (m_second_point.second - m_first_point.second)*(point.second - m_first_point.second);
			double produit_scalaire_deux = (m_second_point.first - m_first_point.first)*(m_second_point.first - m_first_point.first) + (m_second_point.second - m_first_point.second)*(m_second_point.second - m_first_point.second);

			if (produit_scalaire_un >= 0 && produit_scalaire_un < produit_scalaire_deux)
				return true;
		}

		return false;
	}

	/*void Segment::Serialize_to(const std::ostream& output_stream) const
	{

	}

	void Segment::Deserialize_from(const std::istream& input_stream)
	{

	}*/

	Segment::Segment(std::string&& name, Point&& first_point, Point&& second_point)
		: IShape(std::move(name)), m_first_point(std::move(first_point)), m_second_point(std::move(second_point))
	{ }
}
