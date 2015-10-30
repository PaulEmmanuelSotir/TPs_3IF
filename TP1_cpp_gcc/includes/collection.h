/*********************************************************************************
						collection  -  A collection of dogs
						-----------------------------------
date                 : 10/2015
copyright            : (C) 2015 by B3311
*********************************************************************************/

//--------- Interface de la classe <collection.h> (fichier collection.h) ---------
#ifndef COLLECTION_H
#define COLLECTION_H

//----------------------------------------------------------- Interfaces utilisées
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

		// Description : affiche la valeur de la collection.
		//	La valeur de la collection est affichée sous la forme : "({ <val1>, <val2>, ... }, <m_capacity>)"
		//	avec <val1>, <val2>, ... les âges des chiens et <m_capacity> la capacité de la collection.
		void afficher() const;

		// Description: ajoute dog_to_add dans la collection courante
		//		new_dog: reférence constante vers un dog qui sera ajouté dans la collection
		void ajouter(const dog& dog_to_add);

		// Description: retire old_dog de la collection courante
		//		old_dog: reference vers un dog qui sera retiré de la collection
		//		RETOURNE: Un booléen indiquant si au moins un dog a bien été retiré
		//	NOTE: ajuste la capacité de la collection au minimum même si old_dog n'est pas présent dans la collection 
		bool retirer(const dog& old_dog);

		// Description: retire l'ensemble des dogs du parametre 'dogs' de la collection courante
		//		dogs: tableau de dogs qui seront retirés de la collection
		//		size: taille du tableau dogs
		//		RETOURNE: Un booléen indiquant si au moins un dog a bien été retiré
		//	NOTE: ajuste la capacité de la collection au minimum même si aucun dog de dogs n'est pas présent dans la collection 
		bool retirer(const dog dogs[], size_t size);

		// Description: ajuste, si possible, la capacité de la collection à la taille spécifiée
		//		capacity: nouvelle taille de mémoire allouée pour la structure de donnée interne
		//		RETOURNE: Un booléen indiquant si un ajustement de la capacité a bien été effectué
		bool ajuster(size_t capacity);

		// Description: ajoute le contenu de la collection donnée en paramètre 
		//		other: reference vers la collection à réunir avec la collection courante
		//		RETOURNE: Un booléen indiquant si des dogs de 'other' on bien été ajoutés à la collection
		bool reunir(const collection& other);

		//------------------------------------------------- Surcharge d'opérateurs

		// Empêche l'implémentation par défaut du 'copy assignement operator'
		collection& operator=(const collection&) = delete;

		//-------------------------------------------- Constructeurs - destructeur

		// Empêche l'implémentation par défaut du constructeur de copie
		collection(const collection&) = delete;

		// Description: Constructeur d'une collection de taille pré-allouée donnée
		//		capacity: Taille de la nouvelle collection
		explicit collection(size_t capacity);

		// Description: Constructeur d'une collection à partir d'un ensemble de dog donné en paramètre
		//		dogs: tableau des dogs qui seront ajoutés à la collection
		//		size: taille du tableau dogs
		collection(const dog dogs[], size_t size);

		// Description: Destructeur de la colection courante
		virtual ~collection();

		//------------------------------------------------------------------ PRIVE 
	protected:
		//----------------------------------------------------- Méthodes protégées

		// Description: Trouve le nombre de dog apparetenant à la fois à 'm_dogs' 
		//	et au paramètre 'dogs_to_find'
		//		dogs_to_find: tableau de dogs qui seront recherchés dans la collection
		//		size: taille du tableau 'dogs_to_find'
		//		RETOURNE: le nombre de dog apparetenant à la fois à 'm_dogs' et à 'dogs_to_find'
		unsigned int find_all_of(const dog dogs_to_find[], size_t size) const;

		// Description: Désalloue la mémoire allouée pour le tableau de pointeur de dog 
		//	et pour les objets de type dog.
		void disposeDogs();

		//----------------------------------------------------- Attributs protégés

		// Tableau de pointeurs de dog
		dog** m_dogs = nullptr;
		// Taille du tableau m_dogs
		size_t m_capacity = 0;
		// Taille utilisée du tableau m_dogs
		size_t m_size = 0;

		//---------------------------------------------------- Constantes protégés

		static const size_t INITIAL_ALLOCATION_SIZE = 5;
	};
}

#endif // COLLECTION_H
