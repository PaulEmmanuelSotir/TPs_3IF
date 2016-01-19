/*********************************************************************************
										Polygon
										-------
*********************************************************************************/

#ifndef POLYGON_H
#define POLYGON_H

#include <ostream>
#include <vector>
#include <string>

#include "IShape.h"
#include "Utils.h"

//! \namespace TP4
//! espace de nommage regroupant le code cr»e pour le TP4 de C++
namespace TP4
{
	class Polygon : public IShape
	{
	public:
		~Polygon() override = default;

		void Move(coord_t dx, coord_t dy) override;
		bool Is_contained(const Point& point) const override;

		//void Serialize_to(const std::ostream& output_stream) const override;
		//void Deserialize_from(const std::istream& input_stream) override;

	protected:
		std::vector<Point> m_vertices = { { 0U, 0U }, { 2U, 0U }, { 1U, 2U } };

		Polygon(std::string&& name, std::vector<Point>&& vertices);

		template<class Archive>
		void serialize(Archive & ar, const unsigned int version);

		friend class boost::serialization::access;
		friend std::unique_ptr<Polygon> make_polygon(std::string name, std::vector<Point> vertices);
	};

	std::unique_ptr<Polygon> make_polygon(std::string name, std::vector<Point> vertices);

	template<class Archive>
	void Polygon::serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<IShape>(*this);
		ar & m_vertices;
	}
}

#endif // POLYGON_H