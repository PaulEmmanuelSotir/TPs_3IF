/*********************************************************************************
					collection  -  A dynamic and generic collection
					-----------------------------------------------
date                 : 10/2015
copyright            : (C) 2015 by B3311
*********************************************************************************/

//--------- Interface de la classe <collection.h> (fichier collection.h) ---------
#ifndef COLLECTION_H
#define COLLECTION_H

//----------------------------------------------------------- Interfaces utilis�es

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
		//----------------------------------------------------- M�thodes publiques

		// Description : affiche la valeur de la collection.
		//	La valeur de la collection est affich�e sous la forme : "({ <val1>, <val2>, ... }, <m_capacity>)"
		//	avec <val1>, <val2>, ... les �ges des chiens et <m_capacity> la capacit� de la collection.
		void afficher() const;

		// Description: ajoute val_to_add dans la collection courante
		//		val_to_add: ref�rence constante vers une valeur de type T qui sera ajout� dans la collection
		void ajouter(const T& val_to_add);

		// Description: retire old_val de la collection courante
		//		old_val: reference vers un T qui sera retir� de la collection
		//		RETOURNE: Un bool�en indiquant si au moins un �l�ment a bien �t� retir�
		//	NOTE: ajuste la capacit� de la collection au minimum m�me si old_val n'est pas pr�sent dans la collection 
		bool retirer(const T& old_val);

		// Description: retire l'ensemble des valeurs contenues dans le parametre 'vals' de la collection courante
		//		vals: tableau de T qui seront retir�s de la collection
		//		size: taille du tableau vals
		//		RETOURNE: Un bool�en indiquant si au moins un �l�ment a bien �t� retir�
		//	NOTE: ajuste la capacit� de la collection au minimum m�me si aucuns �l�ments de vals n'est pas pr�sent dans la collection 
		bool retirer(const T vals[], size_t size);

		// Description: ajuste, si possible, la capacit� de la collection � la taille sp�cifi�e
		//		capacity: nouvelle taille de m�moire allou�e pour la structure de donn�e interne
		//		RETOURNE: Un bool�en indiquant si un ajustement de la capacit� a bien �t� effectu�
		bool ajuster(size_t capacity);

		// Description: ajoute le contenu de la collection donn�e en param�tre 
		//		other: reference vers la collection � r�unir avec la collection courante
		//		RETOURNE: Un bool�en indiquant si des �l�ments de 'other' on bien �t� ajout�s � la collection
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

		// Description: Constructeur d'une collection � partir d'un ensemble d'�l�ments donn� en param�tre
		//		vals: tableau des �l�ments qui seront ajout�s � la collection
		//		size: taille du tableau vals
		collection(const T vals[], size_t size);

		// Description: Destructeur de la colection courante
		virtual ~collection();

		//------------------------------------------------------------------ PRIVE 
	protected:
		//----------------------------------------------------- M�thodes prot�g�es

		// Description: Trouve le nombre d'�l�ments apparetenant � la fois � 'm_vals' 
		//	et au param�tre 'vals_to_find'
		//		vals_to_find: tableau d'�l�ments de type T qui seront recherch�s dans la collection
		//		size: taille du tableau 'vals_to_find'
		//		RETOURNE: le nombre d'�l�ments apparetenant � la fois � 'm_vals' et � 'vals_to_find'
		unsigned int find_all_of(const T vals_to_find[], size_t size) const;

		// Description: D�salloue la m�moire allou�e pour le tableau de pointeur de T 
		//	et pour les objets de type T.
		void disposeValues();

		//----------------------------------------------------- Attributs prot�g�s

		// Tableau de pointeurs de T
		T** m_vals = nullptr;
		// Taille du tableau m_vals
		size_t m_capacity = 0;
		// Taille utilis�e du tableau m_vals
		size_t m_size = 0;

		//---------------------------------------------------- Constantes prot�g�s

		static const size_t INITIAL_ALLOCATION_SIZE = 5;
	};
}

#endif // COLLECTION_H
