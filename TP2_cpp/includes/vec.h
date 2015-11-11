/************************************************************************************
					vec  -  A dynamic and generic vector
					------------------------------------
date                 : 11/2015
copyright            : (C) 2015 by B3311
************************************************************************************/

//---------------------- Interface de la classe vec<T> -----------------------
#pragma once

//------------------------------------------------------------------ Includes systeme
#include <cstddef>		// std::size_t
#include <utility>		// std::declval et std::forward
#include <limits>		// std::numeric_limits

//----------------------------------------------------------------- Headers utilisées
#include "utils.h"

namespace TP2
{
	//-------------------------------------------------------------------------------
	/// vec
	/// <summary> Classe permettant de stocker un vecteur d'objets de type T </summary> 
	///	<remarks> Le stockage interne des élements est contigu en mémoire </remarks
	///	<remarks> La capacité du vecteur doit être strictement inférieure à vec::MAX_ALLOCATION_SIZE </remarks>
	//-------------------------------------------------------------------------------
	// TODO: Implementer des itérateurs pour vec
	template<typename T>
	class vec
	{
		//-------------------------------------------------------------------- PUBLIC
	public:
		using size_type = std::size_t;
		using predicate = bool(*)(const T&, const T&);	// TODO: serais mieux avec std::function<>

		//-------------------------------------------------------- Méthodes publiques

		/// <summary> Ajoute val_to_add dans le 'vec' courant </summary>
		/// <param name='val_to_add'> reférence constante vers une valeur de type T qui sera ajouté dans le vec </param>
		/// <remarks> Le vecteur considère qu'ajouter un élément peut changer l'ordre des éléments (désactive toutes optimisations liées au tri) </remarks>
		void add(const T& val_to_add);

		/// <summary> Ajoute un element de type T dans le vec courant à partir des argument d'un constructeur de T </summary>
		/// <param name='CtorArgsTypes'> Arguments donnés à un constructeur de T </param>
		/// <remarks> Le vecteur considère qu'ajouter un élément peut changer l'ordre des éléments (désactive toutes optimisations liées au tri) </remarks>
		template<typename... CtorArgsTypes>
		T& add(CtorArgsTypes&&... ctor_args);

		/// <summary> Ajoute le contenu de le vec donné en paramètre  </summary>
		///	<param name='other'> reference vers le vec à réunir avec le vec courant </param>
		///	<returns> Un booléen indiquant si des éléments de 'other' on bien été ajoutés au vec </returns>
		/// <remarks> Le vecteur considère qu'ajouter un élément peut changer l'ordre des éléments (désactive toutes optimisations liées au tri) </remarks>
		bool add(const vec& other);

		/// <summary> Retire old_val de le vec courant </summary>
		///	<param name='old_val'> reference vers un T qui sera retiré de le vec </param>
		///	<returns> Un booléen indiquant si au moins un élément a bien été retiré </returns>
		/// <remarks>: Utilise l'opérateur '==' par défaut pour comparer les éléments </remarks>
		bool remove(const T& old_val);

		/// <summary> Retire l'ensemble des valeurs contenues dans le parametre 'vals' du vec courant </summary>
		///	<param name='vals'> tableau de T qui seront retirés du vec </param>
		///	<param name='size'> taille du tableau vals </param>
		///	<returns> Un booléen indiquant si au moins un élément a bien été retiré </returns>
		/// <remarks> Utilise l'opérateur '=='  par défaut pour comparer les éléments </remarks>
		bool remove(const T vals[], size_type size);

		/// <summary> Ajuste, si possible, la capacité du vec à la taille spécifiée </summary>
		///		<param name='capacity'> nouvelle taille de mémoire allouée pour la structure de donnée interne </param>
		///	<returns> Un booléen indiquant si un ajustement de la capacité a bien été effectué </returns>
		bool ajust(size_type capacity);

		/// <summary> Trouve un élément spécifié en paramaètre dans le vecteur </summary>
		///	<param name='element_to_find'> Référence constante vers l'élement de type T à rechercher </param>
		/// <remarks> Utilise par défaut l'opérateur '==' pour comparer les éléments </remarks>
		/// <remarks> Si le vecteur à été trié avant, cette opération utlise un algorithme de recherche plus rappide </remarks>
		///	<returns> L'indice de l'élément dans le vecteur ou MAX_ALLOCATION_SIZE+1 si aucun éléments n'a été trouvé </returns>
		size_type find(const T& element_to_find) const;

