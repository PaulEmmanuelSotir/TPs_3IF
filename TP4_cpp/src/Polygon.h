/*********************************************************************************
										Polygon
										-------
*********************************************************************************/

#ifndef POLYGON_H
#define POLYGON_H

#include <string>

#include "Utils.h"
#include "Command.h"
#include "optional.h"

//! \namespace TP4
//! espace de nommage regroupant le code crée pour le TP4 de C++
namespace TP4
{
	//----------------------------------------------------------------------------
	//! Structure représentant un polygone convexe.
	//! La structure est serialisable grâce à boost::serialization.
	//----------------------------------------------------------------------------
	struct Polygon
	{
		Polygon() = default;
		Polygon& operator=(const Polygon&) = delete;
	
		std::vector<Point> Get_vertices() const
		{
			return vertices;
		}

	private:
		explicit Polygon(const std::vector<Point>&& vertices);

		std::vector<Point> vertices;

		friend std::ostream& operator<<(std::ostream &flux, const Polygon& polygone);

		friend std::experimental::optional<Polygon> make_polygon(const std::vector<Point> vertices);

		friend Polygon Move(const Polygon& shape, coord_t dx, coord_t dy);
		friend bool Is_contained(const Polygon& shape, Point point);

		friend class boost::serialization::access;
		
		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::make_nvp("vertices", vertices);
		}
	};

	Polygon Move(const Polygon& shape, coord_t dx, coord_t dy);
	bool Is_contained(const Polygon& shape, Point point);

	std::experimental::optional<Polygon> make_polygon(const std::vector<Point> vertices);
}

#endif // !POLYGON_H