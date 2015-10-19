/*********************************************************************************
							dog  -  dummy dog structure
							---------------------------
date                 : 10/2015
copyright            : (C) 2015 by B3311
*********************************************************************************/

#ifndef DOG_H
#define DOG_H

namespace TP1
{
	//----------------------------------------------------------------------------
	// color: Enumèration de quelques couleurs
	//----------------------------------------------------------------------------
	enum class color { RED, GREEN, BLUE, YELLOW, BROWN };

	//----------------------------------------------------------------------------
	// dog: structure simple representant un chien
	//----------------------------------------------------------------------------
	struct dog
	{
		//----------------------------------------------------------------- PUBLIC
	public:
		//-------------------------------------------- Constructeurs - destructeur

		dog() = default;
		explicit dog(unsigned int age) : age(age) { }
		dog(color color, unsigned int age) : color(color), age(age) { }

		//------------------------------------------------------ Membres publiques

		color color = TP1::color::BLUE;
		unsigned int age = 2;
	};

	//------------------------------------------------------- OPERATOR OVERLOADING

	inline bool operator==(const dog& lhs, const dog& rhs) { return lhs.age == rhs.age && lhs.color == rhs.color; }
	inline bool operator!=(const dog& lhs, const dog& rhs) { return !(lhs == rhs); }
}

#endif // DOG_H
