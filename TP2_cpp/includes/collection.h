/*********************************************************************************
					collection  -  A dynamic and generic collection
					-----------------------------------------------
date                 : 10/2015
copyright            : (C) 2015 by B3311
*********************************************************************************/

//-------------------- Interface de la classe collection<T> ----------------------
#pragma once

//----------------------------------------------------------- Interfaces utilisées

namespace TP1
{
	//----------------------------------------------------------------------------
	// collection:
	// classe qui permet de manipuler une collection d'objets de type T
	//----------------------------------------------------------------------------
	template<typename T>
	class collection
	{
		//----------------------------------------------------------------- PUBLIC
	public:
		using size_type = size_t;

		//----------------------------------------------------- Méthodes publiques

		// Description : affiche la valeur de la collection.
		//	La valeur de la collection est affichée sous la forme : "({ <val1>, <val2>, ... }, <m_capacity>)"
		//	avec <val1>, <val2>, ... les âges des chiens et <m_capacity> la capacité de la collection.
		void afficher() const;

		// Description: ajoute val_to_add dans la collection courante
		//		val_to_add: reférence constante vers une valeur de type T qui sera ajouté dans la collection
		void ajouter(const T& val_to_add);

		// Description: retire old_val de la collection courante
		//		old_val: reference vers un T qui sera retiré de la collection
		//		RETOURNE: Un booléen indiquant si au moins un élément a bien été retiré
		//	NOTE: ajuste la capacité de la collection au minimum même si old_val n'est pas présent dans la collection 
		bool retirer(const T& old_val);

		// Description: retire l'ensemble des valeurs contenues dans le parametre 'vals' de la collection courante
		//		vals: tableau de T qui seront retirés de la collection
		//		size: taille du tableau vals
		//		RETOURNE: Un booléen indiquant si au moins un élément a bien été retiré
		//	NOTE: ajuste la capacité de la collection au minimum même si aucuns éléments de vals n'est pas présent dans la collection 
		bool retirer(const T vals[], size_type size);

		// Description: ajuste, si possible, la capacité de la collection à la taille spécifiée
		//		capacity: nouvelle taille de mémoire allouée pour la structure de donnée interne
		//		RETOURNE: Un booléen indiquant si un ajustement de la capacité a bien été effectué
		bool ajuster(size_type capacity);

		// Description: ajoute le contenu de la collection donnée en paramètre 
		//		other: reference vers la collection à réunir avec la collection courante
		//		RETOURNE: Un booléen indiquant si des éléments de 'other' on bien été ajoutés à la collection
		bool reunir(const collection& other);

		//------------------------------------------------- Surcharge d'opérateurs
		T& operator[](size_type idx);
		T operator[](size_type idx) const;

		//-------------------------------------------- Constructeurs - destructeur
		// Constructeur par default
		collection() = default;

		// Description: Constructeur d'une collection de taille pré-allouée donnée
		//		capacity: Taille de la nouvelle collection
		explicit collection(size_type capacity);

		// Description: Constructeur d'une collection à partir d'un ensemble d'éléments donné en paramètre
		//		vals: tableau des éléments qui seront ajoutés à la collection
		//		size: taille du tableau vals
		collection(const T vals[], size_type size);

		// Description: Destructeur de la colection courante
		virtual ~collection();

		//------------------------------------------------------------------ PRIVE 
	protected:
		//----------------------------------------------------- Méthodes protégées

		// Description: Trouve le nombre d'éléments apparetenant à la fois à 'm_vals' 
		//	et au paramètre 'vals_to_find'
		//		vals_to_find: tableau d'éléments de type T qui seront recherchés dans la collection
		//		size: taille du tableau 'vals_to_find'
		//		RETOURNE: le nombre d'éléments apparetenant à la fois à 'm_vals' et à 'vals_to_find'
		unsigned int find_all_of(const T vals_to_find[], size_type size) const;

