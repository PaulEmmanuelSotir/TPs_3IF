/*********************************************************************************
									Group
									------
*********************************************************************************/

#ifndef GROUP_H
#define GROUP_H

#include <string>

#include "Serializable_shape_history.h"
#include "Utils.h"

// TODO: it might be desired to suppress the tracking of objects as it is known a priori that the application in question can never create duplicate objects. Serialization of pointers can be "fine tuned" via the specification of Class Serialization Traits as described in another section of this manual

//! \namespace TP4
//! espace de nommage regroupant le code crée pour le TP4 de C++
namespace TP4
{
	//----------------------------------------------------------------------------
	//! Classe représentant une intersection ou une union de formes. Le paramètre 
	//! template 'is_union' est un booléen indiquant si il s'agit d'une union ou 
	//! d'une intersection de fomres géomètriques.
	//! La classe est serialisable grâce à boost::serialization.
	//----------------------------------------------------------------------------
	template<bool is_union>
	struct Group
	{
		using shape_vec_t = std::vector<History_shape>;

		Group() = default;
		Group(shape_vec_t&& shapes);
		Group(Group&&) = default;// TODO: default ou delete?
		Group& operator=(Group&&) = default; // TODO: default ou delete?
		Group(const Group&) = delete;
		Group& operator=(const Group&) = delete;

	private:
		shape_vec_t shapes;

		template<bool is_u>
		friend Group<is_u> Move(const Group<is_u>& group, coord_t dx, coord_t dy);

		template<bool is_u>
		friend bool Is_contained(const Group<is_u>& group, Point point);

		friend class boost::serialization::access;

		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::make_nvp("shapes", shapes);
		}
	};

	using Shape_union = Group<true>;
	using Shape_intersection = Group<false>;

	template<bool is_union>
	Group<is_union>::Group(shape_vec_t&& shapes)
		: shapes(std::move(shapes))
	{ }

	template<bool is_union>
	Group<is_union> Move(const Group<is_union>& group, coord_t dx, coord_t dy)
	{
		typename Group<is_union>::shape_vec_t new_shapes;
		new_shapes.reserve(group.shapes.size());
		for (auto& shape : group.shapes)
			new_shapes.emplace_back(Move(shape, dx, dy)); // les formes étants immutables 'TP4::Move' retourne une nouvelle forme

		return Group<is_union>(std::move(new_shapes));
	}

	template<bool is_union>
	bool Is_contained(const Group<is_union>& group, Point point)
	{
		for (auto& shape : group.shapes)
			if ((!is_union) ^ Is_contained(shape, point))
				return is_union;
		return !is_union;
	}
}

#endif // !GROUP_H
