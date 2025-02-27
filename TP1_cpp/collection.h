/*********************************************************************************
						collection  -  A collection of dogs
						-----------------------------------
date                 : 10/2015
copyright            : (C) 2015 by B3311
*********************************************************************************/

//--------- Interface de la classe <collection.h> (fichier collection.h) ---------
#ifndef COLLECTION_H
#define COLLECTION_H

//----------------------------------------------------------- Interfaces utilis�es
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
		//----------------------------------------------------- M�thodes publiques

		// Description : affiche la valeur de la collection.
		//	La valeur de la collection est affich�e sous la forme : "({ <val1>, <val2>, ... }, <m_capacity>)"
		//	avec <val1>, <val2>, ... les �ges des chiens et <m_capacity> la capacit� de la collection.
		void afficher() const;

		// Description: ajoute dog_to_add dans la collection courante
		//		new_dog: ref�rence constante vers un dog qui sera ajout� dans la collection
		void ajouter(const dog& dog_to_add);

		// Description: retire old_dog de la collection courante
		//		old_dog: reference vers un dog qui sera retir� de la collection
		//		RETOURNE: Un bool�en indiquant si au moins un dog a bien �t� retir�
		//	NOTE: ajuste la capacit� de la collection au minimum m�me si old_dog n'est pas pr�sent dans la collection 
		bool retirer(const dog& old_dog);

		// Description: retire l'ensemble des dogs du parametre 'dogs' de la collection courante
		//		dogs: tableau de dogs qui seront retir�s de la collection
		//		size: taille du tableau dogs
		//		RETOURNE: Un bool�en indiquant si au moins un dog a bien �t� retir�
		//	NOTE: ajuste la capacit� de la collection au minimum m�me si aucun dog de dogs n'est pas pr�sent dans la collection 
		bool retirer(const dog dogs[], size_t size);

		// Description: ajuste, si possible, la capacit� de la collection � la taille sp�cifi�e
		//		capacity: nouvelle taille de m�moire allou�e pour la structure de donn�e interne
		//		RETOURNE: Un bool�en indiquant si un ajustement de la capacit� a bien �t� effectu�
		bool ajuster(size_t capacity);

		// Description: ajoute le contenu de la collection donn�e en param�tre 
		//		other: reference vers la collection � r�unir avec la collection courante
		//		RETOURNE: Un bool�en indiquant si des dogs de 'other' on bien �t� ajout�s � la collection
		bool reunir(const collection& other);

		//------------------------------------------------- Surcharge d'op�rateurs

		// Emp�che l'impl�mentation par d�faut du 'copy assignement operator'
		collection& operator=(const collection&) = delete;

		//-------------------------------------------- Constructeurs - destructeur

		// Emp�che l'impl�mentation par d�faut du constructeur de copie
		collection(const collection&) = delete;

		// Description: Constructeur d'une collection de taille pr�-allou�e donn�e
		//		capacity: Taille de la nouvelle collection
		explicit collection(size_t capacity);

		// Description: Constructeur d'une collection � partir d'un ensemble de dog donn� en param�tre
		//		dogs: tableau des dogs qui seront ajout�s � la collection
		//		size: taille du tableau dogs
		collection(const dog dogs[], size_t size);

		// Description: Destructeur de la colection courante
		virtual ~collection();

		//------------------------------------------------------------------ PRIVE 
	protected:
		//----------------------------------------------------- M�thodes prot�g�es

		// Description: Trouve le nombre de dog apparetenant � la fois � 'm_dogs' 
		//	et au param�tre 'dogs_to_find'
		//		dogs_to_find: tableau de dogs qui seront recherch�s dans la collection
		//		size: taille du tableau 'dogs_to_find'
		//		RETOURNE: le nombre de dog apparetenant � la fois � 'm_dogs' et � 'dogs_to_find'
		unsigned int find_all_of(const dog dogs_to_find[], size_t size) const;

		// Description: D�salloue la m�moire allou�e pour le tableau de pointeur de dog 
		//	et pour les objets de type dog.
		void disposeDogs();

		//----------------------------------------------------- Attributs prot�g�s

		// Tableau de pointeurs de dog
		dog** m_dogs = nullptr;
		// Taille du tableau m_dogs
		size_t m_capacity = 0;
		// Taille utilis�e du tableau m_dogs
		size_t m_size = 0;

		//---------------------------------------------------- Constantes prot�g�s

		static const size_t INITIAL_ALLOCATION_SIZE = 5;
	};
}

#endif // COLLECTION_H
