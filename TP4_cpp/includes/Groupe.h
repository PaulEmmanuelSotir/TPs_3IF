
/*********************************************************************************
									Groupe
									------
*********************************************************************************/

#ifndef GROUPE_H
#define GROUPE_H

#include <ostream>

#include "Forme.h"
#include "Utils.h"

//! \namespace TP4
//! espace de nommage regroupant le code crée pour le TP4 de C++
namespace TP4
{
	struct Groupe : Forme
	{
		Groupe() = default;
		Groupe(std::string name, const Forme& first, const Forme& second);
		virtual ~Groupe() = default;

		void SerializeTo(const std::ostream& output_stream) override;
		void DeserializeFrom(const std::ostream& output_stream) override;

		const Forme& first;
		const Forme& second;
		std::string name;
	};
}

#endif // GROUPE_H
