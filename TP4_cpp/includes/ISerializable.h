/*********************************************************************************
									ISerilizable
									------------
*********************************************************************************/

#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <ostream>
#include <istream>

//! \namespace TP4
//! espace de nommage regroupant le code cr»e pour le TP4 de C++
namespace TP4
{
	class ISerializable
	{
	public:
		virtual void Serialize_to(const std::ostream& output_stream) const = 0;
		virtual void Deserialize_from(const std::istream& input_stream) = 0;

		virtual ~ISerializable() = default;
	};
}

#endif // ISERIALIZABLE_H
