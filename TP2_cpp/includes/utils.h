/************************************************************************************
							utils  -  Quelques outils communs
							---------------------------------
date                 : 11/2015
copyright            : (C) 2015 by B3311
************************************************************************************/

#pragma once

//------------------------------------------------------------------ Includes systeme
#include <type_traits> // pour exploiter SFINAE et pour 'std::declval()'

//--------------------------------------------------------------------------- Defines

#ifdef __GNUC__ // We use __builtin_expect intrinsinc if available
/// <summary> Permet de contrôler comment les branchages (if-else, ...) sont traduits en 
///		assembleur en donnant pour information au compilateur le fait que l'expression
///		booleenne 'expr' a plus de chances d'être vraie que fausse </summary>
///	<remarks> La macro utilisant des fonctions intrinsèques au compilateur, il est possible
///		, selon le compilateur utilisé, que cette macro soit sans éffets. </remarks>
#define LIKELY(expr)    __builtin_expect((bool)(expr), !0)
/// <summary> Permet de contrôler comment les branchages (if-else, ...) sont traduits en 
///		assembleur en donnant pour information au compilateur le fait que l'expression
///		booleenne 'expr' a plus de chances d'être fausse que vraie </summary>
///	<remarks> La macro utilisant des fonctions intrinsèques au compilateur, il est possible
///		, selon le compilateur utilisé, que cette macro soit sans éffets. </remarks>
#define UNLIKELY(expr)  __builtin_expect((bool)(expr), 0)
#else
/// <summary> Permet de contrôler comment les branchages (if-else, ...) sont traduits en 
///		assembleur en donnant pour information au compilateur le fait que l'expression
///		booleenne 'expr' a plus de chances d'être vraie que fausse </summary>
///	<remarks> La macro utilisant des fonctions intrinsèques au compilateur, il est possible
///		, selon le compilateur utilisé, que cette macro soit sans éffets. </remarks>
#define LIKELY(expr)    expr
/// <summary> Permet de contrôler comment les branchages (if-else, ...) sont traduits en 
///		assembleur en donnant pour information au compilateur le fait que l'expression
///		booleenne 'expr' a plus de chances d'être fausse que vraie </summary>
///	<remarks> La macro utilisant des fonctions intrinsèques au compilateur, il est possible
///		, selon le compilateur utilisé, que cette macro soit sans éffets. </remarks>
#define UNLIKELY(expr)  expr
#endif

namespace TP2
{
	//-------------------------------------------------------------------------------
	/// pair
	/// <summary> Simple classe représantant une paire d'objets de type différents </summary>
	//-------------------------------------------------------------------------------
	template<typename T1, typename T2>
	struct pair
	{
		pair() = default;
		pair(T1 f, T2 s) : first(f), second(s) { }

		T1 first;
		T2 second;
	};

	//------------------------------------------------------- Surcharges d'opérateurs
	/// <summary> Overload de l'opérateur '==' pour le type 'pair' </summary>
	template<typename T1, typename T2>
	bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return
			lhs.first == rhs.first &&
			lhs.second == rhs.second;
	}

	/// <summary> Overload de l'opérateur '!=' pour le type 'pair' </summary>
	template<typename T1, typename T2>
	bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return !(lhs == rhs); }

	//------------------------------------------------------------ Fonctions globales

	// enable ADL (following lines will use custom implementation of swap or std::swap if there isn't custom implementation)
	namespace { using std::swap; }

	// Commenté car is_nothrow_swappable ne fonctionne pas avec gcc installé en IF
	/*
		// TODO: faire une fonction plus générique vérifiant la noexcept-itude pour toute fonctions spécifiée en paramètre (pas seulement swap)
		/// <summary> Metafonction permettant d'aider à vérifier si un ensemble de types disposent d'une fonction swap marquée noexcept </summary>
		/// <returns> Un booléen indiquant si les types passés en paramètre template peuvent être tous swapés en sécurité </returns>
		template <typename Head, typename T, typename... Ts>
		constexpr bool is_nothrow_swappable() {
			return noexcept(swap(std::declval<Head&>(), std::declval<Head&>())) &&
				is_nothrow_swappable<T, Ts...>(); // Récursion
		}

		template <typename T>
		constexpr bool is_nothrow_swappable() {
			return noexcept(swap(std::declval<T&>(), std::declval<T&>())); // Fin de la récursion
		}
	*/

	// Possible sans récursion avec 'noexcept( std::tuple<Ts...>->swap() )'
	// Egalement possibe avec le c++ 17 (fold expressions) :
	/*template <typename... Ts>
	constexpr bool is_nothrow_swappable() {
		return noexcept(swap(std::declval<T&>(), std::declval<T&>())) && ...;
	}*/

	// TODO: correct if n overflows ?
	/// <summary> Calcule la plus petite puissance de 2 supérieure à n (0 si n est négatif) </summary>
	template <typename Integer, typename = typename std::enable_if<std::is_integral<Integer>::value && std::is_signed<Integer>::value>::type>
	inline Integer lowest_pow_of_two_greater_than(Integer n)
	{
		// see "http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2"
		if (n < 0)
			return 0;
		--n;
		for (uint32_t pow = 1; pow < 8 * sizeof(Integer); pow *= 2)
			n |= n >> pow;
		return n + 1;
	}

	/// <summary> Calcule la plus petite puissance de 2 supérieure à n </summary>
	template <typename UnsignedInteger, typename = typename std::enable_if<std::is_integral<UnsignedInteger>::value && std::is_unsigned<UnsignedInteger>::value>::type, typename = void>
	inline UnsignedInteger lowest_pow_of_two_greater_than(UnsignedInteger n)
	{
		// see "http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2"
		--n;
		for (uint32_t pow = 1; pow < 8 * sizeof(UnsignedInteger); pow *= 2)
			n |= n >> pow;
		return n + 1;
	}
}
