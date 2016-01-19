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

// On utilise la fonction intrinsèque __builtin_expect si disponnible
#ifdef __GNUC__
#define LIKELY(expr)    __builtin_expect((bool)(expr), !0)
#define UNLIKELY(expr)  __builtin_expect((bool)(expr), 0)
#else
#define LIKELY(expr)    expr
#define UNLIKELY(expr)  expr
#endif

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

	// TODO: see if it would be better to create a struct binary op + see if handle unsigned values is needed
	template <typename T, typename U, typename = typename std::enable_if_t<!std::is_arithmetic<T>::value>>
	inline U mod(T a, T b) {
		return a % b;
	}

	template <typename UnsignedInteger, typename = typename std::enable_if_t<std::is_integral<UnsignedInteger>::value && std::is_unsigned<UnsignedInteger>::value>>
	constexpr UnsignedInteger mod(UnsignedInteger a, UnsignedInteger b) {
		return UNLIKELY(a >= b) ? a % b : a;
	}

	template <typename Integer, typename = typename std::enable_if_t<std::is_integral<Integer>::value && std::is_signed<Integer>::value>, typename = void>
	constexpr Integer mod(Integer a, Integer b) {
		return UNLIKELY(a >= b || -a >= b) ? a % b : a; // see https://www.youtube.com/watch?v=nXaxk27zwlk&feature=youtu.be&t=3394
	}

	template <typename Floating, typename = typename std::enable_if_t<std:: is_floating_point<Floating>::value>, typename = void, typename = void>
	inline Floating mod(Floating a, Floating b) {
		return std::fmod(a, b); // TODO: benchmark this to see if "UNLIKELY(a >= b || -a >= b) ? ... : a;" could help.
	}
}

#endif // UTILS_H
