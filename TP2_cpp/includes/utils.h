/************************************************************************************
							utils  -  Quelques outils communs
							---------------------------------
date                 : 11/2015
copyright            : (C) 2015 by B3311
************************************************************************************/

#pragma once

//------------------------------------------------------------------ Includes systeme
#include <type_traits> // pour exploiter SFINAE et pour 'std::declval()'

namespace TP2
{
	/// <summary> Unrestricted union template allowing nullable type T </summary>
	/// <remarks> T must have a default constructor </remarks>
	template<typename T>
	union nullable
	{
		T data;
		nullptr_t is_null;
		explicit nullable(T t) { new(&data) T; }
		explicit nullable(nullptr_t t) { is_null = nullptr; }
	};

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

	//-------------------------------------------------------- Surcharges d'opérateurs
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

	//------------------------------------------------------------- Fonctions globales

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

	// Possible sans récursion avec 'noexcept( std::tuple<Ts...>->swap() )'
	// Egalement possibe avec le c++ 17 (fold expressions) :
	/*template <typename... Ts>
	constexpr bool is_nothrow_swappable() {
		return noexcept(swap(std::declval<T&>(), std::declval<T&>())) && ...;
	}*/

	// TODO: correct if n overflows ?
	/// <summary> Calcule la plus petite puissance de 2 supérieure à n (0 si n est négatif) </summary>
	template <typename Integer, typename = typename std::enable_if_t < std::is_integral<Integer>::value && std::is_signed<Integer>::value>>
	constexpr Integer lowestPowOfTwoGreaterThan(Integer n)
	{
		if (n < 0)
			return 0;
		--n;
		for (uint32_t pow = 1; pow < 8 * sizeof(Integer); pow *= 2)
			n |= n >> pow;
		return n + 1;
	}

	/// <summary> Calcule la plus petite puissance de 2 supérieure à n </summary>
	template <typename UnsignedInteger, typename = typename std::enable_if_t<std::is_integral<UnsignedInteger>::value && std::is_unsigned<UnsignedInteger>::value>, typename = void>
	constexpr UnsignedInteger lowestPowOfTwoGreaterThan(UnsignedInteger n)
	{
		--n;
		for (uint32_t pow = 1; pow < 8 * sizeof(UnsignedInteger); pow *= 2)
			n |= n >> pow;
		return n + 1;
	}
}
