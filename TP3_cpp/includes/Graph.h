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
	//!		gérer de façon couteuse les invalidations de ces pointeurs lors d'insertion dans le conteneur contenant les 
	//!		objets de type T)
	template<typename T, typename Hash = std::hash<T>, typename KeyEqual = std::equal_to<T>, typename Allocator = std::allocator<T>>
	class Graph
	{
	public:
		using node_id_t = unsigned int;
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
		std::unordered_multimap<node_id_t, Link_to>& get_links();
		std::unordered_map<T, node_id_t>& get_nodes();
		void clear();

	private:
		unsigned int m_new_id = 0;

		//! multimap non ordonnée stockant tout les liens entre les nœuds du graphe (les clés sont les nœuds source des liens,
		//! les valeurs sont les destinations et leur nombre d'occurrences)
		std::unordered_multimap<node_id_t, Link_to> m_links;

		std::unordered_map<T, node_id_t> m_nodes;
	};
	/*
	
		using node_id_t = unsigned int;
		std::unordered_map<std::string, node_id_t> nodes;
		nodes.emplace(std::make_pair(link.first, id));
		nodes.emplace(std::make_pair(link.second.destination, id));
	*/

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

		auto p = m_nodes.emplace(std::make_pair(std::forward<T>(source), m_new_id));
		source_id = p.second ? m_new_id++ : p.first->second; // TODO: verifier les incrémentations

		p = m_nodes.emplace(std::make_pair(std::forward<T>(destination), m_new_id));
		destination_id = p.second ? m_new_id++ : p.first->second;

		auto range = m_links.equal_range(source_id);

		// Linear lookup on links having the same source node
		for (auto it = range.first; it != range.second; ++it)
		{
			if (it->second.destination == destination_id)
			{
				++(it->second.occurrence);
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
	{ m_links.clear(); }
}

#endif // GRAPH_H


