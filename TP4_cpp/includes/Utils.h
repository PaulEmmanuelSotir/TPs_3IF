/*********************************************************************************
					Utils  -  A few common functions or types
					-----------------------------------------
*********************************************************************************/

#ifndef UTILS_H
#define UTILS_H

#include <type_traits>
#include <sstream>
#include <string>

#include <boost/serialization/utility.hpp>
#include <boost/serialization/unordered_set.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include <boost/serialization/nvp.hpp>

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
	inline std::vector<std::string> split(const std::string& str, char delim) {
		std::stringstream ss(str);
		std::string item;
		std::vector<std::string> tokens;

		while (getline(ss, item, delim))
			tokens.push_back(item);

		return tokens;
	}

	// TODO: voir si il serais mieux de faire une structure binary op
	template <typename T, typename U, typename = typename std::enable_if<!std::is_arithmetic<T>::value>::type>
	inline U mod(T a, T b) {
		return a % b;
	}

	template <typename UnsignedInteger, typename = typename std::enable_if<std::is_integral<UnsignedInteger>::value && std::is_unsigned<UnsignedInteger>::value>::type>
	constexpr UnsignedInteger mod(UnsignedInteger a, UnsignedInteger b) {
		return UNLIKELY(a >= b) ? a % b : a; // voir https://www.youtube.com/watch?v=nXaxk27zwlk&feature=youtu.be&t=3394
	}

	template <typename Integer, typename = typename std::enable_if<std::is_integral<Integer>::value && std::is_signed<Integer>::value>::type, typename = void>
	constexpr Integer mod(Integer a, Integer b) {
		return UNLIKELY(a >= b || -a >= b) ? a % b : a;
	}

	template <typename Floating, typename = typename std::enable_if<std::is_floating_point<Floating>::value>::type, typename = void, typename = void>
	inline Floating mod(Floating a, Floating b) {
		return std::fmod(a, b); // TODO: benchmark this to see if "UNLIKELY(a >= b || -a >= b) ? ... : a;" could help.
	}
}


namespace boost
{
	namespace serialization
	{
		//template<class Archive, class Allocator, class T>
		//inline void save(Archive& ar, const std::vector<std::unique_ptr<T>, Allocator>& vec, const unsigned int file_version)
		//{
		//	auto count = vec.size();
		//	ar << BOOST_SERIALIZATION_NVP(count);

		//	for (const auto& elt : vec)
		//		ar << make_nvp("item", elt);
		//}

		//template<class Archive, class Allocator, class T>
		//inline void load(Archive& ar, std::vector<std::unique_ptr<T>, Allocator>& vec, const unsigned int file_version)
		//{
		//	decltype(vec)::size_type count;
		//	ar >> BOOST_SERIALIZATION_NVP(count);
		//	vec.clear();
		//	vec.reserve(count);

		//	while (count-- != 0)
		//	{
		//		std::unique_ptr<T> ptr;
		//		ar >> make_nvp("item", ptr);
		//		vec.emplace_back(std::move(ptr));
		//	}
		//}

		//template<class Archive, class k, class V, class Comp, class MapAlloc>
		//inline void save(Archive& ar, const std::map<k, std::unique_ptr<V>, Comp, MapAlloc>& map, const unsigned int file_version)
		//{
		//	auto count = map.size();
		//	ar << BOOST_SERIALIZATION_NVP(count);

		//	for (const auto& pair : map)
		//	{
		//		ar << make_nvp("key", pair.first);
		//		ar << make_nvp("value", pair.second);
		//	}
		//}

		//template<class Archive, class K, class V, class Comp, class MapAlloc>
		//inline void load(Archive& ar, std::map<K, std::unique_ptr<V>, Comp, MapAlloc>& map, const unsigned int file_version)
		//{
		//	decltype(map)::size_type count;
		//	ar >> BOOST_SERIALIZATION_NVP(count);
		//	map.clear();

		//	while (count-- != 0)
		//	{
		//		K key;
		//		ar >> make_nvp("key", key);
		//		std::unique_ptr<V> value;
		//		ar >> make_nvp("value", value);
		//		map[key] = std::move(value);
		//	}
		//}

		//template<class Archive, class Allocator, class T>
		//inline void serialize(Archive& ar, std::vector<std::unique_ptr<T>, Allocator>& vec, const unsigned int file_version)
		//{
		//	split_free(ar, vec, file_version);
		//}

		//template<class Archive, class K, class V, class Comp, class Allocator>
		//inline void serialize(Archive& ar, std::map<K, std::unique_ptr<V>, Comp, Allocator>& map, const unsigned int file_version)
		//{
		//	boost::serialization::split_free(ar, map, file_version);
		//}


		//template<class Archive, class First, class Second>
		//inline void save_construct_data(Archive& ar, const std::pair<First, std::unique_ptr<Second>>* pair, const unsigned int file_version)
		//{
		//	// Save data required to construct instance
		//	using non_const_first_t = typename std::remove_const<First>::type;
		//	ar	<< boost::serialization::make_nvp("first", const_cast<non_const_first_t &>(pair->first))
		//		<< boost::serialization::make_nvp("second", pair->second);
		//}

		//template<class Archive, class First, class Second>
		//inline void load_construct_data(Archive& ar, std::pair<First, std::unique_ptr<Second>>* pair, const unsigned int file_version)
		//{
		//	typename std::remove_const<First>::type first;
		//	std::unique_ptr<Second> second;
		//	ar	>> boost::serialization::make_nvp("first", first)
		//		>> boost::serialization::make_nvp("second", second);

		//	// Invoke inplace constructor to initialize instance of std::pair
		//	::new(pair) std::pair<First, std::unique_ptr<Second>>(std::move(first), std::move(second));
		//}

		/*template<class Archive, class First, class Second>
		inline void serialize(Archive& ar, std::pair<First, std::unique_ptr<Second>>& pair, const unsigned int file_version)
		{

		}*/
	}
}

//
//namespace boost
//{
//	namespace serialization
//	{
//		// TODO: enlever ça?
//		template<typename T, typename Archive>
//		void serialize(Archive& ar, std::unique_ptr<T>& g, const unsigned int version)
//		{
//			ar & (*g);
//		}
//	}
//}

#endif // UTILS_H
