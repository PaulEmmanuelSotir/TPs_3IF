
#include <string>

#include "groupe.h"
#include "Forme.h"

TP4::Groupe::Groupe(std::string name, const TP4::Forme& first, const TP4::Forme& second)
	: name(name), first(first), second(second)
{ }

void TP4::Groupe::SerializeTo(const std::ostream& output_stream)
{
	// TODO: generate JSON
}

void TP4::Groupe::DeserializeFrom(const std::ostream& output_stream)
{
	// TODO: parse JSON
}
