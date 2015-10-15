#pragma once

enum class color { RED, GREEN, BLUE, YELLOW, BROWN };

struct dog
{
public:
	dog() = default;
	explicit dog(unsigned int age) : age(age) { }
	dog(color color, unsigned int age) : color(color), age(age) { }

	const color color = color::BLUE;
	unsigned int age = 2;
};