		/// <summary> Trie les éléments du vecteur </summary>
		/// <remarks> Utilise l'opérateur 'inferieur à' pour comparer les éléments </remarks>
		/// <remarks> Il serait préférable que le type T dispose d'une surcharge de la fonction swap pour des raisons de performances </remarks>
		void sort();

		/// <summary> Retourne la taille occupée du vecteur </summary>
		size_type length() const;

		/// <summary> Retourne la capacité du vecteur </summary>
		size_type capacity() const;

		//--------------------------------------------------- Surcharges d'opérateurs

		/// <summary> Surcharge de l'operateur d'assignement par copie </summary>
		const vec& operator=(vec other);

		/// <summary> Surcharges de l'operateur '[]' permettant l'accès d'un élément du vecteur </summary>
		T operator[](size_type idx) const;
		/// <summary> Surcharges de l'operateur '[]' permettant l'accès et la modification d'un élément du vecteur </summary>
		T& operator[](size_type idx);

		/// <summary> Surcharge de l'operateur ostream :
		///		La valeur du vec est serialisée sous la forme : "({ 'val1', 'val2', ... }, 'm_capacity')"
		///		avec 'val1', 'val2', ... les éléments du vec et 'm_capacity' la capacité du vec. </summary>
		/// <remarks>: utilise l'opérateur ostream sur le type T </remarks>
		template<typename U>
		friend std::ostream& operator<<(std::ostream& os, const vec<U>& dt);

		/// <summary> Permute deux vecs donnés en paramètres dont les types d'éléments, T, sont identiques. </summary>
		template<typename U>
		friend void swap(vec<U>& lhs, vec<U>& rhs) noexcept;

		//----------------------------------------------- Constructeurs - destructeur

		/// <summary> Constructeur par default ou constructeur définissant les opérateurs utilisés pour faire des comparaisons entre éléments </summary>
		///	<param name='eq_pred'> Pointeur vers la fonction qui sera utilisée pour faire l'égalité entre deux éléments </param>
		///	<param name='comp_inf_pred'> Pointeur vers la fonction qui sera utilisée pour faire une comparaison 'inférieur à' entre deux éléments </param>
		vec(predicate eq_pred = &default_equality_predicate<T>, predicate comp_inf_pred = &default_inferior_comp_predicate<T>);
		
		/// <summary> Constructeur de copie </summary>
		vec(const vec& other);

		/// <summary> Move constructeur </summary>
		vec(vec&& other) noexcept;

		/// <summary> Constructeur d'un vec de taille pré-allouée et de taille maximum données </summary>
		///	<param name='capacity'> Taille du nouveau vec </param>
		///	<param name='max_capacity'> Taille maximum du nouveau vec </param>
		///	<param name='eq_pred'> Pointeur vers la fonction qui sera utilisée pour faire l'égalité entre deux éléments </param>
		///	<param name='comp_inf_pred'> Pointeur vers la fonction qui sera utilisée pour faire une comparaison 'inférieur à' entre deux éléments </param>
		explicit vec(size_type capacity, size_type max_capacity = MAX_ALLOCATION_SIZE, predicate eq_pred = &default_equality_predicate<T>, predicate comp_inf_pred = &default_inferior_comp_predicate<T>);

		/// <summary> Constructeur d'un vec à partir d'un ensemble d'éléments donné en paramètre </summary>
		///	<param name='vals'> tableau des éléments qui seront ajoutés au vec </param>
		///	<param name='size'> taille du tableau vals </param>
		// Non type-safe, TODO: utiliser gsl::array_view, std::array et/ou std::initializer_list
		//vec(const T vals[], size_type size);

		/// <summary> Destructeur de la colection courante </summary>
		virtual ~vec();

		//------------------------------------------------------ Constantes publiques

		static const size_type MAX_ALLOCATION_SIZE = std::numeric_limits<size_type>::max() - 1;

		//--------------------------------------------------------------------- PRIVE 
	protected:
		//-------------------------------------------------------- Méthodes protégées
		/// <summary> Réalloue la mémoire pour le tableau m_vals.
		///		La nouvelle capacité du vecteur sera la plus petite puissance de 2 superieure au double de la capacité actuelle </summary>
		inline void reallocateMemory();

