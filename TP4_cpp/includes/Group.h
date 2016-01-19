/*********************************************************************************
									Group
									------
*********************************************************************************/

#ifndef GROUPE_H
#define GROUPE_H

#include <ostream>
#include <memory>

#include "IShape.h"
#include "Utils.h"

//! \namespace TP4
//! espace de nommage regroupant le code crée pour le TP4 de C++
namespace TP4
{
	//! ...
	//! Etant donné que la classe contient des std::unique_ptr, la classe n'est pas copiable (uniquement movable)
	template<bool is_union>
	class Group : public IShape
	{
	public:
		Group(std::string name, std::vector<std::unique_ptr<IShape>>&& shapes);
		Group(Group&&)					= default;
		Group& operator=(Group&&)		= default;
		Group(const Group&)				= delete;
		Group& operator=(const Group&)	= delete;
		~Group() override				= default;

		void Move(coord_t dx, coord_t dy) override;
		bool Is_contained(const Point& point) const override;

		void Serialize_to(const std::ostream& output_stream) const override;
		void Deserialize_from(const std::istream& input_stream) override;

	protected:
		const std::vector<std::unique_ptr<IShape>> m_shapes;
	};

	using Shape_union = Group<true>;
	using Shape_intersection = Group<false>;

	template<bool is_union>
	Group<is_union>::Group(std::string name, std::vector<std::unique_ptr<IShape>>&& shapes)
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
		// TODO: verifier que ça marche bien
		for (auto& shape_ptr : m_shapes)
			if ((!is_union) ^ shape_ptr->Is_contained(point))
				return is_union;
		return !is_union;
	}

	template<bool is_union>
	void Group<is_union>::Serialize_to(const std::ostream& output_stream) const
	{
		// TODO: generate JSON
	}

	template<bool is_union>
	void Group<is_union>::Deserialize_from(const std::istream& input_stream)
	{
		// TODO: parse JSON
	}
}

#endif // GROUPE_H
