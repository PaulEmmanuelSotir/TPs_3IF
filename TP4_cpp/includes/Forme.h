/*********************************************************************************
					Forme - Une forme géométrique serialisable
					------------------------------------------
*********************************************************************************/

#ifndef FORME_H
#define FORME_H

#include <ostream>

//! \namespace TP4
//! espace de nommage regroupant le code crée pour le TP4 de C++
namespace TP4
{
	//! Classe abstraite représentant une forme géométrique sérialisable
	class Forme
	{
	public:
		virtual void SerializeTo(const std::ostream& output_stream) = 0;
		virtual void DeserializeFrom(const std::ostream& output_stream) = 0;

		virtual ~Forme() = 0;
	};
}

#endif // FORME_H
