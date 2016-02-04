//
//  Polygone.cpp
//  
//
//  Created by Victoire Chapelle on 14/01/2016.
//
//

#include "Polygon.h"

#include <math.h>
#include <string>
#include <boost/serialization/vector.hpp>

#include "Utils.h"

namespace TP4
{
	std::unique_ptr<Polygon> make_polygon(std::string name, std::vector<Point> vertices)
	{
		if (name.empty())
			return nullptr;

		if (vertices.size() > 3)
		{
			Point p1, p2;

			p1.first = vertices[0].first - vertices[vertices.size()].first;
			p1.second = vertices[0].second - vertices[vertices.size()].second;
			p2.first = vertices[1].first - vertices[0].first;
			p2.second = vertices[1].second - vertices[0].second;

			double det_value;
			double current_det_value;

			det_value = p1.first * p2.second - p1.second * p2.first;

			for (size_t i = 0; i < vertices.size(); ++i)
			{
				p1.first = vertices[mod(i + 1, vertices.size())].first - vertices[i].first;
				p1.second = vertices[mod(i + 1, vertices.size())].second - vertices[i].second;
				p2.first = vertices[mod(i + 2, vertices.size())].first - vertices[mod(i + 1, vertices.size())].first;
				p2.second = vertices[mod(i + 2, vertices.size())].second - vertices[mod(i + 1, vertices.size())].second;

				current_det_value = p1.first * p2.second - p1.second * p2.first;

				if (det_value*current_det_value <= 0)
					return nullptr;

			}
		}

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
			double length_2_squared = (m_vertices[i].first - m_vertices[mod(i + 1, m_vertices.size())].first)*(m_vertices[i].first - m_vertices[mod(i + 1, m_vertices.size())].first) + (m_vertices[i].second - m_vertices[mod(i + 1, m_vertices.size())].second)*(m_vertices[i].second - m_vertices[mod(i + 1, m_vertices.size())].second);
			double length_3 = sqrt((m_vertices[mod(i + 1, m_vertices.size())].first - x)*(m_vertices[mod(i + 1, m_vertices.size())].first - x) + (m_vertices[mod(i + 1, m_vertices.size())].second - y)*(m_vertices[mod(i + 1, m_vertices.size())].second - y));

			double cos = length_2_squared / ((length_1*length_1) + (length_3*length_3) - 2 * length_3*length_1);

			sum += cos;
		}

		// Si la somme est 1 le point est à l'intérieur (somme des angles = 360°)
		if (sum < 1.001 && sum > 0.999)
			return true;
		return false;

	}

	Polygon::Polygon(std::string&& name, std::vector<Point>&& vertices)
		: IShape(std::move(name)), m_vertices(std::move(vertices))
	{ }
}
