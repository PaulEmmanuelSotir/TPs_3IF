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
		// TODO: peut être garder un offset (plus rapide que d'iterer sur les sommets)
		for (Point& p : m_vertices)
		{
			p.first += dx;
			p.second += dy;
		}
	}

	bool Polygon::Is_contained(const Point& point) const
	{
		double sum = 0.0;
		auto x = point.first;
		auto y = point.second;

		// Calcul de la somme des cosinus que font les angles entre les sommets consécutifs et le point
		for (size_t i = 0; i < m_vertices.size(); ++i)
		{
			double length_1 = sqrt((m_vertices[i].first - x)*(m_vertices[i].first - x) + (m_vertices[i].second - y)*(m_vertices[i].second - y));
			double length_2_squared = (m_vertices[i].first - m_vertices[mod(i + 1,m_vertices.size())].first)*(m_vertices[i].first - m_vertices[mod(i + 1,m_vertices.size())].first) + (m_vertices[i].second - m_vertices[mod(i + 1,m_vertices.size())].second)*(m_vertices[i].second - m_vertices[mod(i + 1,m_vertices.size())].second);
			double length_3 = sqrt((m_vertices[mod(i + 1,m_vertices.size())].first - x)*(m_vertices[mod(i + 1,m_vertices.size())].first - x) + (m_vertices[mod(i + 1,m_vertices.size())].second - y)*(m_vertices[mod(i + 1,m_vertices.size())].second - y));

			double cos = length_2_squared / ((length_1*length_1) + (length_3*length_3) - 2 * length_3*length_1);

			sum += cos;
		}

		// Si la somme est 1 le point est à l'intérieur (somme des angles = 360°)
		if (sum < 1.001 && sum > 0.999)
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
