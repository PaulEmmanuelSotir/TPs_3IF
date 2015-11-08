/************************************************************************************
					collection  -  A dynamic and generic collection
					-----------------------------------------------
date                 : 11/2015
copyright            : (C) 2015 by B3311
************************************************************************************/

//---------------------- Interface de la classe collection<T> -----------------------
#pragma once

//------------------------------------------------------------------ Includes systeme
#include <cstddef>		// std::size_t
#include <utility>		// std::declval
#include <limits>		// std::numeric_limits
// TODO: enlever �a
#include <type_traits>	// pour exploiter SFINAE et pour 'std::declval()'

//----------------------------------------------------------------- Headers utilis�es
#include "utils.h"

namespace TP2
{
	//-------------------------------------------------------------------------------
	/// collection
	/// <summary> Classe permettant de stocker une collection d'objets de type T </summary> 
	///	<remarks> Le stockage interne des �lements est contigu </remarks>
	//-------------------------------------------------------------------------------
	template<typename T>
	class collection
	{
		//-------------------------------------------------------------------- PUBLIC
	public:
		using size_type = std::size_t;

		//-------------------------------------------------------- M�thodes publiques

		/// <summary> Ajoute val_to_add dans la collection courante </summary>
		/// <param name='val_to_add'> ref�rence constante vers une valeur de type T qui sera ajout� dans la collection </param>
		void add(const T& val_to_add);

		/// <summary> Ajoute le contenu de la collection donn�e en param�tre  </summary>
		///		<param name='other'> reference vers la collection � r�unir avec la collection courante </param>
		///	<returns> Un bool�en indiquant si des �l�ments de 'other' on bien �t� ajout�s � la collection </returns>
		bool add(const collection& other);

		/// <summary> Retire old_val de la collection courante </summary>
		///		<param name='old_val'> reference vers un T qui sera retir� de la collection </param>
		///	<returns> Un bool�en indiquant si au moins un �l�ment a bien �t� retir� </returns>
		/// <remarks>: Utilise l'op�rateur '==' pour comprer les �l�ments </remarks>
		bool remove(const T& old_val);

		/// <summary> Retire l'ensemble des valeurs contenues dans le parametre 'vals' de la collection courante </summary>
		///		<param name='vals'> tableau de T qui seront retir�s de la collection </param>
		///		<param name='size'> taille du tableau vals </param>
		///	<returns> Un bool�en indiquant si au moins un �l�ment a bien �t� retir� </returns>
		/// <remarks> Utilise l'op�rateur '==' pour comparer les �l�ments </remarks>
		bool remove(const T vals[], size_type size);

		/// <summary> Ajuste, si possible, la capacit� de la collection � la taille sp�cifi�e </summary>
		///		<param name='capacity'> nouvelle taille de m�moire allou�e pour la structure de donn�e interne </param>
		///	<returns> Un bool�en indiquant si un ajustement de la capacit� a bien �t� effectu� </returns>
		bool ajust(size_type capacity);

		//--------------------------------------------------- Surcharges d'op�rateurs

		/// <summary> Surcharge de l'operateur d'assignement par copie </summary>
		collection& operator=(collection other);

		/// <summary> Surcharges de l'operateur '[]' permettant l'acc�s et la modification du �l�ment de la collection </summary>
		T& operator[](size_type idx);
		T operator[](size_type idx) const;

		/// <summary> Surcharge de l'operateur ostream
		///		La valeur de la collection est serialis�e sous la forme : "({ 'val1', 'val2', ... }, 'm_capacity')"
		///		avec 'val1', 'val2', ... les �l�ments de la collection et 'm_capacity' la capacit� de la collection. </summary>
		/// <remarks>: utilise l'op�rateur ostream sur le type T </remarks>
		template<typename U>
		friend std::ostream& operator<<(std::ostream& os, const collection<U>& dt);

		/// <summary> Permute deux collections donn�es en param�tres dont les types d'�l�ments T sont identiques. </summary>
		template<typename U>
		friend void swap(collection<U>& lhs, collection<U>& rhs) noexcept;

		//----------------------------------------------- Constructeurs - destructeur

		/// <summary> Constructeur par default </summary>
		collection() = default;

		/// <summary> Constructeur de copie </summary>
		collection(const collection& other);

		/// <summary> Move constructeur </summary>
		collection(collection&& other) noexcept(is_nothrow_swappable<collection<T>>());

		/// <summary> Constructeur d'une collection de taille pr�-allou�e donn�e </summary>
		///		<param name='capacity'> Taille de la nouvelle collection </param>
		explicit collection(size_type capacity);

		/// <summary> Constructeur d'une collection � partir d'un ensemble d'�l�ments donn� en param�tre </summary>
		///		<param name='vals'> tableau des �l�ments qui seront ajout�s � la collection </param>
		///		<param name='size'> taille du tableau vals </param>
		collection(const T vals[], size_type size);

		/// <summary> Destructeur de la colection courante </summary>
		virtual ~collection();

		//--------------------------------------------------------------------- PRIVE 
	protected:
		//-------------------------------------------------------- M�thodes prot�g�es

