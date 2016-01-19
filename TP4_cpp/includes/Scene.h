/*********************************************************************************
									Scene
									-----
*********************************************************************************/

#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "IShape.h"
#include "Utils.h"
#include "Command.h"

//! \namespace TP4
//! espace de nommage regroupant le code crée pour le TP4 de C++
namespace TP4
{
	//! ...
	//! Etant donné que la classe contient des std::unique_ptr, la classe n'est pas copiable (uniquement movable)
	class Scene final
	{
	public:
		Scene()							= default;
		Scene(Scene&&)					= default;
		Scene& operator=(Scene&&)		= default;
		Scene(const Scene&)				= delete;
		Scene& operator=(const Scene&)	= delete;

		//! @throws std::invalid_argument ...
		void Add_segment(name_t name, Point x, Point y);
		void Add_rectangle(name_t name, Point x, Point y);
		void Add_polygon(name_t name, const std::vector<Point>& vertices);
		void Delete(const std::vector<name_t>& name);
		void Union(name_t union_name, const std::unordered_set<name_t>& shapes_names);
		void Intersect(name_t inter_name, const std::unordered_set<name_t>& shapes_names);
		bool Is_point_contained_by(Point point, name_t shape_name) const;
		void Move_shape(name_t shape_name, coord_t dx, coord_t dy);
		void Clear();
		void Undo();
		void Redo();
		void Load(std::string filename);
		void Save(std::string filename);

	private:
		std::unordered_map<name_t, std::unique_ptr<IShape>> m_shapes;
		std::vector<std::unique_ptr<Command>> m_command_history;

		template<typename T>
		void Append_to_history(const T& cmd);

		template<typename Group_t>
		void CreateGroup(const name_t& group_name, const std::unordered_set<name_t>& shapes_names);

		template<class Archive>
		void serialize(Archive & ar, const unsigned int version) { ar & m_shapes; }

		friend class boost::serialization::access;
	};


	template<typename T>
	void Scene::Append_to_history(const T& cmd)
	{
		m_command_history.push_back(std::make_unique<T>(cmd));
	}

	template<typename Group_t>
	void Scene::CreateGroup(const name_t& group_name, const std::unordered_set<name_t>& shapes_names)
	{
		std::vector<decltype(m_shapes)::iterator> shapes_its;

		// Vérifie si le nom n'est pas déja pris
		if (m_shapes.find(group_name) != std::cend(m_shapes))
			throw std::invalid_argument("Shape name already existing");

		// Trouve les formes concernées et vérifie qu'il n'y a pas de duplicats
		for (const auto& shape_name : shapes_names)
		{
			auto it = m_shapes.find(shape_name);
			if (it == std::cend(m_shapes))
				throw std::invalid_argument("One or more shape name is invalid");
			shapes_its.push_back(it);
		}

		// Transfert l'ownership des formes vers le groupe
		std::vector<std::unique_ptr<IShape>> shapes;
		for (auto& it : shapes_its)
		{
			shapes.emplace_back(std::move(it->second));
			m_shapes.erase(it);
		}

		// Add shape to m_shapes
		m_shapes.emplace(group_name, std::make_unique<Group_t>(group_name, std::move(shapes)));
	}
}

#endif // SCENE_H
