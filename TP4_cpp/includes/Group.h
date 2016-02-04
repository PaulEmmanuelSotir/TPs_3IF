/*********************************************************************************
									Group
									------
*********************************************************************************/

#ifndef GROUP_H
#define GROUP_H

#include <boost/serialization/split_member.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/unique_ptr.hpp>

#include "IShape.h"
#include "Utils.h"

// TODO: it might be desired to suppress the tracking of objects as it is known a priori that the application in question can never create duplicate objects. Serialization of pointers can be "fine tuned" via the specification of Class Serialization Traits as described in another section of this manual

namespace TP4
{
	template<bool is_union>
	class Group;

	using Shape_union = Group<true>;
	using Shape_intersection = Group<false>;
}

namespace boost // C++ 17: namespace boost::serialization
{
	namespace serialization
	{
		template<class Archive, bool is_union>
		void save_construct_data(Archive& ar, const TP4::Group<is_union>* shape, const unsigned int file_version);

		template<class Archive, bool is_union>
		void load_construct_data(Archive& ar, TP4::Group<is_union>* shape, const unsigned int file_version);
	}
}

//! \namespace TP4
//! espace de nommage regroupant le code crée pour le TP4 de C++
namespace TP4
{
	//! ...
	template<bool is_union>
	class Group : public IShape
	{
	public:
		using shape_vec_t = std::vector<std::unique_ptr<IShape>>;

		Group(std::string name, shape_vec_t&& shapes);
		Group(Group&&) = default;
		Group& operator=(Group&&) = default;
		Group(const Group&) = delete;
		Group& operator=(const Group&) = delete;
		~Group() override = default;

		void Move(coord_t dx, coord_t dy) override;
		bool Is_contained(const Point& point) const override;

	protected:
		shape_vec_t m_shapes;

		template<class Archive>
		inline void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::make_nvp("IShape", boost::serialization::base_object<IShape>(*this));
		}

		friend class boost::serialization::access;

		template<class Archive, bool is_u>
		friend void boost::serialization::save_construct_data(Archive& ar, const Group<is_u>* shape, const unsigned int file_version);

		template<class Archive, bool is_u>
		friend void boost::serialization::load_construct_data(Archive& ar, Group<is_u>* shape, const unsigned int file_version);
	};

	template<bool is_union>
	Group<is_union>::Group(std::string name, shape_vec_t&& shapes)
		: IShape(std::move(name)), m_shapes(std::move(shapes))
	{ }

	template<bool is_union>
	void Group<is_union>::Move(coord_t dx, coord_t dy)
	{
		for (auto& shape_ptr : m_shapes)
			shape_ptr->Move(dx, dy);
	}

	template<bool is_union>
	bool Group<is_union>::Is_contained(const Point& point) const
	{
		bool test = is_union;
		// TODO: verifier que ça marche bien
		for (auto& shape_ptr : m_shapes)
			if ((!is_union) ^ shape_ptr->Is_contained(point))
				return is_union;
		return !is_union;
	}
}

namespace boost // C++ 17: namespace boost::serialization
{
	namespace serialization
	{
		template<class Archive, bool is_union>
		void save_construct_data(Archive& ar, const TP4::Group<is_union>* shape, const unsigned int file_version)
		{
			// Enregistre les données nescessaires à la construction d'un 'TP4::Group<is_union>'
			ar << make_nvp("name", shape->m_name);
			ar << make_nvp("shapes", shape->m_shapes);
		}

		template<class Archive, bool is_union>
		void load_construct_data(Archive& ar, TP4::Group<is_union>* shape, const unsigned int file_version)
		{
			// Récupère les données nesceassaires à la construction d'un 'TP4::Group<is_union>'
			TP4::name_t name;
			std::vector<std::unique_ptr<TP4::IShape>> shapes;
			ar >> make_nvp("name", name);
			ar >> make_nvp("shapes", shapes);

			// Appele le constructeur de 'TP4::Group<is_union>' à l'addresse donnée par 'shape'
			::new (shape) TP4::Group<is_union>(std::move(name), std::move(shapes));
		}
	}
}

#endif // GROUP_H
