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
	// classe qui permet de manipuler une collection d'objets de type dog
	//----------------------------------------------------------------------------
	class collection
	{
		//----------------------------------------------------------------- PUBLIC
	public:
		//----------------------------------------------------- Méthodes publiques
		void afficher() const;
		// Mode d'emploi : affiche le contenu de la collection

		bool ajouter(const dog& dog_to_add);
		// Mode d'emploi: ajoute dog_to_add dans la collection courante
		//		new_dog: reférence constante vers un dog qui sera ajouté dans la collection

		bool retirer(const dog& old_dog);
		// Mode d'emploi: retire old_dog de la collection courante
		//		old_dog: reference vers un dog qui sera retiré de la collection puis deleté
		// NOTE: ajuste la capacité de la collection au minimum même si old_dog n'est pas présent dans la collection 

		bool retirer(const dog dogs[], size_t size);
		// Mode d'emploi: retire l'ensemble des dogs du parametre 'dogs' de la collection courante
		//		dogs: tableau de dogs qui seront retirés de la collection puis deletés
		//		size: taille du tableau dogs
		// NOTE: ajuste la capacité de la collection au minimum même si aucun dog de dogs n'est pas présent dans la collection 

		bool ajuster(size_t capacity);
		// Mode d'emploi: ajuste, si possible, la capacité de la collection à la taille spécifiée
		// 	capacity: nouvelle taille de mémoire allouée pour la structure de donnée interne

		bool reunir(const collection& other);
		// Mode d'emploi: ajoute le contenu de la collection donnée en paramétre
		//	other: reference vers la collection à réunir avec la collection courante

		//------------------------------------------------- Surcharge d'opérateurs
		// Empêche l'implémentation par défaut du 'copy assignement operator'
		collection& operator=(const collection&) = delete;

		//-------------------------------------------- Constructeurs - destructeur
		// Empêche l'implémentation par défaut du constructeur de copie
		collection(const collection&) = delete;

		explicit collection(size_t capacity);
		// Mode d'emploi: Constructeur d'une collection de taille pré-allouée donnée
		//	capacity: Taille de la nouvelle collection

		collection(const dog dogs[], size_t size);
		// Mode d'emploi: Constructeur d'une collection à partir d'un ensemble de dog donnée en paramètre
		// NOTE: la classe collection prend l'ownership sur les dogs donnés en paramètre et pourrais donc les deleter

		virtual ~collection();
		// Mode d'emloi: Destructeur de la colection courante

		//------------------------------------------------------------------ PRIVE 
	protected:
		//----------------------------------------------------- Méthodes protégées
		unsigned int find_all_of(const dog dogs_to_find[], size_t size) const;
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
