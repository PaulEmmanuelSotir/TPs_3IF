/*********************************************************************************
						Graph  - A graph with template nodes
						------------------------------------
date                 : 12/2015
copyright            : (C) 2015 by B3311
*********************************************************************************/

//-------------------- Interface de la classe template Graph<T> ------------------
#ifndef GRAPH_H
#define GRAPH_H

//--------------------------------------------------------------- Includes systeme
#include <unordered_map>
#include <initializer_list>

//! \namespace TP3
//! espace de nommage regroupant le code crée pour le TP3 de C++
namespace TP3
{
	//---------------------------------------------------------------------- Types

	//! Classe représentant un graphe fait de noeuds contenant des données de type T
	//! et de liens orientés entre ces noeuds. Un noeud a nescessairement au moins un
	//! lien (noeuds ajoutés automatiquement lors de l'ajout de liens). Si un même lien
	//! est ajouté plusieurs fois, alors son nombre d'occurrences associé est incrémenté.
	//! @remarks
	//!		L'utilisateur doit surcharger la fonction std::hash pour le type T si elle 
	//!		n'existe pas dejà.
	template<typename T, typename Hash = std::hash<T>, typename KeyEqual = std::equal_to<T>, typename Allocator = std::allocator<T>>
	class Graph
	{
		//----------------------------------------------------------------- PUBLIC
	public:
		//----------------------------------------------- Types et alias publiques
		//! Alias pour le type permettant d'identifier un noeud
		using node_id_t = unsigned int;

		//! Structure utilisée pour représenter la destination et le nombre d'occurrences d'un lien
		struct Link_to
		{
			Link_to() = default;
			Link_to(const Link_to&) = default;
			Link_to& operator=(const Link_to&) = default;
			Link_to(Link_to&&) = default;
			Link_to& operator=(Link_to&&) = default;

			explicit Link_to(node_id_t dest) : occurrence(1), destination(dest) { };

			unsigned int occurrence = 0;
			node_id_t destination;
		};

		//----------------------------------------------------- Méthodes publiques

		//! Ajoute un lien au graph
		//! @params source référence universelle vers la valeur du noeud source du lien
		//! @params destination référence universelle vers la valeur de la destination du lien
		void add_link(T&& source, T&& destination);

		//! Retourne une multimap non ordonée représentant les liens du graph et associant à l'identifiant
		//! d'un noeud source, une structure contenant l'id du noeud de destination et le nombre d'occurrences du lien.
		std::unordered_multimap<node_id_t, Link_to>& get_links();

		//! Retourne une map non ordonée associant la valeur de chaque noeud à leur identifiant
		std::unordered_map<T, node_id_t>& get_nodes();

		//! Vide le graphe de ses noeuds et liens
		void clear();

		//----------------------------------------------------- Méthodes spéciales

		//! Constructeur par défaut ou permettant de spécifier la fonction de hashage, l'opérateur
		//! d'égalité et l'allocateur pour le type T.
		//! Par defaut, std::Hash<T>(), std::equal_to<T>() et std::allocator<T>() sont utilisés.
		explicit Graph(const Hash& hash = Hash(),
					   const KeyEqual& equal = KeyEqual(),
					   const Allocator& alloc = Allocator());

		//! Constructeur permettant de spécifier une liste d'initialisation, la fonction de hashage,
		//! l'opérateur d'égalité et l'allocateur pour le type T.
		//! Par defaut, std::Hash<T>(), std::equal_to<T>() et std::allocator<T>() sont utilisés.
		//! @params init_list list d'initialisation contenant des paires représentant des liens 
		//!		(pair.fisrt est le noeud source et pair.second est la destination).
		Graph(std::initializer_list<std::pair<T, T>> init_list,
			  const Hash& hash = Hash(),
			  const KeyEqual& equal = KeyEqual(),
			  const Allocator& alloc = Allocator());

		// On utilise l'implémentation par défaut du copy/move constructor et copy/move assignment operator
		Graph(const Graph&) = default;
		Graph& operator=(const Graph&) = default;
		Graph(Graph&&) = default;
		Graph& operator=(Graph&&) = default;

		//------------------------------------------------------------------ PRIVE
	private:
		//------------------------------------------------------- Attributs privés

		//! attribut contenant le prochain id attribué à un nouveau noeud (pas indispensable ici, mais est 
		//! utile pour une implémenation future de méthodes de supression d'éléments)
		node_id_t m_new_id = 0;

		//! multimap non ordonnée stockant tout les liens entre les nœuds du graphe (les clés sont les
		//! identifiants des nœuds source, les valeurs sont les destinations et leur nombre d'occurrences)
		std::unordered_multimap<node_id_t, Link_to> m_links;
		
		//! map non ordonée contenant les noeuds (valeur et identifiant)
		std::unordered_map<T, node_id_t> m_nodes;
	};

	//--------------- Implémentation de la classe template Graph<T> --------------

	template<typename T, typename Hash, typename KeyEqual, typename Allocator>
	Graph<T, Hash, KeyEqual, Allocator>::Graph(const Hash& hash, const KeyEqual& equal, const Allocator& alloc)
		: m_links(), m_nodes(10, hash, equal, alloc) { }

	template<typename T, typename Hash, typename KeyEqual, typename Allocator>
	Graph<T, Hash, KeyEqual, Allocator>::Graph(std::initializer_list<std::pair<T, T>> init_list, const Hash& hash, const KeyEqual& equal,  const Allocator& alloc)
		: m_links(), m_nodes(10, hash, equal, alloc)
	{
		for (const auto& link : init_list)
			add_link(link.first, link.second);
	}

	template<typename T, typename Hash, typename KeyEqual, typename Allocator>
	void Graph<T, Hash, KeyEqual, Allocator>::add_link(T&& source, T&& destination)
	{
		node_id_t source_id, destination_id;

		// Add source node to m_nodes if not stored yet and get source id
		auto p = m_nodes.emplace(std::make_pair(std::forward<T>(source), m_new_id));
		source_id = p.second ? m_new_id++ : p.first->second; // TODO: verifier les incrémentations

		// Add destination node to m_nodes if not stored yet and get destination id
		p = m_nodes.emplace(std::make_pair(std::forward<T>(destination), m_new_id));
		destination_id = p.second ? m_new_id++ : p.first->second;

		// Find every links which have the same source
		auto range = m_links.equal_range(source_id);

		// Linear lookup on resulting range to find if we have already added a link with the same destination and source 
		for (auto it = range.first; it != range.second; ++it)
		{
			if (it->second.destination == destination_id)
			{
				++(it->second.occurrence); // increment link occurrence number
				return;
			}
		}

		// Store new link otherwise
		m_links.emplace(source_id, Link_to(destination_id));
	}

	template<typename T, typename Hash, typename KeyEqual, typename Allocator>
	inline std::unordered_multimap<typename Graph<T, Hash, KeyEqual, Allocator>::node_id_t, typename Graph<T, Hash, KeyEqual, Allocator>::Link_to>& Graph<T, Hash, KeyEqual, Allocator>::get_links()
	{ return m_links; }

	template<typename T, typename Hash, typename KeyEqual, typename Allocator>
	inline std::unordered_map<T, typename Graph<T, Hash, KeyEqual, Allocator>::node_id_t>& Graph<T, Hash, KeyEqual, Allocator>::get_nodes()
	{ return m_nodes; }

	template<typename T, typename Hash, typename KeyEqual, typename Allocator>
	inline void Graph<T, Hash, KeyEqual, Allocator>::clear()
	{
		m_links.clear();
		m_nodes.clear();
		m_new_id = 0;
	}
}

#endif // GRAPH_H


