//
//  Polygone.cpp
//  
//
//  Created by Victoire Chapelle on 14/01/2016.
//
//

#include <math.h>
#include <string>
#include <vector>

#include "Polygon.h"

namespace TP4
{
	std::unique_ptr<Polygon> make_polygon(std::string name, std::vector<Point> vertices)
	{
		bool is_convex = false;
		// TODO: vérifier que le polygone est convexe
		if (name.empty() || !is_convex)
			return nullptr;

		return std::unique_ptr<Polygon>(new Polygon(std::move(name), std::move(vertices)));
	}

	void Polygon::Move(coord_t dx, coord_t dy)
	{
		// TODO: peut être garder un offset (plus rapide que d'iterer sur les sommets (dans ce cas il faut faire une classe plutôt qu'une struct))
		for (Point& p : m_vertices)
		{
			p.first += dx;
			p.second += dy;
		}
	}

	bool Polygon::Is_contained(const Point& point) const
	{
		coord_t sum = 0;
		auto x = point.first;
		auto y = point.second;

		// Calcul de la somme des cosinus que font les angles entre les sommets consécutifs et le point
		for (size_t i = 0; i < m_vertices.size() - 1; ++i)
		{
			double length_1 = sqrt((m_vertices[i].first - x)*(m_vertices[i].first - x) + (m_vertices[i].second - y)*(m_vertices[i].second - y));
			double length_2 = sqrt((m_vertices[i].first - m_vertices[i + 1].first)*(m_vertices[i].first - m_vertices[i + 1].first) + (m_vertices[i].second - m_vertices[i + 1].second)*(m_vertices[i].second - m_vertices[i + 1].second));
			double length_3 = sqrt((m_vertices[i + 1].first - x)*(m_vertices[i + 1].first - x) + (m_vertices[i + 1].second - y)*(m_vertices[i + 1].second - y));

			double cos = (length_2*length_2) / ((length_1*length_1) + (length_3*length_3) - 2 * length_3*length_1);

			sum += static_cast<coord_t>(cos);
		}

		double length_1 = sqrt((m_vertices[m_vertices.size() - 1].first - x)*(m_vertices[m_vertices.size() - 1].first - x) + (m_vertices[m_vertices.size() - 1].second - y)*(m_vertices[m_vertices.size() - 1].second - y));
		double length_2 = sqrt((m_vertices[m_vertices.size() - 1].first - m_vertices[0].first)*(m_vertices[m_vertices.size() - 1].first - m_vertices[0].first) + (m_vertices[m_vertices.size() - 1].second - m_vertices[0].second)*(m_vertices[m_vertices.size() - 1].second - m_vertices[0].second));
		double length_3 = sqrt((m_vertices[0].first - x)*(m_vertices[0].first - x) + (m_vertices[0].second - y)*(m_vertices[0].second - y));

		double cos = (length_2*length_2) / ((length_1*length_1) + (length_3*length_3) - 2 * length_3*length_1);

		sum += static_cast<coord_t>(cos);

		// TODO: voir si l'imprécision des doubles ne pourrais pas fausser le résultat?
		// Si la somme est 1 le point est à l'intérieur (somme des angles = 360°)
		if (sum == 1)
			return true;
		return false;

	}

	void Polygon::Serialize_to(const std::ostream& output_stream) const
	{
		// TODO: generate JSON
	}

	void Polygon::Deserialize_from(const std::istream& input_stream)
	{
		// TODO: parse JSON
	}

	Polygon::Polygon(std::string&& name, std::vector<Point>&& vertices)
		: IShape(std::move(name)), m_vertices(std::move(vertices))
	{ }
}