		/// <summary> Algorithme récursif Quicksort </summary>
		inline void quickSort(size_type p, size_type q) const;

		/// <summary> Fonction de partition utilisée pour l'algorithme Quicksort </summary>
		inline size_type partition(size_type p, size_type q) const;

		/// <summary> Fonction de partition utilisée pour l'algorithme Quicksort.
		///		Utilise les prédicats donnés en paramètre pour faire la comparaison 'inférieure à' et l'égalité entre deux éléments de type T </summary>
		size_type dichoto(const size_type beg_idx, const size_type end_idx, const T& val) const;

		/// <summary> Trouve le nombre d'éléments apparetenant à la fois à 'm_vals' et au paramètre 'vals_to_find' </summary>
		///	<param name='vals_to_find'> tableau d'éléments de type T qui seront recherchés dans le vec </param>
		///	<param name='size'> taille du tableau 'vals_to_find' </param>
		///	<returns> le nombre d'éléments apparetenant à la fois à 'm_vals' et à 'vals_to_find' </returns>
		unsigned int find_all_of(const T vals_to_find[], size_type size) const;

		/// <summary> Désalloue la mémoire allouée pour le tableau d'objets de type T </summary>
		void dispose();

		//----------------------------------------------- Fonctions statiques protégés

		// ces fonctions sont statiques car elles n'on aucuns liens avec une instance si ce n'est le type des objets en argument
		// (évite des problème liés au fait de marquer ces fonction 'const' ou non)

		/// <summary> Simple fonction utilisant l'opérateur '==' pour comparer deux objets de type T </summary>
		template<typename U>
		inline static bool default_equality_predicate(const U& a, const U& b) { return a == b; };
		/// <summary> Simple fonction utilisant l'opérateur 'inferieur à' pour comparer deux objets de type T </summary>
		template<typename U>
		inline static bool default_inferior_comp_predicate(const U& a, const U& b) { return a < b; };

		//--------------------------------------------------------- Attributs protégés

		/// Tableau de T
		T* m_vals = nullptr;
		/// Taille du tableau m_vals
		size_type m_capacity = 0;
		/// Taille maximale du tableau m_vals
		const size_type m_max_capacity = MAX_ALLOCATION_SIZE;
		/// Taille utilisée du tableau m_vals
		size_type m_size = 0;
		/// Booleen indiquant si le vecteur peut être considèré comme trié
		bool m_is_sorted = false;
		/// Pointeur vers la fonction qui sera utilisée pour faire l'égalité entre deux éléments 
		predicate m_eq_pred = default_equality_predicate;
		/// Pointeur vers la fonction qui sera utilisée pour faire une comparaison 'inférieur à' entre deux éléments
		predicate m_comp_inf_pred = default_equality_predicate;

		//------------------------------------------------------- Constantes protégées

		static const size_type INITIAL_ALLOCATION_SIZE = 4;
	};

	//--------------------- Implémentation de la classe vec<T> -----------------------

	//------------------------------------------------------------------------- PUBLIC

	template<typename T>
	void vec<T>::add(const T& val_to_add)
	{
		// Reallocate memory if we don't have free space anymore
		if (m_size == m_capacity) // TODO: unlikely
			reallocateMemory();

		// Append/Copy new value
		m_vals[m_size] = val_to_add;
		++m_size;

		m_is_sorted = false; // We assume vector is no more sorted
	}

	template<typename T>
	template<typename... CtorArgsTypes>
	T& vec<T>::add(CtorArgsTypes&&... ctor_args)
	{
		m_is_sorted = false; // We assume vector is no more sorted

		// Reallocate memory if we don't have free space anymore
		if (m_size == m_capacity) // TODO: unlikely
			reallocateMemory();

		// Just call T constructor with specified arguments without any memory allocation
		new (m_vals + m_size) T(std::forward<CtorArgsTypes>(ctor_args)...);
		return m_vals[m_size++];
	}

	template<typename T>
	bool vec<T>::add(const vec& other)
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

