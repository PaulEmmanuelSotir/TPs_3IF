/*********************************************************************************
					Forme - Une forme géométrique serialisable
					------------------------------------------
*********************************************************************************/

#ifndef UTILS_H
#define UTILS_H

#include <ostream>

//! \namespace TP4
//! espace de nommage regroupant le code crée pour le TP4 de C++
namespace TP4
{
	class Forme
	{
	public:
		virtual void SerializeTo(const std::ostream& output_stream) = 0;
		virtual void DeserializeFrom(const std::ostream& output_stream) = 0;

		virtual ~Forme() = 0;
	};
}

#endif // UTILS_H
