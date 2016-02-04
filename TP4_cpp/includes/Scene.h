/*********************************************************************************
									Scene
									-----
*********************************************************************************/

#ifndef SCENE_H
#define SCENE_H

#include <boost/config.hpp>
//#include <boost/archive/text_oarchive.hpp>
//#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/unordered_set.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include <boost/serialization/utility.hpp>

#include "Rectangle.h"
#include "Command.h"
#include "Segment.h"
#include "Polygon.h"
#include "IShape.h"
#include "Group.h"

//! \namespace TP4
//! espace de nommage regroupant le code cr�e pour le TP4 de C++
namespace TP4
{
	//! ...
	//! Etant donn� que la classe contient des std::unique_ptr, la classe n'est pas copiable (uniquement movable)
	//! TODO: faire une copie qui cr�e de nouveaux unique_ptr ?
	class Scene final
	{
	public:
		Scene() = default;
		Scene(Scene&&) = default;
		Scene& operator=(Scene&&) = default;
		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;

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
		void Create_group(const name_t& group_name, const std::unordered_set<name_t>& shapes_names);

		//! Fonction ajoutant au registre de l'archive de serialisation les types d�riv�s de IShape. Cela permet � boost::serialization de g�rer le polymorphisme lors de la (de)serialisation
		template<typename Archive>
		static void register_IShape_derived_types(Archive& ar)
		{
			ar.template register_type<Rectangle>();
			ar.template register_type<Segment>();
			ar.template register_type<Polygon>();
			ar.template register_type<Shape_union>();
			ar.template register_type<Shape_intersection>();
		}

		template<typename Archive>
		void save(Archive& ar, const unsigned int version) const
		{
			register_IShape_derived_types(ar);

			// Serialisation manuelle de m_shapes (on ne peut pas faire 'ar << m_shapes' car m_shapes contient des unique_ptr non copiables
			auto size = m_shapes.size();
			ar << boost::serialization::make_nvp("shape_count", size);
			for (const auto& p : m_shapes)
			{
				ar << boost::serialization::make_nvp("name", p.first);
				ar << boost::serialization::make_nvp("shape", p.second);
			}
		}

		template<typename Archive>
		void load(Archive& ar, const unsigned int version)
		{
			register_IShape_derived_types(ar);
			m_shapes.clear();

			// Deserialisation manuelle de m_shapes (on ne peut pas faire 'ar >> m_shapes' car m_shapes contient des unique_ptr non copiables
			decltype(m_shapes)::size_type size;
			ar >> boost::serialization::make_nvp("shape_count", size);
			m_shapes.clear();
			m_shapes.reserve(size);

			while (size-- != 0)
			{
				std::unique_ptr<IShape> shape;
				name_t name;
				ar >> boost::serialization::make_nvp("name", name);
				ar >> boost::serialization::make_nvp("shape", shape);
				if (shape)
					m_shapes[name] = std::move(shape);
			}
		}

		BOOST_SERIALIZATION_SPLIT_MEMBER()

		friend class boost::serialization::access;
	};


	template<typename T>
	void Scene::Append_to_history(const T& cmd)
	{
		m_command_history.push_back(std::make_unique<T>(cmd));
	}

	template<typename Group_t>
	void Scene::Create_group(const name_t& group_name, const std::unordered_set<name_t>& shapes_names)
	{
		std::vector<decltype(m_shapes)::iterator> shapes_its;

		// V�rifie si le nom n'est pas d�ja pris
		if (m_shapes.find(group_name) != std::end(m_shapes))
			throw std::invalid_argument("Shape name already existing");

		// Trouve les formes concern�es et v�rifie qu'il n'y a pas de duplicats
		for (const auto& shape_name : shapes_names)
		{
			auto it = m_shapes.find(shape_name);
			if (it == std::end(m_shapes))
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
