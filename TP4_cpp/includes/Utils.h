/*********************************************************************************
					Utils  -  A few common functions or types
					-----------------------------------------
*********************************************************************************/

#ifndef UTILS_H
#define UTILS_H

#include <utility>
#include <sstream>
#include <string>
#include <vector>

//! \namespace TP4
//! espace de nommage regroupant le code crée pour le TP4 de C++
namespace TP4
{
	using Point = std::pair<double, double>;

	inline std::vector<std::string> split(const std::string &s, char delim) {
		std::stringstream ss(s);
		std::string item;
		std::vector<std::string> tokens;

		while (getline(ss, item, delim))
			tokens.push_back(item);

		return tokens;
	}
}

#endif // UTILS_H
