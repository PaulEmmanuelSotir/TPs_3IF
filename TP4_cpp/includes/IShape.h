/*********************************************************************************
					IShape - Une forme géométrique serialisable
					-------------------------------------------
*********************************************************************************/

#ifndef ISHAPE_H
#define ISHAPE_H

#include <ostream>
#include <istream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

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
		explicit IShape(std::string&& name)
			: m_name(std::move(name))
		{ }

		const std::string m_name;

		//! When the class Archive corresponds to an output archive, the
		//! & operator is defined similar to <<. Likewise, when the class Archive
		//! is a type of input archive the & operator is defined similar to >>.
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version) { ar & m_name; }

		friend class boost::serialization::access;
	};
}

#endif // ISHAPE_H
