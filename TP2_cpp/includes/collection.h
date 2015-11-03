/*********************************************************************************
					collection  -  A dynamic and generic collection
					-----------------------------------------------
date                 : 10/2015
copyright            : (C) 2015 by B3311
*********************************************************************************/

//--------- Interface de la classe <collection.h> (fichier collection.h) ---------
#ifndef COLLECTION_H
#define COLLECTION_H

//----------------------------------------------------------- Interfaces utilisées

namespace TP1
{
	//----------------------------------------------------------------------------
	// collection:
	// classe qui permet de manipuler une collection d'objets de type T
	//----------------------------------------------------------------------------
	template<typename T>
	class collection
	{
		//----------------------------------------------------------------- PUBLIC
	public:
		//----------------------------------------------------- Méthodes publiques

		// Description : affiche la valeur de la collection.
		//	La valeur de la collection est affichée sous la forme : "({ <val1>, <val2>, ... }, <m_capacity>)"
		//	avec <val1>, <val2>, ... les âges des chiens et <m_capacity> la capacité de la collection.
		void afficher() const;

		// Description: ajoute val_to_add dans la collection courante
		//		val_to_add: reférence constante vers une valeur de type T qui sera ajouté dans la collection
		void ajouter(const T& val_to_add);

		// Description: retire old_val de la collection courante
		//		old_val: reference vers un T qui sera retiré de la collection
		//		RETOURNE: Un booléen indiquant si au moins un élément a bien été retiré
		//	NOTE: ajuste la capacité de la collection au minimum même si old_val n'est pas présent dans la collection 
		bool retirer(const T& old_val);

		// Description: retire l'ensemble des valeurs contenues dans le parametre 'vals' de la collection courante
		//		vals: tableau de T qui seront retirés de la collection
		//		size: taille du tableau vals
		//		RETOURNE: Un booléen indiquant si au moins un élément a bien été retiré
		//	NOTE: ajuste la capacité de la collection au minimum même si aucuns éléments de vals n'est pas présent dans la collection 
		bool retirer(const T vals[], size_t size);

		// Description: ajuste, si possible, la capacité de la collection à la taille spécifiée
		//		capacity: nouvelle taille de mémoire allouée pour la structure de donnée interne
		//		RETOURNE: Un booléen indiquant si un ajustement de la capacité a bien été effectué
		bool ajuster(size_t capacity);

		// Description: ajoute le contenu de la collection donnée en paramètre 
		//		other: reference vers la collection à réunir avec la collection courante
		//		RETOURNE: Un booléen indiquant si des éléments de 'other' on bien été ajoutés à la collection
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

		// Description: Constructeur d'une collection à partir d'un ensemble d'éléments donné en paramètre
		//		vals: tableau des éléments qui seront ajoutés à la collection
		//		size: taille du tableau vals
		collection(const T vals[], size_t size);

		// Description: Destructeur de la colection courante
		virtual ~collection();

		//------------------------------------------------------------------ PRIVE 
	protected:
		//----------------------------------------------------- Méthodes protégées

		// Description: Trouve le nombre d'éléments apparetenant à la fois à 'm_vals' 
		//	et au paramètre 'vals_to_find'
		//		vals_to_find: tableau d'éléments de type T qui seront recherchés dans la collection
		//		size: taille du tableau 'vals_to_find'
		//		RETOURNE: le nombre d'éléments apparetenant à la fois à 'm_vals' et à 'vals_to_find'
		unsigned int find_all_of(const T vals_to_find[], size_t size) const;

		// Description: Désalloue la mémoire allouée pour le tableau de pointeur de T 
		//	et pour les objets de type T.
		void disposeValues();

		//----------------------------------------------------- Attributs protégés

		// Tableau de pointeurs de T
		T** m_vals = nullptr;
		// Taille du tableau m_vals
		size_t m_capacity = 0;
		// Taille utilisée du tableau m_vals
		size_t m_size = 0;

		//---------------------------------------------------- Constantes protégés

		static const size_t INITIAL_ALLOCATION_SIZE = 5;
	};
}

#endif // COLLECTION_H
