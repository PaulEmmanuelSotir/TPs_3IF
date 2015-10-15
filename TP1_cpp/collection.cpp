/*************************************************************************
				collection  -  A collection of dogs
				-----------------------------------
début                : 01/10/2015
copyright            : (C) 2015 par B3311
Distributed under the MIT License.(See http://opensource.org/licenses/MIT)
*************************************************************************/

//---------- Réalisation de la classe <collection{file_base}> (fichier collection{file_name}) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>

//------------------------------------------------------ Include personnel
#include "collection.h"

//------------------------------------------------------------- Constantes

//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés


//----------------------------------------------------------------- PUBLIC

void collection::afficher() const
{
	if (m_size > 0)
		std::cout << "{ ";
	else
		std::cout << "{ }";

	for (size_t i = 0; i < m_size; ++i)
		std::cout << m_dogs[i]->age << ((i < m_size - 1) ? ", " : " }");
}

bool collection::ajouter(dog* new_dog)
{
	if (new_dog == nullptr)
		return false;

	// Reallocate memory if we don't have free space anymore
	if (m_size == m_capacity)
	{
		// Double capacity at each new allocations
		if (!ajuster(m_size != 0 ? 2 * m_size : INITIAL_ALLOCATION_SIZE))
			return false;
	}

	// Append new dog value
	m_dogs[m_size++] = new_dog;

	return true;
}

bool collection::retirer(const dog *const * dogs, size_t size)
{
	if (dogs == nullptr || size == 0 || m_dogs == nullptr)
		return false;

	size_t new_size = m_size - size;
	dog** new_dogs = new dog*[new_size];
	if (new_dogs == nullptr)
		return false;
	for (size_t i = 0; i < m_size; i++)
	{
		int compteur = 0;
		bool exist = false;
		for (size_t j = 0; j < size; j++)
		{
			if (m_dogs[i] == dogs[j])
			{
				exist = true;
				delete m_dogs[i];
				m_dogs[i] = nullptr;
			}
		}
		if (!exist)
		{
			new_dogs[compteur] = m_dogs[i];
			compteur++;
		}
	}
	delete[] m_dogs;
	m_dogs = new_dogs;

	m_size = new_size;
	m_capacity = new_size; // As specified, we need to avoid any unused allocated memory after a 'collection::retirer(...)' call

	return true;
}

bool collection::retirer(const dog& old_dog)
{
	const dog *const ptr = &old_dog;
	return retirer(&ptr, 1);
}

bool collection::ajuster(size_t new_size)
{
	if (new_size <= m_size)
		return false;

	dog** new_dogs = new dog*[new_size];
	if (new_dogs == nullptr)
		return false;

	for (size_t i = 0; i < m_size; i++)
		new_dogs[i] = m_dogs[i];
	m_capacity = new_size;

	if (m_dogs != nullptr)
		delete[] m_dogs;
	m_dogs = new_dogs;

	return true;
}

bool collection::reunir(const collection& other)
{
	// Allocate a new array of dog pointers
	dog** new_dogs = new dog*[2 * (m_size + other.m_size)];
	if (new_dogs == nullptr)
		return false;

	if (other.m_dogs != nullptr)
		for (size_t i = 0; i < other.m_size; i++)
			new_dogs[i + m_size] = other.m_dogs[i];

	if (m_dogs != nullptr)
	{
		for (size_t i = 0; i < m_size; i++)
			new_dogs[i] = m_dogs[i];

		delete[] m_dogs;
	}

	m_dogs = new_dogs;
	m_size = m_size + other.m_size;
	m_capacity = 2 * m_size;

	return true;
}


//-------------------------------------------- Constructeurs - destructeur
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

collection::collection(dog** dogs, size_t size)
{
#ifdef MAP
	cout << "Appel au constructeur 'collection::collection(dog*, size_t)'" << endl;
#endif

	m_capacity = size;
	m_size = size;

	if (size > 0)
	{
		m_dogs = new dog*[size];
		if (m_dogs != nullptr)
		{
			if (dogs != nullptr)
			{
				// Copy given dogs pointers
				for (size_t i = 0; i < size; ++i)
					m_dogs[i] = dogs[i];
			}
			else
				m_dogs = nullptr;
		}
		else
		{
			// uh oh, dynamic allocation failed...
			m_size = 0;
			m_capacity = 0;
			return;
		}
	}
}

collection::~collection()
// Algorithme :
//
{
#ifdef MAP
	cout << "Appel au destructeur de 'collection'" << endl;
#endif

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
	}
} //----- Fin de ~collection{file_base}

  //------------------------------------------------------------------ PRIVE

  //----------------------------------------------------- Méthodes protégées

  //------------------------------------------------------- Méthodes privées