		// Description: Désalloue la mémoire allouée pour le tableau de pointeur de T 
		//	et pour les objets de type T.
		void disposeValues();

		//----------------------------------------------------- Attributs protégés

		// Tableau de pointeurs de T
		T** m_vals = nullptr;
		// Taille du tableau m_vals
		size_type m_capacity = 0;
		// Taille utilisée du tableau m_vals
		size_type m_size = 0;

		//---------------------------------------------------- Constantes protégés

		static const size_type INITIAL_ALLOCATION_SIZE = 5;
	};

	//------------------ Implémentation de la classe collection<T> -------------------

	//------------------------------------------------------------------------- PUBLIC
	template<typename T>
	void collection<T>::afficher() const
	{
		if (m_size > 0)
		{
			std::cout << "({ ";

			for (size_type i = 0; i < m_size; ++i)
				std::cout << m_vals[i] << ((i < m_size - 1) ? ", " : " }, ");

			std::cout << m_capacity << ")";
		}
		else
			std::cout << "({ }, " << m_capacity << ")";
	}

	template<typename T>
	void collection<T>::ajouter(const T& val_to_add)
	{
		// Copy given value
		T* new_val = new T(val_to_add);

		// Reallocate memory if we don't have free space anymore
		if (m_size == m_capacity)
		{
			// Double capacity at each new allocations
			ajuster(m_size > 0 ? 2 * m_size : INITIAL_ALLOCATION_SIZE);
		}

		// Append new value
		m_vals[m_size++] = new_val;
	}