		/// <summary> Trouve le nombre d'�l�ments apparetenant � la fois � 'm_vals' et au param�tre 'vals_to_find' </summary>
		///		<param name='vals_to_find'> tableau d'�l�ments de type T qui seront recherch�s dans la collection </param>
		///		<param name='size'> taille du tableau 'vals_to_find' </param>
		///	<returns> le nombre d'�l�ments apparetenant � la fois � 'm_vals' et � 'vals_to_find' </returns>
		unsigned int find_all_of(const T vals_to_find[], size_type size) const;

		/// <summary> D�salloue la m�moire allou�e pour le tableau d'objets de type T </summary>
		void dispose();

		//--------------------------------------------------------- Attributs prot�g�s

		/// Tableau de T
		T* m_vals = nullptr;
		/// Taille du tableau m_vals
		size_type m_capacity = 0;
		/// Taille utilis�e du tableau m_vals
		size_type m_size = 0;

		//------------------------------------------------------- Constantes prot�g�es

		static const size_type MAX_ALLOCATION_SIZE = std::numeric_limits<size_type>::max();
		static const size_type INITIAL_ALLOCATION_SIZE = 4;
	};

	//------------------ Impl�mentation de la classe collection<T> -------------------

	//------------------------------------------------------------------------- PUBLIC

	template<typename T>
	void collection<T>::add(const T& val_to_add)
	{
		// Reallocate memory if we don't have free space anymore
		if (m_size == m_capacity)
		{
			// Take a power of two capacity greater than 2 * m_size
			if (m_size > 0)
			{
				size_type powOf2_size = lowestPowOfTwoGreaterThan(2 * m_size);
				ajust(powOf2_size < MAX_ALLOCATION_SIZE ? powOf2_size : MAX_ALLOCATION_SIZE);
			}
			else
				ajust(INITIAL_ALLOCATION_SIZE);
		}

		// Append/Copy new value
		m_vals[m_size] = val_to_add;
		++m_size;
	}

	template<typename T>
	bool collection<T>::add(const collection& other)
	{
		if (other.m_size == 0 || other.m_vals == nullptr)
			return false; // We don't have any elements to append

		if (m_capacity - m_size >= other.m_size)
		{
			// We have enought free allocated space to store other.m_vals in m_vals
			for (size_type i = 0; i < other.m_size; ++i)
				m_vals[m_size + i] = other.m_vals[i];

			m_size += other.m_size;
		}
		else
		{
			// Allocate a new array of T objects
			size_type new_capacity = lowestPowOfTwoGreaterThan(m_size + other.m_size);
			T* new_vals = new T[new_capacity];

			// Copy other.m_vals to new_vals
			for (size_type i = 0; i < other.m_size; ++i)
				new_vals[i + m_size] = other.m_vals[i];

			if (m_vals != nullptr)
			{
				// Copy m_vals objects to new_vals
				for (size_type i = 0; i < m_size; ++i)
					new_vals[i] = m_vals[i];

				delete[] m_vals;
			}

			// Assign the new array to 'm_vals' and update 'm_capacity' and 'm_size'
			m_vals = new_vals;
			m_size += other.m_size;
			m_capacity = new_capacity;
		}

		return true;
	}

	template<typename T>
	bool collection<T>::remove(const T vals_to_remove[], size_type size)
	{
		if (vals_to_remove == nullptr || size == 0 || m_vals == nullptr)
			return false;

		// Find the number of elements to remove and get the index of the first one
		unsigned int removes_todo_count = find_all_of(vals_to_remove, size);

		if (removes_todo_count == 0)
			return false; // There isn't any element to remove

		if (removes_todo_count >= m_size)
			dispose(); // We remove all elements
		else
		{
			size_type new_size = m_size - removes_todo_count;
			T* new_vals = new T[new_size];

			// Copy 'm_vals' values in 'new_vals' except those present in 'vals_to_remove'
			size_type removes_count = 0;
			for (size_type i = 0; i < m_size; ++i)
			{
				auto val = m_vals[i];

				// Check if 'm_vals[i]' is in 'vals_to_remove'
				bool is_to_copy = true;
				for (size_type j = 0; j < size && removes_count < removes_todo_count; ++j)
				{
					if (vals_to_remove[j] == val)
					{
						++removes_count;
						is_to_copy = false;
					}
				}

				if (is_to_copy)
					new_vals[i - removes_count] = val;
			}

			delete[] m_vals;
			m_vals = new_vals;
			m_size = new_size;
			m_capacity = new_size;
		}
		return true;
	}

	template<typename T>
	bool collection<T>::remove(const T& old_value)
	{
		return retirer(&old_value, 1);
	}

	template<typename T>
	bool collection<T>::ajust(size_type new_capacity)
	{
		if (new_capacity < m_size || new_capacity == m_capacity)
			return false; // We forbid any element removal during a 'collection::ajust' call

		if (new_capacity == 0)
		{
			// We know that 'm_size == 0', 'm_capacity > 0' and 'm_vals != nullptr' 
			// We free all pre-allocated memory and return:
			dispose();
			return true;
		}

		// Allocate a new array of T objects
		T* new_vals = new T[new_capacity];

		// If this collection have any T objects, we copy them to 'new_vals' and we delete 'm_vals'
		if (m_vals != nullptr)
		{
			for (size_type i = 0; i < m_size; ++i)
				new_vals[i] = m_vals[i];

			delete[] m_vals;
		}

		// Assign the new array to 'm_vals' and update 'm_capacity'
		m_vals = new_vals;
		m_capacity = new_capacity;

		return true;
	}

