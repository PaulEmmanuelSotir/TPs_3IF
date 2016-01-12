/*********************************************************************************
					Forme - Une forme g�om�trique serialisable
					------------------------------------------
*********************************************************************************/

#ifndef FORME_H
#define FORME_H

#include <ostream>

//! \namespace TP4
//! espace de nommage regroupant le code cr�e pour le TP4 de C++
namespace TP4
{
	//! Classe abstraite repr�sentant une forme g�om�trique s�rialisable
	class Forme
	{
	public:
		virtual void Move(double dx, double dy) = 0;
		virtual bool IsContained(double x, double y) = 0;		
		
		virtual void SerializeTo(const std::ostream& output_stream) = 0;
		virtual void DeserializeFrom(const std::ostream& output_stream) = 0;

		virtual ~Forme() = 0;
	};
}

#endif // FORME_H
