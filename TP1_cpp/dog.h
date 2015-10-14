#pragma once

enum class color { RED, GREEN, BLUE, YELLOW, BROWN};

class dog
{
public:
	dog() = default;
	explicit dog(unsigned int age) : m_age(age) { 	}
	dog(color color, unsigned int age) : m_color(color), m_age(age) { 	}

	unsigned int getAge()
	{
		return m_age;
	}
protected:
	const color m_color = color::BLUE;
	unsigned int m_age = 2;
};