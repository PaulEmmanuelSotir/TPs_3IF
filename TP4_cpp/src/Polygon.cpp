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
#include "Segment.h"

namespace TP4
{
	std::experimental::optional<Polygon> make_polygon(const std::vector<Point> vertices)
	{
		if (vertices.size() > 2)
		{
			Point p1, p2;

			p1.first = vertices[0].first - vertices[vertices.size() - 1].first;
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

				if (det_value*current_det_value < 0 - 0.00001)
					return std::experimental::nullopt;
			}

			return std::experimental::optional<Polygon>(Polygon(std::move(vertices)));
		}

		return std::experimental::nullopt;
	}

	Polygon Move(const Polygon& shape, coord_t dx, coord_t dy)
	{
		std::vector<Point> new_vertices;
		new_vertices.reserve(new_vertices.size());

		for (const Point& p : shape.vertices)
			new_vertices.emplace_back(p.first + dx, p.second + dy);

		return Polygon(std::move(new_vertices));
	}

	inline double squared_distance(Point a, Point b)
	{
		return (a.first - b.first) * (a.first - b.first) 
			+ (a.second - b.second) * (a.second - b.second);
	}

	bool Is_contained(const Polygon& shape, Point point)
	{
		double sum = 0.0;

		// Calcul de la somme des cosinus que font les angles entre les sommets consécutifs et le point
		for (size_t i = 0; i < shape.vertices.size(); ++i)
		{
			auto next_point = shape.vertices[mod(i + 1, shape.vertices.size())];

			double a2 = squared_distance(shape.vertices[i], point);
			double c2 = squared_distance(shape.vertices[i], next_point);
			double b2 = squared_distance(next_point, point);

			if (abs(a2) < 0.001 || abs(b2) < 0.001)
				return true; // Le point est confondu avec un sommet

			auto seg = make_segment(shape.vertices[i], next_point);
			if(seg)
				if (Is_contained(*seg, point))
					return true;

			// Formule d'al-kashi : cos(angle) = (a² + b² - c²) / (2*a*b)
			double cos = (a2 + b2 - c2) / (2.0*sqrt(a2)*sqrt(b2)); 
		//	double cos = c2 / (length_1 + length_3 - 2.0*sqrt(length_3)*sqrt(length_1));

			sum += acos(cos);
		}

		// Si la somme est 1 le point est à l'intérieur (somme des angles = 360°)
		// TODO: faire mieux?
		if (abs(mod(sum, 2.0*3.14159) < 0.001))
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
			flux << "(" << polygone.vertices[i].first << ", " << polygone.vertices[i].second << (i == polygone.vertices.size() - 1 ? ") " : "); ");
		flux << "}";

		return flux;
	}
}
