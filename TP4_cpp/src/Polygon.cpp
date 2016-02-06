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
#include "optional.h"

namespace TP4
{
	std::experimental::optional<Polygon> make_polygon(const std::vector<Point> vertices)
	{
		if (vertices.size() > 3)
		{
			Point p1, p2;

			p1.first = vertices[0].first - vertices[vertices.size()-1].first;
			p1.second = vertices[0].second - vertices[vertices.size() - 1].second;
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
					return std::experimental::nullopt;
			}
		}

		return std::experimental::optional<Polygon>(Polygon(std::move(vertices)));
	}

	Polygon Move(const Polygon& shape, coord_t dx, coord_t dy)
	{
		std::vector<Point> new_vertices;
		new_vertices.reserve(new_vertices.size());

		for (const Point& p : shape.vertices)
			new_vertices.emplace_back(p.first + dx, p.second + dy);

		return Polygon(std::move(new_vertices));
	}

	bool Is_contained(const Polygon& shape, Point point)
	{
		double sum = 0.0;
		auto x = point.first;
		auto y = point.second;

		// Calcul de la somme des cosinus que font les angles entre les sommets consécutifs et le point
		for (size_t i = 0; i < shape.vertices.size(); ++i)
		{
			double length_1 = sqrt(		(shape.vertices[i].first - x) * (shape.vertices[i].first - x)
									+	(shape.vertices[i].second - y) * (shape.vertices[i].second - y));
			
			double length_2_squared = (shape.vertices[i].first - shape.vertices[mod(i + 1, shape.vertices.size())].first) * (shape.vertices[i].first - shape.vertices[mod(i + 1, shape.vertices.size())].first)
									+ (shape.vertices[i].second - shape.vertices[mod(i + 1, shape.vertices.size())].second) * (shape.vertices[i].second - shape.vertices[mod(i + 1, shape.vertices.size())].second);
			
			double length_3 = sqrt(		(shape.vertices[mod(i + 1, shape.vertices.size())].first - x) * (shape.vertices[mod(i + 1, shape.vertices.size())].first - x)
									+	(shape.vertices[mod(i + 1, shape.vertices.size())].second - y) * (shape.vertices[mod(i + 1, shape.vertices.size())].second - y));

			double cos = length_2_squared / ((length_1*length_1) + (length_3*length_3) - 2 * length_3*length_1);

			sum += cos;
		}

		// Si la somme est 1 le point est à l'intérieur (somme des angles = 360°)
		// TODO: faire mieux?
		if (sum < 1.001 && sum > 0.999)
			return true;
		return false;
	}

	Polygon::Polygon(const std::vector<Point>&& vertices)
		: vertices(std::move(vertices))
	{ }

	std::ostream& operator<<(std::ostream& flux, const Polygon& polygone)
	{
		flux << "{ ";
		for (size_t i = 0; i < polygone.vertices.size(); ++i)
			flux << "(" << polygone.vertices[i].first << ", " << polygone.vertices[i].second << (i == polygone.vertices.size()-1 ? ") " : "); ");
		flux << "}";

		return flux;
	}
}
