#include <unordered_set>
#include <iostream>
#include <fstream>
#include <tuple>

#include "Group.h"
#include "Scene.h"
#include "Segment.h"
#include "Polygon.h"
#include "rectangle.h"

namespace TP4
{
	void Scene::Add_segment(name_t name, Point x, Point y)
	{
		auto segment = static_cast<std::unique_ptr<IShape>>(make_segment(name, x, y));
		if (!segment)
			throw std::invalid_argument("Invalid segment");

		bool inserted;
		std::tie(std::ignore, inserted) = m_shapes.emplace(name, std::move(segment));
		if (!inserted)
			throw std::invalid_argument("Shape name already existing");

		Append_to_history(Add_segment_cmd(std::move(name), x, y));
	}

	void Scene::Add_rectangle(name_t name, Point x, Point y)
	{
		auto rectangle = static_cast<std::unique_ptr<IShape>>(make_rectangle(name, x, y));
		if (!rectangle)
			throw std::invalid_argument("Invalid rectangle");

		bool inserted;
		std::tie(std::ignore, inserted) = m_shapes.emplace(name, std::move(rectangle));
		if (!inserted)
			throw std::invalid_argument("Shape name already existing");

		Append_to_history(Add_rectangle_cmd(std::move(name), x, y));
	}

	void Scene::Add_polygon(name_t name, const std::vector<Point>& vertices)
	{
		auto polygon = static_cast<std::unique_ptr<IShape>>(make_polygon(name, vertices));
		if (!polygon)
			throw std::invalid_argument("Invalid polygon");

		bool inserted;
		std::tie(std::ignore, inserted) = m_shapes.emplace(name, std::move(polygon));
		if (!inserted)
			throw std::invalid_argument("Shape name already existing");

		Append_to_history(Add_polygon_cmd(std::move(name), vertices));
	}

	void Scene::Delete(const std::vector<name_t>& shapes_names)
	{
		using it_t = decltype(m_shapes)::const_iterator;

		std::vector<it_t> shape_iterators;

		for (const auto& shape_name : shapes_names)
		{
			it_t it = m_shapes.find(shape_name);
			if (it == std::cend(m_shapes))
				throw std::invalid_argument("One or more shape name is invalid");
			shape_iterators.push_back(it);
		}

		for (auto& it : shape_iterators)
			m_shapes.erase(it);

		Append_to_history(Delete_cmd(shapes_names));
	}

	void Scene::Union(name_t union_name, const std::unordered_set<name_t>& shapes_names)
	{
		CreateGroup<Shape_union>(union_name, shapes_names);
		Append_to_history(Union_cmd(std::move(union_name), shapes_names));
	}

	void Scene::Intersect(name_t inter_name, const std::unordered_set<name_t>& shapes_names)
	{
		CreateGroup<Shape_intersection>(inter_name, shapes_names);
		Append_to_history(Inter_cmd(std::move(inter_name), shapes_names));
	}

	bool Scene::Is_point_contained_by(Point point, name_t shape_name) const
	{
		auto it = m_shapes.find(shape_name);
		if (it == std::cend(m_shapes))
			throw std::invalid_argument("Invalid shape name");

		return it->second->Is_contained(point);
	}

	void Scene::Move_shape(name_t shape_name, coord_t dx, coord_t dy)
	{
		auto it = m_shapes.find(shape_name);
		if (it == std::cend(m_shapes))
			throw std::invalid_argument("Invalid shape name");

		it->second->Move(dx, dy);

		Append_to_history(Move_cmd(std::move(shape_name), dx, dy));
	}

	void Scene::Clear()
	{
		m_shapes.clear();
		Append_to_history(Clear_cmd());
	}

	void Scene::Undo()
	{
		// ...
	}

	void Scene::Redo()
	{
		// ...
	}

	void Scene::Load(std::string filename)
	{
		std::ifstream in_fstream;
		in_fstream.open(filename);
		if (!in_fstream.is_open())
			throw std::invalid_argument("Wrong file name");

		Deserialize_from(in_fstream);
		in_fstream.close();

		Append_to_history(Load_cmd(std::move(filename)));
	}

	void Scene::Save(std::string filename)
	{
		std::ofstream out_fstream;
		out_fstream.open(filename);
		if (!out_fstream.is_open())
			throw std::invalid_argument("Wrong file name");

		Serialize_to(out_fstream);
		out_fstream.close();

		Append_to_history(Save_cmd(std::move(filename)));
	}

	void Scene::Serialize_to(const std::ostream& output_stream) const
	{
		// ...
	}

	void Scene::Deserialize_from(const std::istream& input_stream)
	{
		// ...
	}
}
