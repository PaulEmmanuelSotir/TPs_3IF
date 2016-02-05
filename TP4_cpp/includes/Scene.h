/*********************************************************************************
									Scene
									-----
*********************************************************************************/

#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <memory>

#ifdef USE_TXT_ARCHIVE
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#else
#ifdef USE_BINARY_ARCHIVE
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#else // Use XML archive
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#endif // !USE_BINARY_ARCHIVE
#endif // !USE_TXT_ARCHIVE

#include "Serializable_shape_history.h"
#include "Rectangle.h"
#include "Command.h"
#include "Segment.h"
#include "Polygon.h"
#include "Group.h"

//! \namespace TP4
//! espace de nommage regroupant le code cr�e pour le TP4 de C++
namespace TP4
{
	//! ...
	//! TODO: faire une copie qui cr�e de nouveaux unique_ptr ?
	class Scene final
	{
	public:
		Scene() = default;
		Scene(Scene&&) = default;
		Scene(const Scene&) = delete;
		Scene& operator=(Scene&&) = default;
		Scene& operator=(const Scene&) = delete;

		//! @throws std::invalid_argument ...
		void Undo();
		void Redo();
		void Clear();
		void List();
		void Load(std::string filename);
		void Save(std::string filename);
		void Delete(const std::vector<name_t>& name);
		void Add_segment(name_t name, Point x, Point y);
		void Add_rectangle(name_t name, Point x, Point y);
		bool Is_point_contained_by(Point point, name_t shape_name) const;
		void Move_shape(name_t shape_name, coord_t dx, coord_t dy);
		void Add_polygon(name_t name, const std::vector<Point>& vertices);
		void Union(name_t union_name, const std::unordered_set<name_t>& shapes_names);
		void Intersect(name_t inter_name, const std::unordered_set<name_t>& shapes_names);

	private:
		Shape_history m_shapes;

		template<typename Group_t>
		void Create_group(const name_t& group_name, const std::unordered_set<name_t>& shapes_names);
	};

	template<typename Group_t>
	void Scene::Create_group(const name_t& group_name, const std::unordered_set<name_t>& shapes_names)
	{
		m_shapes.commit();

		std::vector<History_state::iterator> shapes_its;
		auto& current_shapes = m_shapes.current();

		// V�rifie si le nom n'est pas d�ja pris
		if (current_shapes.find(group_name) != std::end(current_shapes))
			throw std::invalid_argument("Shape name already existing");

		// Trouve les formes concern�es et v�rifie qu'il n'y a pas de duplicats
		for (const auto& shape_name : shapes_names)
		{
			auto it = current_shapes.find(shape_name);
			if (it == std::end(current_shapes))
				throw std::invalid_argument("One or more shape name is invalid");
			shapes_its.push_back(it);
		}

		// Transfert l'ownership des formes vers le groupe
		std::vector<History_shape> shapes;
		for (auto& it : shapes_its)
		{
			shapes.emplace_back(std::move(it->second));
			current_shapes.erase(it);
		}

		// Add shape to current history state
		current_shapes.emplace(group_name, Group_t(std::move(shapes)));
	}
}

#endif // !SCENE_H
