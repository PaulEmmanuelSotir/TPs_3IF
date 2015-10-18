#pragma once

namespace TP1
{
	enum class color { RED, GREEN, BLUE, YELLOW, BROWN };

	//----------------------------------------------------------------------------
	// dog:
	// structure representant un chien
	//----------------------------------------------------------------------------
	struct dog
	{
	public:
		dog() = default;
		explicit dog(unsigned int age) : age(age) { }
		dog(color color, unsigned int age) : color(color), age(age) { }

		color color = TP1::color::BLUE;
		unsigned int age = 2;
	};

	inline bool operator==(const dog& lhs, const dog& rhs) { return lhs.age == rhs.age && lhs.color == rhs.color; }
	inline bool operator!=(const dog& lhs, const dog& rhs) { return !(lhs == rhs); }
}
