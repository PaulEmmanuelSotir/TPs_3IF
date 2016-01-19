/*********************************************************************************
					IShape - Une forme g�om�trique serialisable
					-------------------------------------------
*********************************************************************************/

#ifndef ISHAPE_H
#define ISHAPE_H

#include <ostream>
#include <istream>

#include "ISerializable.h"
#include "Command.h"

//! \namespace TP4
//! espace de nommage regroupant le code cr�e pour le TP4 de C++
namespace TP4
{
	// TODO: implement operator overloadings == != < > <= >=

	//! Classe abstraite repr�sentant une forme g�om�trique s�rialisable
	class IShape : public ISerializable
	{
	public:
		virtual void Move(coord_t dx, coord_t dy) = 0;
		virtual bool Is_contained(const Point& point) const = 0;

	protected:
		explicit IShape(std::string&& name)
			: m_name(std::move(name))
		{ }

		const std::string m_name;
	};
}

#endif // ISHAPE_H
