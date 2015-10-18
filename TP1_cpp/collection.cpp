/*********************************************************************************
				collection  -  A collection of dogs
				-----------------------------------
date				: 01/10/2015
copyright			: (C) 2015 par B3311
Distributed under the MIT License.(See http://opensource.org/licenses/MIT)
*********************************************************************************/

//------- Réalisation de la classe <collection.h> (fichier collection.cpp) -------

//------------------------------------------------------------------------ INCLUDE

//---------------------------------------------------------------- Include système
#include <iostream>

//-------------------------------------------------------------- Include personnel
#include "collection.h"

namespace TP1
{
	//------------------------------------------------------------------------- PUBLIC
	void collection::afficher() const
	{
		if (m_size > 0)
			std::cout << "{ ";
		else
			std::cout << "{ }";

		for (size_t i = 0; i < m_size; ++i)
			std::cout << m_dogs[i]->age << ((i < m_size - 1) ? ", " : " }");
	}

	bool collection::ajouter(const dog& dog_to_add)
	{
		// Copy given dog
		dog* new_dog = new dog(dog_to_add);

		// Reallocate memory if we don't have free space anymore
		if (m_size == m_capacity)
		{
			// Double capacity at each new allocations
			if (!ajuster(m_size > 0 ? 2 * m_size : INITIAL_ALLOCATION_SIZE))
				return false;
		}

		// Append new dog value
		m_dogs[m_size++] = new_dog;

		return true;
	}

	bool collection::retirer(const dog dogs_to_remove[], size_t size)
	{
		if (dogs_to_remove == nullptr || size == 0 || m_dogs == nullptr)
		{
			ajuster(m_size); // As specified, we always allocate the shorter amount of memory possible (m_size == m_capacity) after 'retirer(...)' is called
			return false;
		}

		// Find the number of dog to remove and get the index of the first one
		unsigned int removes_todo_count = find_all_of(dogs_to_remove, size);

		if (removes_todo_count == 0)
		{
			// There isn't any dog to remove
			ajuster(m_size); // As specified, we always allocate the shorter amount of memory possible (m_size == m_capacity) after 'retirer(...)' is called
			return false;
		}

		if (removes_todo_count >= m_size)
			disposeDogs(); // We remove all dogs
		else
		{
			size_t new_size = m_size - removes_todo_count;
			dog** new_dogs = new dog*[new_size];

			// Copy 'm_dogs' dogs in 'new_dogs' except those present in 'dogs_to_remove'
			size_t removes_count = 0;
			for (size_t i = 0; i < m_size; ++i)
			{
				auto dog = m_dogs[i];

				// Check if 'm_dogs[i]' is in 'dogs_to_remove'
				bool is_to_copy = true;
				for (size_t j = 0; j < size && removes_count < removes_todo_count; ++j)
				{
					if (dogs_to_remove[j] == *(dog))
					{
						++removes_count;
						is_to_copy = false;
					}
				}

				if (is_to_copy)
					new_dogs[i - removes_count] = dog;
			}

			delete[] m_dogs;
			m_dogs = new_dogs;
			m_size = new_size;
			m_capacity = new_size;
		}

		return true;
	}

	bool collection::retirer(const dog& old_dog)
	{
		return retirer(&old_dog, 1);
	}

	bool collection::ajuster(size_t new_capacity)
	{
		if (new_capacity < m_size || new_capacity == m_capacity)
			return false;

		if (new_capacity == 0)
		{
			// m_size == 0 and we want to free all pre-allocated memory (m_capacity > 0 && m_dogs != nullptr)
			delete[] m_dogs;
			m_dogs = nullptr;
			return true;
		}

		dog** new_dogs = new dog*[new_capacity];

		if (m_dogs != nullptr)
		{
			for (size_t i = 0; i < m_size; i++)
				new_dogs[i] = m_dogs[i];

			delete[] m_dogs;
		}

		m_dogs = new_dogs;
		m_capacity = new_capacity;

		return true;
	}

	bool collection::reunir(const collection& other)
	{
		if (other.m_size == 0 || other.m_dogs == nullptr)
			return false; // We don't have any dogs to append

		if (m_capacity - m_size >= other.m_size)
		{
			// We have enought free allocated space to store other.m_dogs in m_dogs
			for (size_t i = 0; i < other.m_size; ++i)
				m_dogs[m_size + i] = new dog(*(other.m_dogs[i]));

			m_size += other.m_size;
		}
		else
		{
			// Allocate a new array of dog pointers
			dog** new_dogs = new dog*[2 * (m_size + other.m_size)];

			// Copy other.m_dogs to new_dogs
			for (size_t i = 0; i < other.m_size; i++)
				new_dogs[i + m_size] = new dog(*(other.m_dogs[i]));

			if (m_dogs != nullptr)
			{
				// Copy m_dogs pointers to new_dogs
				for (size_t i = 0; i < m_size; ++i)
					new_dogs[i] = m_dogs[i];

				delete[] m_dogs;
			}

			m_dogs = new_dogs;
			m_size += other.m_size;
			m_capacity = 2 * m_size;
		}

		return true;
	}

	//---------------------------------------------------- Constructeurs - destructeur
	collection::collection(size_t capacity)
		// Algorithme :
		//
	{
#ifdef MAP
		cout << "Appel au constructeur 'collection::collection(size_t)'" << endl;
#endif

		if (capacity > 0)
			m_dogs = new dog*[capacity];
		else
			m_dogs = nullptr;
		m_capacity = capacity;
	} //----- Fin de collection{file_base} (constructeur de copie)

	collection::collection(const dog dogs[], size_t size)
	{
#ifdef MAP
		cout << "Appel au constructeur 'collection::collection(dog*, size_t)'" << endl;
#endif

		if (size > 0 && dogs != nullptr)
		{
			m_capacity = size;
			m_size = size;

			// Create a new array of dog pointers
			m_dogs = new dog*[size];

			// Copy given dogs
			for (size_t i = 0; i < size; ++i)
				m_dogs[i] = new dog(dogs[i]);
		}
	}

	collection::~collection()
		// Algorithme :
		//
	{
#ifdef MAP
		cout << "Appel au destructeur de 'collection'" << endl;
#endif

		disposeDogs();
	} //----- Fin de ~collection{file_base}

	//-------------------------------------------------------------------------- PRIVE

	//------------------------------------------------------------- Méthodes protégées
	unsigned int collection::find_all_of(const dog dogs_to_find[], size_t size) const
	{
		unsigned int matches_count = 0;

		if (size > 0 && dogs_to_find != nullptr && m_size > 0)
		{
			for (size_t idx = m_size - 1; idx < m_size; --idx)
			{
				for (size_t idx2 = 0; idx2 < size; ++idx2)
				{
					if (*(m_dogs[idx]) == dogs_to_find[idx2])
					{
						++matches_count;
						break;
					}
				}
			}
		}

		return matches_count;
	}

	void collection::disposeDogs()
	{
		if (m_dogs != nullptr)
		{
			for (size_t i = 0; i < m_size; ++i)
			{
				dog* dog_ptr = m_dogs[i];
				if (dog_ptr != nullptr)
					delete dog_ptr;
				m_dogs[i] = nullptr;
			}
			delete[] m_dogs;
			m_dogs = nullptr;

			m_size = 0;
			m_capacity = 0;
		}
	}

}