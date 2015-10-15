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

	//------------------------------------------------- Surcharge d'op�rateurs
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
	//----------------------------------------------------- M�thodes prot�g�es

private:
	//------------------------------------------------------- M�thodes priv�es

protected:
	//----------------------------------------------------- Attributs prot�g�s
	dog** m_dogs = nullptr;
	size_t m_capacity = 0;
	size_t m_size = 0;

	static const size_t INITIAL_ALLOCATION_SIZE = 5;

private:
	//------------------------------------------------------- Attributs priv�s

	//---------------------------------------------------------- Classes amies

	//-------------------------------------------------------- Classes priv�es

	//----------------------------------------------------------- Types priv�s

};

//----------------------------------------- Types d�pendants de <collection{file_base}>

#endif // COLLECTION_H
