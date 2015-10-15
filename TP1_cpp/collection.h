/*************************************************************************
collection{file_base}  -  description
-------------------
début                : collection{date}
copyright            : (C) collection{year} par collection{user}
*************************************************************************/

//---------- Interface de la classe <collection{file_base}> (fichier collection{file_name}) ------
#ifndef COLLECTION_H
#define COLLECTION_H

#include "dog.h"

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// collection: 
//------------------------------------------------------------------------ 
class collection
{
	//----------------------------------------------------------------- PUBLIC
public:
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
	//
	// Contrat :
	//

	bool retirer(const dog *const * dogs, size_t size);
	// Mode d'emploi (constructeur de copie) :
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

private:
	//------------------------------------------------------- Méthodes privées

protected:
	//----------------------------------------------------- Attributs protégés
	dog** m_dogs = nullptr;
	size_t m_capacity = 0;
	size_t m_size = 0;

	static const size_t INITIAL_ALLOCATION_SIZE = 5;

private:
	//------------------------------------------------------- Attributs privés

	//---------------------------------------------------------- Classes amies

	//-------------------------------------------------------- Classes privées

	//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <collection{file_base}>

#endif // COLLECTION_H
