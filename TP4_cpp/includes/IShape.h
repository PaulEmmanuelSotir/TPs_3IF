/*********************************************************************************
					IShape - Une forme géométrique serialisable
					-------------------------------------------
*********************************************************************************/

#ifndef ISHAPE_H
#define ISHAPE_H

#include <boost/config.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/unordered_set.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/assume_abstract.hpp>

#include "Command.h"

//! \namespace TP4
//! espace de nommage regroupant le code crée pour le TP4 de C++
namespace TP4
{
	// TODO: implement operator overloadings == != < > <= >=

	//! Classe abstraite représentant une forme géométrique sérialisable
	class IShape
	{
	public:
		virtual ~IShape() = default;
		virtual void Move(coord_t dx, coord_t dy) = 0;
		virtual bool Is_contained(const Point& point) const = 0;

	protected:
		explicit IShape(name_t&& name)
			: m_name(std::move(name))
		{ }

		name_t m_name;

		template<typename Archive>
		inline void serialize(Archive& ar, const unsigned int version) { }

		friend class boost::serialization::access;
	};
}
#include "Serialization.h"

#endif // ISHAPE_H
