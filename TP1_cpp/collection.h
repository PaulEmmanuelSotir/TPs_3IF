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

//------------------------------------------------------- Interfaces utilis�es
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
		void afficher() const;
		// Mode d'emploi : affiche le contenu de la collection

		bool ajouter(const dog& dog_to_add);
		// Mode d'emploi: ajoute dog_to_add dans la collection courante
		//		new_dog: ref�rence constante vers un dog qui sera ajout� dans la collection

		bool retirer(const dog& old_dog);
		// Mode d'emploi: retire old_dog de la collection courante
		//		old_dog: reference vers un dog qui sera retir� de la collection puis delet�
		// NOTE: ajuste la capacit� de la collection au minimum m�me si old_dog n'est pas pr�sent dans la collection 

		bool retirer(const dog dogs[], size_t size);
		// Mode d'emploi: retire l'ensemble des dogs du parametre 'dogs' de la collection courante
		//		dogs: tableau de dogs qui seront retir�s de la collection puis delet�s
		//		size: taille du tableau dogs
		// NOTE: ajuste la capacit� de la collection au minimum m�me si aucun dog de dogs n'est pas pr�sent dans la collection 

		bool ajuster(size_t capacity);
		// Mode d'emploi: ajuste, si possible, la capacit� de la collection � la taille sp�cifi�e
		// 	capacity: nouvelle taille de m�moire allou�e pour la structure de donn�e interne

		bool reunir(const collection& other);
		// Mode d'emploi: ajoute le contenu de la collection donn�e en param�tre
		//	other: reference vers la collection � r�unir avec la collection courante

		//------------------------------------------------- Surcharge d'op�rateurs
		// Emp�che l'impl�mentation par d�faut du 'copy assignement operator'
		collection& operator=(const collection&) = delete;

		//-------------------------------------------- Constructeurs - destructeur
		// Emp�che l'impl�mentation par d�faut du constructeur de copie
		collection(const collection&) = delete;

		explicit collection(size_t capacity);
		// Mode d'emploi: Constructeur d'une collection de taille pr�-allou�e donn�e
		//	capacity: Taille de la nouvelle collection

		collection(const dog dogs[], size_t size);
		// Mode d'emploi: Constructeur d'une collection � partir d'un ensemble de dog donn�e en param�tre
		// NOTE: la classe collection prend l'ownership sur les dogs donn�s en param�tre et pourrais donc les deleter

		virtual ~collection();
		// Mode d'emloi: Destructeur de la colection courante

		//------------------------------------------------------------------ PRIVE 
	protected:
		//----------------------------------------------------- M�thodes prot�g�es
		unsigned int find_all_of(const dog dogs_to_find[], size_t size) const;
		void disposeDogs();

		//----------------------------------------------------- Attributs prot�g�s
		dog** m_dogs = nullptr;
		size_t m_capacity = 0;
		size_t m_size = 0;

		//---------------------------------------------------- Constantes prot�g�s
		static const size_t INITIAL_ALLOCATION_SIZE = 5;
	};
}

#endif // COLLECTION_H
