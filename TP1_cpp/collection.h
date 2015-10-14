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

	bool ajouter(dog* dog);
	// Mode d'emploi (constructeur de copie) :
	//
	// Contrat :
	//

	bool retirer(const dog& dog1);
	// Mode d'emploi (constructeur de copie) :
	//
	// Contrat :
	//

	bool retirer(const dog *const * dogs, size_t size);
	// Mode d'emploi (constructeur de copie) :
	//
	// Contrat :
	//

	bool ajuster(size_t new_size);
	// Mode d'emploi (constructeur de copie) :
	//
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

	explicit collection(size_t max_size);
	// Mode d'emploi (constructeur de copie) :
	//
	// Contrat :
	//

	collection(dog** dogs, size_t max_size);
	// Mode d'emploi (constructeur de copie) :
	//
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
	dog** dogs = nullptr;
	size_t max_size = 0;
	size_t used_size = 0;

	static const size_t HIGH_ALLOCATION_STEP = 8;
	static const size_t LOW_ALLOCATION_STEP = 4;
	static const size_t ALLOCATION_STEP = (HIGH_ALLOCATION_STEP + LOW_ALLOCATION_STEP) / 2;

private:
	//------------------------------------------------------- Attributs privés

	//---------------------------------------------------------- Classes amies

	//-------------------------------------------------------- Classes privées

	//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <collection{file_base}>

#endif // COLLECTION_H
