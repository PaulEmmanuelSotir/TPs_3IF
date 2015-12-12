#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <initializer_list>

//! \namespace TP3
//! espace de nommage regroupant le code crée pour le TP3 de C++
namespace TP3
{
	//! ...
	//! @remarks
	//!		L'utilisateur doit surcharger la fonction std::hash pour le type T si elle n'existe pas dejà
	//! @remarks
	//!		Des copies d'un même objets/nœuds de type T seront stockées dans le graph, il est donc de la responsabilité
	//!		de l'utilisateur que ces objets soient lègers (c'est une solution plus flexible que d'essayer de stocker les
	//!		objets de type T dans un autre conteneur (comme un std::unordered_set) dans le graph pour éviter la copie des 
	//!		objets de type T car, si on stock des pointeurs/smart ptr/iterateur dans m_links au lieu de copies, il faudrait
	//!		gérer de façon couteuse les invalidations de ces pointeur lors d'insertion dans le conteneur contenant les 
	//!		objets de type T)
	template<typename T, typename Hash = std::hash<T>, typename KeyEqual = std::equal_to<T>, typename Allocator = std::allocator<T>>
	class Graph
	{
	public:
		Graph(const Hash& hash = Hash(),
		      const KeyEqual& equal = KeyEqual(),
		      const Allocator& alloc = Allocator());

		Graph(std::initializer_list<std::pair<T, T>> init_list,
			const Hash& hash = Hash(),
			const KeyEqual& equal = KeyEqual(),
			const Allocator& alloc = Allocator());

		Graph(const Graph&) = default;
		Graph& operator=(const Graph&) = default;
		Graph(Graph&&) = default;
		Graph& operator=(Graph&&) = default;

		void add_link(T&& source, T&& destination);
		void clear();

	private:
		struct Link_to
		{
			Link_to() = default;
			Link_to(const Link_to&) = default;
			Link_to& operator=(const Link_to&) = default;
			Link_to(Link_to&&) = default;
			Link_to& operator=(Link_to&&) = default;

			explicit Link_to(T dest) : occurrence(1), destination(dest) { };

			unsigned int occurrence = 0;
			T destination;
		};

		//! multimap non ordonnée stockant tout les liens entre les nœuds du graphe (les clés sont les nœuds source des liens,
		//! les valeurs sont les destinations et leur nombre d'occurrences)
		std::unordered_multimap<T, Link_to> m_links;
	};

	template<typename T, typename Hash, typename KeyEqual, typename Allocator>
	Graph<T, Hash, KeyEqual, Allocator>::Graph(const Hash& hash,
	                                           const KeyEqual& equal,
	                                           const Allocator& alloc)
		: m_links(10, hash, equal, alloc) { }

	template<typename T, typename Hash, typename KeyEqual, typename Allocator>
	Graph<T, Hash, KeyEqual, Allocator>::Graph(std::initializer_list<std::pair<T, T>> init_list,
	                                           const Hash& hash = Hash(),
	                                           const KeyEqual& equal = KeyEqual(),
	                                           const Allocator& alloc = Allocator())
		: m_links(10, hash, equal, alloc)
	{
		for (const auto& link : init_list)
			add_link(link.first, link.second);
	}

	template<typename T, typename Hash, typename KeyEqual, typename Allocator>
	void Graph<T, Hash, KeyEqual, Allocator>::add_link(T&& source, T&& destination)
	{
		auto range = m_links.equal_range(std::forward<T>(source));

		// Linear lookup on links having the same source node
		for (auto it = range.first; it != range.second; ++it)
		{
			if (it->second.destination == std::forward<T>(destination))
			{
				++(it->second.occurrence);
				return;
			}
		}

		// Store new link otherwise
		m_links.emplace(std::forward<T>(source), Link_to(std::forward<T>(destination)));
	}

	template<typename T, typename Hash, typename KeyEqual, typename Allocator>
	void Graph<T, Hash, KeyEqual, Allocator>::clear()
	{
		m_links.clear();
	}
}

#endif // GRAPH_H


