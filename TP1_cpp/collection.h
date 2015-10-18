/*****************************************************************************
				collection  -  A collection of dogs
				-----------------------------------
date                 : 01/10/2015
copyright            : (C) 2015 par B3311
Distributed under the MIT License.(See http://opensource.org/licenses/MIT)
*****************************************************************************/

//------- Interface de la classe <collection.h> (fichier collection.h) -------
#ifndef COLLECTION_H
#define COLLECTION_H

//------------------------------------------------------- Interfaces utilisées
#include "dog.h"

namespace TP1
{
	//----------------------------------------------------------------------------
	// collection:
	//----------------------------------------------------------------------------
	class collection
	{
		//----------------------------------------------------------------- PUBLIC
	public:
		//------------------------------------------------------- Usings publiques
		using size_type = size_t;
		using dog_ptr = dog*;
		using dog_cref = const dog&;
		using dog_array = dog **;
		using const_dog_array = const dog *const *;
		using collection_cref = const collection&;

		//----------------------------------------------------- Méthodes publiques
		void afficher() const;
		// Mode d'emploi : 
		// 
		// Contrat : 
		// 

		bool ajouter(dog* new_dog);
		// Mode d'emploi (constructeur de copie) :
		// NOTE: takes ownership on given new_dog and could delete it.
		// Contrat :
		//

		bool retirer(const dog& old_dog);
		// Mode d'emploi (constructeur de copie) :
		// NOTE: if given dog isn't in this collection, it won't reallocate memory for m_dogs, even if m_capacity > m_size
		// Contrat :
		//

		bool retirer(const dog *const * dogs, size_t size);
		// Mode d'emploi (constructeur de copie) :
		// NOTE: we assume size is correct
		// NOTE: if none of given dogs is in this collection, it still reallocate memory for m_dogs so that m_capacity == m_size
		// Contrat :
		//

		bool ajuster(size_t capacity);
		// Mode d'emploi (constructeur de copie) :
		// capacity >= m_size !
		// Contrat :
		//

		bool reunir(const collection& other);
		// Mode d'emploi (constructeur de copie) :
		//
		// Contrat :
		//

		//------------------------------------------------- Surcharge d'opérateurs
		// Avoid default copy assignment implementation
		collection& operator=(const collection&) = delete;

		//-------------------------------------------- Constructeurs - destructeur
		// Avoid default copy constructor implementation
		collection(const collection&) = delete;

		explicit collection(size_t capacity);
		// Mode d'emploi (constructeur de copie) :
		//
		// Contrat :
		//

		collection(dog** dogs, size_t size);
		// Mode d'emploi (constructeur de copie) :
		// NOTE: takes ownership on given dogs and could delete them.
		// NOTE: we assume size is correct
		// Contrat :
		//

		virtual ~collection();
		// Mode d'emploi :
		//
		// Contrat :
		//

		//------------------------------------------------------------------ PRIVE 
	protected:
		//----------------------------------------------------- Méthodes protégées
		size_t find_all_of(const dog *const * dogs_to_find, size_t size, unsigned int& matches_count) const;
		void disposeDogs();

		//----------------------------------------------------- Attributs protégés
		dog** m_dogs = nullptr;
		size_t m_capacity = 0;
		size_t m_size = 0;

		//---------------------------------------------------- Constantes protégés
		static const size_t INITIAL_ALLOCATION_SIZE = 5;
	};
}

#endif // COLLECTION_H