	template<typename T>
	bool collection<T>::retirer(const T vals_to_remove[], size_type size)
	{
		if (vals_to_remove == nullptr || size == 0 || m_vals == nullptr)
		{
			ajuster(m_size); // As specified, we always allocate the shorter amount of memory possible (m_size == m_capacity) after 'retirer(...)' is called
			return false;
		}

		// Find the number of elements to remove and get the index of the first one
		unsigned int removes_todo_count = find_all_of(vals_to_remove, size);

		if (removes_todo_count == 0)
		{
			// There isn't any element to remove
			ajuster(m_size); // As specified, we always allocate the shorter amount of memory possible (m_size == m_capacity) after 'retirer(...)' is called
			return false;
		}

		if (removes_todo_count >= m_size)
			disposeVal(); // We remove all elements
		else
		{
			size_type new_size = m_size - removes_todo_count;
			T** new_vals = new T*[new_size];

			// Copy 'm_vals' values in 'new_vals' except those present in 'vals_to_remove'
			size_type removes_count = 0;
			for (size_type i = 0; i < m_size; ++i)
			{
				auto val = m_vals[i];

				// Check if 'm_vals[i]' is in 'vals_to_remove'
				bool is_to_copy = true;
				for (size_type j = 0; j < size && removes_count < removes_todo_count; ++j)
				{
					if (vals_to_remove[j] == *(val))
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
	bool collection<T>::retirer(const T& old_value)
	{
		return retirer(&old_value, 1);
	}

	template<typename T>
	bool collection<T>::ajuster(size_type new_capacity)
	{
		if (new_capacity < m_size || new_capacity == m_capacity)
			return false; // We forbid any element removal during an 'collection::ajuster' call

		if (new_capacity == 0)
		{
			// We know that 'm_size == 0', 'm_capacity > 0' and 'm_vals != nullptr' 
			// We free all pre-allocated memory:
			delete[] m_vals;
			m_vals = nullptr;
			m_capacity = 0;
			return true;
		}

		// Allocate a new array of T pointers
		T** new_vals = new T*[new_capacity];

		// If this collection have any T pointers, we copy them to 'new_vals' and we delete 'm_vals'
		if (m_vals != nullptr)
		{
			for (size_type i = 0; i < m_size; i++)
				new_vals[i] = m_vals[i];

			delete[] m_vals;
		}

		// Assign the new array to 'm_vals' and update 'm_capacity'
		m_vals = new_vals;
		m_capacity = new_capacity;

		return true;
	}

	template<typename T>
	bool collection<T>::reunir(const collection& other)
	{
		if (other.m_size == 0 || other.m_vals == nullptr)
			return false; // We don't have any elements to append

		if (m_capacity - m_size >= other.m_size)
		{
			// We have enought free allocated space to store other.m_vals in m_valss
			for (size_type i = 0; i < other.m_size; ++i)
				m_vals[m_size + i] = new T(*(other.m_vals[i]));

			m_size += other.m_size;
		}
		else
		{
			// Allocate a new array of T pointers
			T** new_vals = new T*[2 * (m_size + other.m_size)];

			// Copy other.m_vals to new_vals
			for (size_type i = 0; i < other.m_size; i++)
				new_vals[i + m_size] = new T(*(other.m_vals[i]));

			if (m_vals != nullptr)
			{
				// Copy m_vals pointers to new_vals
				for (size_type i = 0; i < m_size; ++i)
					new_vals[i] = m_vals[i];

				delete[] m_vals;
			}

			// Assign the new array to 'm_vals' and update 'm_capacity' and 'm_size'
			m_vals = new_vals;
			m_size += other.m_size;
			m_capacity = 2 * m_size;
		}

		return true;
	}

	//---------------------------------------------------- Constructeurs - destructeur
	template<typename T>
	collection<T>::collection(size_type capacity)
	{
#ifdef MAP
		cout << "Appel au constructeur 'collection::collection(size_type)'" << endl;
#endif

		if (capacity > 0)
			m_vals = new T*[capacity];
		else
			m_vals = nullptr;
		m_capacity = capacity;
	}

	template<typename T>
	collection<T>::collection(const T vals[], size_type size)
	{
#ifdef MAP
		cout << "Appel au constructeur 'collection::collection(const T[], size_type)'" << endl;
#endif

		if (size > 0 && vals != nullptr)
		{
			m_capacity = size;
			m_size = size;

			// Create a new array of T pointers
			m_vals = new T*[size];

			// Copy given elements
			for (size_type i = 0; i < size; ++i)
				m_vals[i] = new T(vals[i]);
		}
	}

	template<typename T>
	collection<T>::~collection()
	{
#ifdef MAP
		cout << "Appel au destructeur de 'collection'" << endl;
#endif
		// On désalloue la mémoire allouée pour le tableau de pointeur de T et pour les objets de type T eux-même
		disposeValues();
	} //----- Fin de ~collection{file_base}

	//-------------------------------------------------------- Surcharges d'opérateurs
	template<typename T>
	T& collection<T>::operator[](size_type idx)
	{
		return *m_vals[idx];
	}

	template<typename T>
	T collection<T>::operator[](size_type idx) const
	{
		return *m_vals[idx];
	}

	//-------------------------------------------------------------------------- PRIVE

	//------------------------------------------------------------- Méthodes protégées
	template<typename T>
	unsigned int collection<T>::find_all_of(const T vals_to_find[], size_type size) const
	{
		unsigned int matches_count = 0;

		if (size > 0 && vals_to_find != nullptr && m_size > 0)
		{
			for (size_type idx = m_size - 1; idx < m_size; --idx)
			{
				for (size_type idx2 = 0; idx2 < size; ++idx2)
				{
					if (*(m_vals[idx]) == vals_to_find[idx2])
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
	void collection<T>::disposeValues()
	{
		if (m_vals != nullptr)
		{
			for (size_type i = 0; i < m_size; ++i)
			{
				T* val_ptr = m_vals[i];
				if (val_ptr != nullptr)
					delete val_ptr;
				m_vals[i] = nullptr;
			}
			delete[] m_vals;
			m_vals = nullptr;

			m_size = 0;
			m_capacity = 0;
		}
	}
}