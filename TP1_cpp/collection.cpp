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
	if (used_size > 0)
		std::cout << "{ ";
	else
		std::cout << "{ }";

	for (size_t i = 0; i < used_size; ++i)
		std::cout << dogs[i]->getAge() << ((i < used_size - 1) ? ", " : " }");
}

bool collection::ajouter(dog* dog)
{
	if (dog == nullptr)
		return false;

	if (used_size == max_size)
	{
		if (!ajuster(max_size + ALLOCATION_STEP))
			return false;
	}
	dogs[used_size] = dog;
	used_size++;

	return true;
}

bool collection::retirer(const dog *const * dogs, size_t size)
{
	if (dogs == nullptr || size == 0 || this->dogs == nullptr)
		return false;

	size_t new_size = used_size - size;
	dog** new_dogs = new dog*[new_size];
	if (new_dogs == nullptr)
		return false;
	for (size_t i = 0; i < used_size; i++)
	{
		int compteur = 0;
		bool exist = false;
		for (size_t j = 0; j < size; j++)
		{
			if (this->dogs[i] == dogs[j])
			{
				exist = true;
				delete this->dogs[i];
				this->dogs[i] = nullptr;
			}
		}
		if (!exist)
		{
			new_dogs[compteur] = this->dogs[i];
			compteur++;
		}
	}
	delete[] this->dogs;
	this->dogs = new_dogs;

	return true;
}

bool collection::retirer(const dog& old_dog)
{
	const dog *const ptr = &old_dog;
	return retirer(&ptr, 1);
}

bool collection::ajuster(size_t new_size)
{
	if (new_size <= used_size)
		return false;

	dog** new_dogs = new dog*[new_size];
	if (new_dogs == nullptr)
		return false;

	for (size_t i = 0; i < used_size; i++)
		new_dogs[i] = dogs[i];
	max_size = new_size;

	if (dogs != nullptr)
		delete[] dogs;
	dogs = new_dogs;

	return true;
}

bool collection::reunir(const collection& other)
{
	dog** new_dogs = new dog*[used_size + other.used_size + ALLOCATION_STEP];
	if (new_dogs == nullptr)
		return false;

	if (other.dogs != nullptr)
		for (size_t i = 0; i < other.used_size; i++)
			new_dogs[i + this->used_size] = other.dogs[i];

	if (this->dogs != nullptr)
	{
		for (size_t i = 0; i < used_size; i++)
			new_dogs[i] = this->dogs[i];

		delete[] this->dogs;
	}

	this->dogs = new_dogs;
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
		this->dogs = new dog*[capacity];
	else
		this->dogs = nullptr;
	this->max_size = capacity;
} //----- Fin de collection{file_base} (constructeur de copie)

collection::collection(dog** dogs, size_t size)
{
#ifdef MAP
	cout << "Appel au constructeur 'collection::collection(dog*, size_t)'" << endl;
#endif

	this->max_size = size;
	this->used_size = size;

	if (size > 0)
	{
		this->dogs = new dog*[size];
		if (dogs != nullptr)
		{
			for (size_t i = 0; i < size; ++i)
				this->dogs[i] = dogs[i];
		}
	}
	else
		this->dogs = nullptr;
}

collection::~collection()
// Algorithme :
//
{
#ifdef MAP
	cout << "Appel au destructeur de 'collection'" << endl;
#endif

	if (dogs != nullptr)
	{
		for (size_t i = 0; i < used_size; ++i)
		{
			dog* dog_ptr = dogs[i];
			if (dog_ptr != nullptr)
				delete dog_ptr;
			dogs[i] = nullptr;
		}
		delete[] dogs;
		dogs = nullptr;
	}
} //----- Fin de ~collection{file_base}

  //------------------------------------------------------------------ PRIVE

  //----------------------------------------------------- Méthodes protégées

  //------------------------------------------------------- Méthodes privées