		m_is_sorted = false; // We assume vector is no more sorted
		return true;
	}

	template<typename T>
	bool vec<T>::remove(const T vals_to_remove[], size_type size)
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
					if (m_eq_pred(vals_to_remove[j],val))
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
	bool vec<T>::remove(const T& old_value)
	{
		return retirer(&old_value, 1);
	}

	template<typename T>
	bool vec<T>::ajust(size_type new_capacity)
	{
		if (new_capacity < m_size || new_capacity == m_capacity)
			return false; // We forbid any element removal during a 'vec::ajust' call

		if (new_capacity == 0)
		{
			// We know that 'm_size == 0', 'm_capacity > 0' and 'm_vals != nullptr' 
			// We free all pre-allocated memory and return:
			dispose();
			return true;
		}

		// Allocate a new array of T objects
		T* new_vals = new T[new_capacity];

		// If this vec have any T objects, we copy them to 'new_vals' and we delete 'm_vals'
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

	template<typename T>
	typename vec<T>::size_type vec<T>::find(const T& element_to_find) const
	{
		if (m_size > 0) // TODO: LIKELY
		{
			if (m_is_sorted)
			{
				if (m_size != 1)
					// Dichotomic search
					return dichoto(0, m_size - 1, element_to_find);
				else
					return m_eq_pred(element_to_find, m_vals[0]) ? 0 : MAX_ALLOCATION_SIZE + 1;
			}
			else
			{
				// Simple loop over vector elements
				for (size_type i = 0; i < m_size; ++i)
					if (m_eq_pred(element_to_find, m_vals[i]))
						return i;
			}
		}
		return static_cast<size_type>(-1);
	}

	template<typename T>
	void vec<T>::sort()
	{
		// Use quick sort algorithm to sort elements
		quickSort(0, m_size);

		m_is_sorted = true;
	}

	template<typename T>
	typename vec<T>::size_type vec<T>::length() const { return m_size; }

	template<typename T>
	typename vec<T>::size_type vec<T>::capacity() const { return m_capacity; }

	//---------------------------------------------------- Constructeurs - destructeur

	template<typename T>
	vec<T>::vec(predicate eq_pred = &default_equality_predicate<T>, predicate comp_inf_pred = &default_inferior_comp_predicate<T>)
		: m_eq_pred(eq_pred), m_comp_inf_pred(comp_inf_pred)
	{
#ifdef MAP
		cout << "Appel au constructeur 'vec<T>::vec(predicate eq_pred = &default_equality_predicate<T>, predicate comp_inf_pred = &default_inferior_comp_predicate<T>)'" << endl;
#endif
	}

	template<typename T>
	vec<T>::vec(vec&& other) noexcept
		: vec()
	{
#ifdef MAP
		cout << "Appel au move-constructeur 'vec<T>::vec(vec<T>&&)'" << endl;
#endif
		swap(*this, other);
	}

	template<typename T>
	vec<T>::vec(const vec& other)
		: vec(other.m_capacity)
	{
#ifdef MAP
		cout << "Appel au constructeur de copie 'vec<T>::vec(const vec<T>&)'" << endl;
#endif
		m_size = other.m_size;
		try // T's copy assignment operator could throw and let vec in incoherent state
		{
			// Copy 'other' vec elements
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
	vec<T>::vec(size_type capacity, size_type max_capacity = MAX_ALLOCATION_SIZE, predicate eq_pred = &default_equality_predicate<T>, predicate comp_inf_pred = &default_inferior_comp_predicate<T>)
		: m_capacity(capacity), m_max_capacity(max_capacity), m_eq_pred(eq_pred), m_comp_inf_pred(comp_inf_pred)
	{
#ifdef MAP
		cout << "Appel au constructeur 'vec<T>::vec(size_type, predicate eq_pred = &default_equality_predicate<T>, predicate comp_inf_pred = &default_inferior_comp_predicate<T>)'" << endl;
#endif

		if (capacity > 0)
			m_vals = new T[capacity];
		else
			m_vals = nullptr;
	}

	/*template<typename T>
	vec<T>::vec(const T vals[], size_type size)
	{
#ifdef MAP
		cout << "Appel au constructeur 'vec<T>::vec(const T[], size_type)'" << endl;
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
	}*/

	template<typename T>
	vec<T>::~vec()
	{
#ifdef MAP
		cout << "Appel au destructeur de 'vec<T>'" << endl;
#endif
		// On désalloue la mémoire allouée pour le tableau de T si nescessaire
		dispose();
	}

	//-------------------------------------------------------- Surcharges d'opérateurs
	template<typename T>
	const vec<T>& vec<T>::operator=(vec other)
	{
		// Copy and swap idiom (in 'rule of 4' context (copy elision))
		swap(*this, other);
		return *this;
	}

	template<typename T>
	T vec<T>::operator[](size_type idx) const { return m_vals[idx]; }

	template<typename T>
	T& vec<T>::operator[](size_type idx) {
		return m_vals[idx];
	}

	template<typename U>
	std::ostream& operator<<(std::ostream& os, const vec<U>& vec)
	{
		if (vec.m_size > 0)
		{
			os << "({ ";

			for (typename vec<U>::size_type i = 0; i < vec.m_size; ++i)
				os << vec.m_vals[i] << ((i < vec.m_size - 1) ? ", " : " }, ");

			os << vec.m_capacity << ")";
		}
		else
			os << "({ }, " << vec.m_capacity << ")";

		return os;
	}

	template<typename U>
	void swap(vec<U>& lhs, vec<U>& rhs) noexcept
	{
		// if one of the following swap calls isn't noexcept, we raise a static_assert
		static_assert(is_nothrow_swappable<typename vec<U>::size_type, U*>(), "Swap function could throw and let vec<T> objects in incoherant state!");

		// enable ADL (following lines will use custom implementation of swap or std::swap if there isn't custom implementation)
		using std::swap;

		swap(lhs.m_size, rhs.m_size);
		swap(lhs.m_capacity, rhs.m_capacity);
		swap(lhs.m_vals, rhs.m_vals);
	}

	//-------------------------------------------------------------------------- PRIVE

	//------------------------------------------------------------- Méthodes protégées

	template<typename T>
	inline void vec<T>::reallocateMemory()
	{
		// Take a power of two capacity greater than 2 * m_size
		if (m_size > 0) // TODO: likely
		{
			size_type powOf2_size = lowestPowOfTwoGreaterThan(2 * m_size);
			ajust(powOf2_size < m_max_capacity ? powOf2_size : m_max_capacity);
		}
		else
			ajust(INITIAL_ALLOCATION_SIZE);
	}

	template<typename T>
	inline void vec<T>::quickSort(size_type p, size_type q) const
	{
		if (p < q)
		{
			size_type r = partition(p, q);
			quickSort(p, r);
			quickSort(r + 1, q);
		}
	}

	template<typename T>
	inline typename vec<T>::size_type vec<T>::partition(size_type p, size_type q) const
	{
		// enable ADL (following lines will use custom implementation of swap or std::swap if there isn't custom implementation)
		using std::swap;

		T val = m_vals[p];
		size_type i = p;

		for (size_type j = p + 1; j < q; ++j)
			if (!(m_comp_inf_pred(val, m_vals[j])))
				swap(m_vals[++i], m_vals[j]);

		swap(m_vals[i], m_vals[p]);
		return i;
	}

	template<typename T>
	typename vec<T>::size_type vec<T>::dichoto(size_type beg_idx, size_type end_idx, const T& val) const
	{
		while (beg_idx <= end_idx)
		{
			// get middle index
			const size_type mid_idx = beg_idx + ((end_idx - beg_idx) / 2);

			if (m_eq_pred(m_vals[mid_idx], val)) // TODO: UNLIKELY
				return mid_idx;			// return the index of the element we found
			else if (m_comp_inf_pred(m_vals[mid_idx], val))
				beg_idx = mid_idx + 1;	// we split the right part
			else
				end_idx = mid_idx - 1;	// we split the left part
		}
		return MAX_ALLOCATION_SIZE + 1;	// Not found
	}

	template<typename T>
	unsigned int vec<T>::find_all_of(const T vals_to_find[], size_type size) const
	{
		unsigned int matches_count = 0;

		if (size > 0 && vals_to_find != nullptr && m_size > 0) // TODO: UNLIKELY
		{
			for (size_type idx2 = 0; idx2 < size; ++idx2)
			{
				if (find(vals_to_find[idx2]) < m_size)
					++matches_count;
			}
		}

		return matches_count;
	}

	template<typename T>
	void vec<T>::dispose()
	{
		if (m_vals != nullptr)
		{
			delete[] m_vals;
			m_vals = nullptr;
			m_size = 0;
			m_capacity = 0;
		}
	}

	//------------------------------------------------------------ Fonctions statiques

/*	template<typename T>
	inline bool default_equality_predicate(const T& a, const T& b) { return a == b; }

	template<typename T>
	inline bool default_inferior_comp_predicate(const T& a, const T& b) { return a < b; }*/

}
