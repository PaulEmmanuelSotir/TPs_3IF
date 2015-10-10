/*************************************************************************
collection{file_base}  -  description
-------------------
début                : collection{date}
copyright            : (C) collection{year} par collection{user}
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
/*

bool collection::ajuster(size_t new_size)
{
	if (new_size > max_size)
	{
		dog** new_dogs = new dog*[new_size];
		if (new_dogs == nullptr)
			return false;
		for (int i = 0; i < mew_size; i++)
		{
			new_dogs[i] = dogs[i];
		}
		max_size = new_size;
		delete[] dogs;
		dogs = new_dogs;
	}
	else if (new_size < used_size)
		return false;
	else
	{
		for (int i = new_size; i < max_size; i++)
		{
			delete dogs[i];
		}
		return true;
	}
}*/

bool collection::ajouter(dog* dog)
{
	if (used_size == max_size)
	{
		if (!ajuster(max_size + ALLOCATION_STEP))
			return false;
	}
	dogs[used_size] = dog;
	used_size++;
	
	return true;
}

bool collection::retirer(const dog& dog)
{
	if (dogs != nullptr)
	{

	}
	return true;
}

bool collection::retirer(const dog *const * dogs)
{

	return true;
}

bool collection::ajuster(size_t new_size)
{
	if (new_size > max_size)
	{
		dog** new_dogs = new dog*[new_size];
		if (new_dogs == nullptr)
			return false;
		for (int i = 0; i < used_size; i++)
			new_dogs[i] = dogs[i];
		max_size = new_size;
		delete[] dogs;
		dogs = new_dogs;
	}
	else if (new_size < used_size)
		return false;
	else
	{
		for (int i = new_size; i < max_size; i++)
		{
			delete dogs[i];
			dogs[i] = nullptr;
		}
		return true;
	}
}

bool collection::reunir(const collection& other)
{

	return true;
}

//-------------------------------------------- Constructeurs - destructeur
collection::collection(size_t max_size)
// Algorithme :
//
{
#ifdef MAP
	cout << "Appel au constructeur 'collection::collection(size_t)'" << endl;
#endif

	if (max_size > 0)
		this->dogs = new dog*[max_size];
	this->max_size = max_size;
} //----- Fin de collection{file_base} (constructeur de copie)

collection::collection(dog** dogs, size_t max_size)
{
#ifdef MAP
	cout << "Appel au constructeur 'collection::collection(dog*, size_t)'" << endl;
#endif

	this->max_size = max_size;
	if (max_size > 0)
		this->dogs = dogs;
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
		for (int i = 0; i < used_size; ++i)
		{
			dog* dog_ptr = dogs[i];
			if (dog_ptr != nullptr)
			{
				delete dog_ptr;
				dog_ptr = nullptr;
			}
		}
		delete[] dogs;
		dogs = nullptr;
	}
} //----- Fin de ~collection{file_base}

  //------------------------------------------------------------------ PRIVE

  //----------------------------------------------------- Méthodes protégées

  //------------------------------------------------------- Méthodes privées
