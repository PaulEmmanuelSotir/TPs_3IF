/*************************************************************************
collection{file_base}  -  description
-------------------
d�but                : collection{date}
copyright            : (C) collection{year} par collection{user}
*************************************************************************/

//---------- Interface de la classe <collection{file_base}> (fichier collection{file_name}) ------
#ifndef COLLECTION_H
#define COLLECTION_H

#include "dog.h"

//--------------------------------------------------- Interfaces utilis�es

//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// collection: 
//------------------------------------------------------------------------ 
class collection
{
	//----------------------------------------------------------------- PUBLIC
public:
	//----------------------------------------------------- M�thodes publiques
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

	//------------------------------------------------- Surcharge d'op�rateurs
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


	virtual ~collection ();
	// Mode d'emploi :
	//
	// Contrat :
	//

	//------------------------------------------------------------------ PRIVE 

protected:
	//----------------------------------------------------- M�thodes prot�g�es

private:
	//------------------------------------------------------- M�thodes priv�es

protected:
	//----------------------------------------------------- Attributs prot�g�s
	dog** dogs = nullptr;
	size_t max_size = 0;
	size_t used_size = 0;

	static const size_t HIGH_ALLOCATION_STEP = 8;
	static const size_t LOW_ALLOCATION_STEP = 4;
	static const size_t ALLOCATION_STEP = (HIGH_ALLOCATION_STEP + LOW_ALLOCATION_STEP) / 2;

private:
	//------------------------------------------------------- Attributs priv�s

	//---------------------------------------------------------- Classes amies

	//-------------------------------------------------------- Classes priv�es

	//----------------------------------------------------------- Types priv�s

};

//----------------------------------------- Types d�pendants de <collection{file_base}>

#endif // COLLECTION_H
