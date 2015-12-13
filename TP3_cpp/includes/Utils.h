#ifndef UTILS_H
#define UTILS_H

#include <tuple>
#include <string>
#include <type_traits>

namespace TP3
{
	template <size_t N, typename... Args>
	using get_by_Index_t = typename std::tuple_element<N, std::tuple<Args...>>::type;

	template <typename T, typename... Args>
	struct index_of;

	template <typename T, typename... Args>
	struct index_of<T, T, Args...> : std::integral_constant<std::size_t, 0> { };

	template <typename T, typename Tail, typename... Args>
	struct index_of<T, Tail, Args...> : std::integral_constant<std::size_t, 1 + index_of<T, Args...>::value> { };

	//TODO: add support for any integer base

	//TODO: quel sens donner � 'strong_convertion' ici ?
	template<typename T, bool strong_convertion = true>
	inline T parse(const std::string& str)
	{
		return static_cast<T>(str);
	}

	template<>
	inline float parse<float, true>(const std::string& str)
	{
		size_t idx;
		auto val = std::stof(str, &idx);
		if (idx != str.length())
			throw std::invalid_argument("Given std::string cannot be converted to float");
		return val;
	}

	template<>
	inline float parse<float, false>(const std::string& str) { return std::stof(str); }

	template<>
	inline double parse<double, true>(const std::string& str)
	{
		size_t idx;
		auto val = std::stod(str, &idx);
		if (idx != str.length())
			throw std::invalid_argument("Given std::string cannot be converted to double");
		return val;
	}

	template<>
	inline double parse<double, false>(const std::string& str) { return std::stod(str); }

	template<>
	inline long double parse<long double, true>(const std::string& str)
	{
		size_t idx;
		auto val = std::stold(str, &idx);
		if (idx != str.length())
			throw std::invalid_argument("Given std::string cannot be converted to long double");
		return val;
	}

	template<>
	inline long double parse<long double, false>(const std::string& str) { return std::stold(str); }

	template<>
	inline int parse<int, true>(const std::string& str)
	{
		size_t idx;
		auto val = std::stoi(str, &idx);
		if (idx != str.length())
			throw std::invalid_argument("Given std::string cannot be converted to int");
		return val;
	}

	template<>
	inline int parse<int, false>(const std::string& str) { return std::stoi(str); }

	// TODO: improve range check ?
	template<>
	inline unsigned int parse<unsigned int, true>(const std::string& str)
	{
		size_t idx;
		auto val = static_cast<unsigned int>(std::stoul(str, &idx));
		if (idx != str.length())
			throw std::invalid_argument("Given std::string cannot be converted to unsigned int");
		return val;
	}

	template<>
	inline unsigned int parse<unsigned int, false>(const std::string& str) { return static_cast<unsigned int>(std::stoul(str)); }

	// TODO: improve range check ?
	template<>
	inline short parse<short, true>(const std::string& str)
	{
		size_t idx;
		auto val = static_cast<short>(std::stol(str, &idx));
		if (idx != str.length())
			throw std::invalid_argument("Given std::string cannot be converted to short");
		return val;
	}

	template<>
	inline short parse<short, false>(const std::string& str) { return static_cast<short>(std::stol(str)); }

	// TODO: improve range check ?
	template<>
	inline unsigned short parse<unsigned short, true>(const std::string& str)
	{
		size_t idx;
		auto val = static_cast<unsigned short>(std::stoul(str, &idx));
		if (idx != str.length())
			throw std::invalid_argument("Given std::string cannot be converted to unsigned short");
		return val;
	}

	template<>
	inline unsigned short parse<unsigned short, false>(const std::string& str) { return static_cast<unsigned short>(std::stoul(str)); }

	template<>
	inline long parse<long, true>(const std::string& str)
	{
		size_t idx;
		auto val = std::stol(str, &idx);
		if (idx != str.length())
			throw std::invalid_argument("Given std::string cannot be converted to long");
		return val;
	}

	template<>
	inline long parse<long, false>(const std::string& str) { return std::stol(str); }

	template<>
	inline unsigned long parse<unsigned long, true>(const std::string& str)
	{
		size_t idx;
		auto val = std::stoul(str, &idx);
		if (idx != str.length())
			throw std::invalid_argument("Given std::string cannot be converted to unsigned long");
		return val;
	}

	template<>
	inline unsigned long parse<unsigned long, false>(const std::string& str) { return std::stoul(str); }

	template<>
	inline long long parse<long long, true>(const std::string& str)
	{
		size_t idx;
		auto val = std::stoll(str, &idx);
		if (idx != str.length())
			throw std::invalid_argument("Given std::string cannot be converted to long long");
		return val;
	}

	template<>
	inline long long parse<long long, false>(const std::string& str) { return std::stoll(str); }

	template<>
	inline unsigned long long parse<unsigned long long, true>(const std::string& str)
	{
		size_t idx;
		auto val = std::stoull(str, &idx);
		if (idx != str.length())
			throw std::invalid_argument("Given std::string cannot be converted to unsigned long long");
		return val;
	}

	template<>
	inline unsigned long long parse<unsigned long long, false>(const std::string& str) { return std::stoull(str); }
}

#endif // UTILS_H