	//---------------------------------------------------- Constructeurs - destructeur
	template<typename T>
	collection<T>::collection(collection&& other) noexcept(is_nothrow_swappable<collection<T>>())
		: collection()
	{
#ifdef MAP
		cout << "Appel au move-constructeur 'collection<T>::collection(collection<T>&&)'" << endl;
#endif
		swap(*this, other);
	}

	template<typename T>
	collection<T>::collection(const collection& other)
		: collection(other.m_capacity)
	{
#ifdef MAP
		cout << "Appel au constructeur de copie 'collection<T>::collection(const collection<T>&)'" << endl;
#endif
		m_size = other.m_size;
		try // T's copy assignment operator could throw and let collection in incoherent state
		{
			// Copy 'other' collection elements
			for (size_type i = 0; i < other.m_size; ++i)
				m_vals[i] = other.m_vals[i];
		}
		catch (...)
		{
			dispose();
			throw;
		}
	}

	template<typename T>
	collection<T>::collection(size_type capacity)
	{
#ifdef MAP
		cout << "Appel au constructeur 'collection<T>::collection(size_type)'" << endl;
#endif

		if (capacity > 0)
			m_vals = new T[capacity];
		else
			m_vals = nullptr;
		m_capacity = capacity;
	}

	template<typename T>
	collection<T>::collection(const T vals[], size_type size)
	{
#ifdef MAP
		cout << "Appel au constructeur 'collection<T>::collection(const T[], size_type)'" << endl;
#endif

		if (size > 0 && vals != nullptr)
		{
			// Create a new array of T objects
			m_vals = new T[size];
			m_capacity = size;

			// Copy given elements
			for (size_type i = 0; i < size; ++i)
				m_vals[i] = vals[i];
			m_size = size;
		}
	}

	template<typename T>
	collection<T>::~collection()
	{
#ifdef MAP
		cout << "Appel au destructeur de 'collection<T>'" << endl;
#endif
		// On d�salloue la m�moire allou�e pour le tableau de T si nescessaire
		dispose();
	}

	//-------------------------------------------------------- Surcharges d'op�rateurs
	template<typename T>
	collection<T>& collection<T>::operator=(collection other)
	{
		// Copy and swap idiom (in 'rule of 4' context (copy elision)
		swap(*this, other);
		return *this;
	}

	template<typename T>
	T& collection<T>::operator[](size_type idx)
	{
		return m_vals[idx];
	}

	template<typename T>
	T collection<T>::operator[](size_type idx) const
	{
		return m_vals[idx];
	}

	template<typename U>
	std::ostream& operator<<(std::ostream& os, const collection<U>& vec)
	{
		if (vec.m_size > 0)
		{
			os << "({ ";

			for (typename collection<U>::size_type i = 0; i < vec.m_size; ++i)
				os << vec.m_vals[i] << ((i < vec.m_size - 1) ? ", " : " }, ");

			os << vec.m_capacity << ")";
		}
		else
			os << "({ }, " << vec.m_capacity << ")";

		return os;
	}

	template<typename U>
	void swap(collection<U>& lhs, collection<U>& rhs) noexcept
	{
		// if one of the following swap calls isn't noexcept, we raise a static_assert
	//	static_assert(is_nothrow_swappable<typename collection<U>::size_type, U*>::value, "Swap function could throw and let collection<T> objects in incoherant state!");
		static_assert(noexcept(std::declval<typename collection<U>::size_type&>()), "size");
		static_assert(noexcept(std::declval<U* &>()), "U*");
	
		// enable ADL (following lines will use custom implementation of swap or std::swap if there isn't custom implementation)
		using std::swap;

		swap(lhs.m_size, rhs.m_size);
		swap(lhs.m_capacity, rhs.m_capacity);
		swap(lhs.m_vals, rhs.m_vals);
	}

	//-------------------------------------------------------------------------- PRIVE

	//------------------------------------------------------------- M�thodes prot�g�es
	template<typename T>
	unsigned int collection<T>::find_all_of(const T vals_to_find[], size_type size) const
	{
		unsigned int matches_count = 0;

		if (size > 0 && vals_to_find != nullptr && m_size > 0)
		{
			for (size_type idx1 = m_size - 1; idx1 < m_size; --idx1)
			{
				for (size_type idx2 = 0; idx2 < size; ++idx2)
				{
					if (m_vals[idx1] == vals_to_find[idx2])
					{
						++matches_count;
						break;
					}
				}
			}
		}

		return matches_count;
	}

	template<typename T>
	void collection<T>::dispose()
	{
		if (m_vals != nullptr)
		{
			delete[] m_vals;
			m_vals = nullptr;
			m_size = 0;
			m_capacity = 0;
		}
	}
}
