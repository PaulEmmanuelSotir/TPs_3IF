#include "Scene.h"

#include <fstream>
#include <tuple>

#include "Group.h"
#include "Segment.h"
#include "Polygon.h"
#include "rectangle.h"
#include "Serializable_shape_history.h"

namespace TP4
{
	void Scene::Add_segment(name_t name, Point x, Point y)
	{
		m_shapes.commit();
		auto segment = make_segment(x, y);
		if (!segment)
			throw std::invalid_argument("Invalid segment");

		bool inserted;
		std::tie(std::ignore, inserted) = m_shapes.current().emplace(std::move(name), segment.value());
		if (!inserted)
			throw std::invalid_argument("Shape name already existing");
	}

	void Scene::Add_rectangle(name_t name, Point x, Point y)
	{
		m_shapes.commit();
		auto rectangle = make_rectangle(x, y);
		if (!rectangle)
			throw std::invalid_argument("Invalid rectangle");

		bool inserted;
		std::tie(std::ignore, inserted) = m_shapes.current().emplace(std::move(name), rectangle.value());
		if (!inserted)
			throw std::invalid_argument("Shape name already existing");
	}

	void Scene::Add_polygon(name_t name, const std::vector<Point>& vertices)
	{
		m_shapes.commit();
		auto polygon = make_polygon(vertices);
		if (!polygon)
			throw std::invalid_argument("Invalid polygon");

		bool inserted;
		std::tie(std::ignore, inserted) = m_shapes.current().emplace(std::move(name), polygon.value());
		if (!inserted)
			throw std::invalid_argument("Shape name already existing");
	}

	void Scene::Delete(const std::vector<name_t>& shapes_names)
	{
		m_shapes.commit();
		using it_t = History_state::const_iterator;
		auto& current_shapes = m_shapes.current();

		std::vector<it_t> shape_iterators;

		for (const auto& shape_name : shapes_names)
		{
			it_t it = current_shapes.find(shape_name);
			if (it == std::end(current_shapes)) // C++ 14: std::cend
				throw std::invalid_argument("One or more shape name is invalid");
			shape_iterators.push_back(it);
		}

		for (auto& it : shape_iterators)
			current_shapes.erase(it);
	}

	void Scene::Union(name_t union_name, const std::unordered_set<name_t>& shapes_names)
	{
		Create_group<Shape_union>(union_name, shapes_names);
	}

	void Scene::Intersect(name_t inter_name, const std::unordered_set<name_t>& shapes_names)
	{
		Create_group<Shape_intersection>(inter_name, shapes_names);
	}

	bool Scene::Is_point_contained_by(Point point, name_t shape_name) const
	{
		const auto& current_shapes = m_shapes.current();
		auto it = current_shapes.find(shape_name);
		if (it == std::end(current_shapes)) // C++ 14: std::cend
			throw std::invalid_argument("Invalid shape name");

		return Is_contained(it->second, point);
	}

	void Scene::Move_shape(name_t shape_name, coord_t dx, coord_t dy)
	{
		m_shapes.commit();
		auto& current_shapes = m_shapes.current();
		auto it = current_shapes.find(shape_name);
		if (it == std::end(current_shapes)) // C++ 14: std::cend
			throw std::invalid_argument("Invalid shape name");

		Move(it->second, dx, dy);
	}

	void Scene::ClearAll()
	{
		m_shapes.clear();
	}

	void Scene::ClearCurrentState()
	{
		m_shapes.commit();
		m_shapes.current().clear();
	}

	void Scene::Undo()
	{
		m_shapes.undo();
	}

	void Scene::Redo()
	{
		m_shapes.redo();
	}

	void Scene::List()
	{
		if (m_shapes.current().size() == 0)
			std::cout << "Aucunes formes" << std::endl;
		else
		{
			for (const auto& shape : m_shapes.current())
			{
				std::cout << "* " << shape.first << " :\t";
				Print(shape.second);
				std::cout << std::endl;
			}
		}
	}

	void Scene::Load(std::string filename)
	{
		std::ifstream in_fstream;
		in_fstream.open(filename);
		if (!in_fstream.is_open())
			throw std::invalid_argument("Wrong file name");

		boost::archive::xml_iarchive archive(in_fstream);

		m_shapes.commit();
		auto& current_shapes = m_shapes.current();
		current_shapes.clear();

		archive >> boost::serialization::make_nvp("shapes", current_shapes);
		// archive and stream are closed when destructors are called
	}

	void Scene::Save(std::string filename)
	{
		const auto& current_shapes = m_shapes.current();

		std::ofstream out_fstream;
		out_fstream.open(filename);
		if (!out_fstream.is_open())
			throw std::invalid_argument("Wrong file name");

		boost::archive::xml_oarchive archive(out_fstream);
		archive << boost::serialization::make_nvp("shapes", current_shapes);
		// archive and stream are closed when destructors are called
	}
}
