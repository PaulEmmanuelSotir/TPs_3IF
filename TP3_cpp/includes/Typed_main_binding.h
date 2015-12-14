/*********************************************************************************
					Typed_main_binding  - An helper class for main args
					---------------------------------------------------
date                 : 12/2015
copyright            : (C) 2015 by B3311
*********************************************************************************/

//---------- Interface de la classe template Typed_main_binding<Args...> ---------
#ifndef TYPED_MAIN_BINDING_H
#define TYPED_MAIN_BINDING_H

//-------------------------------------------------------------- Includes systèmes
#include <vector>
#include <utility>
#include "optional.h"
#include <type_traits>

//------------------------------------------------------------ Includes personnels
#include "Utils.h"

//! \namespace TP3
//! espace de nommage regroupant le code crée pour le TP3 de C++
namespace TP3
{
	//-------------------------------------------------------------- Metafonctions

	//! Alias simplifiant la spécification du type de retour des méthodes 'get_option_tags()'
	//! @remarks
	//!		Les seules contraintes concernant le concept de 'option_with_tags' est que le type
	//!		de retour de 'get_option_tags()' soit itérable et contienne des valeurs implicitement 
	//!		convertibles en 'std::string' (pas nescessairement statique ou de type tags_t<N>)
	template<size_t N>
	using tags_t = std::array<std::string, N>;

	//! Spécialisation d'une metafonction aidant à verifier si un type T n'est pas conforme
	//! au concept de 'option_with_tags'
	template<typename T, typename = void>
	struct has_option_tag_getter : std::false_type { };

	//! Spécialisation d'une metafonction aidant à verifier si un type T est conforme au
	//! concept de 'option_with_tags' (verifie seulement la présence de la méthode statique)
	template<typename T>
	struct has_option_tag_getter<T, decltype(std::declval<T>().get_option_tags(), void())> : std::true_type { };

	//! Spécialisation d'une metafonction aidant à verifier si un type T n'est pas conforme
	//! au concept de 'option_with_value'
	template<typename T, typename = void>
	struct option_has_value : std::false_type { };

	//! Spécialisation d'une metafonction aidant à verifier si un type T est conforme au
	//! concept de 'option_with_value'
	template<typename T>
	struct option_has_value<T, decltype(std::declval<T>().value, void())> : std::true_type { };

	// TODO: verifier que T n'est pas tags_t<0> :
/*	template<typename T>
	constexpr bool has_option_tag()
	{ return has_option_tag_getter<T>::value && std::is_same<decltype(std::declval<T>().get_option_tags()), tags_t<0>>::value; }*/

	//---------------------------------------------------------------------- Types

	//! Classe template permettant de simplifier l'interprétation de argv et argc.
	//! A partir d'une fonction dont la signature est du type 'typed_main_t<Args...>'
	//! (avec les types Args validants les concepts décrits ci dessous), la classe
	//! template en déduit statiquement la forme des commandes acceptables et gère
	//! automatiquement toutes les vérifications et conversions nécessaires au runtime
	//! pour pouvoir appeler, si possible, le main typé spécifié (avec les paramètres
	//! optionnels correspondants à la commande).
	//! @remarks
	//!		Les arguments templates 'Args' doivent être conformes aux concepts de :
	//!		- 'option_with_tags' et 'option_with_value' : option ayant un ou des tags
	//!			et un paramètre (e.g. "-t 21")
	//!		- ou 'option_with_tags' : option sans paramètre avec un tag (e.g. "-e")
	//!		- ou 'option_with_value' : option sans tags et ayant un paramètre.
	//!			Ce type d'option est en fait obligatoire : il determine la forme de la
	//!			commande car toute les options de (Args...) avant celle-ci doivent être
	//!			également avant dans argv (de même pour les options après une option sans tag)
	//! @remarks
	//!		- Description du concept 'option_with_value' : Le type T doit contenir un attribut
	//!			publique 'value' tel que son type soit pourvus d'une surcharge de 'T TP3::parse<T>(std::string)'
	//!		- Description du concept 'option_with_tags' : Le type T doit contenir une méthode
	//!			publique et statique 'get_option_tags()' retournant un objet itérable contenant
	//!			des valeurs implicitment convertibles en 'std::string'.
	// TODO: support default values
	// TODO: allow multiple typed_main implementation for alternative command usages
	template<typename... Args>
	class Typed_main_binding
	{
		//----------------------------------------------------------------- PUBLIC
	public:
		//----------------------------------------------- Types et alias publiques
		using typed_main_t = std::function<void(std::experimental::optional<Args>...)>;

		//----------------------------------------------------- Méthodes publiques

		//! Execute, si possible, le main typé en construisant les paramètres optionels 
		//! du main typé à partir de argv et argc.
		//! @throw std::invalid_argument
		//! @throw std::out_of_range
		void exec(int argc, char* argv[]);

		//----------------------------------------------------- Méthodes spéciales

		//! Constructeur prenant en paramètre le main typé qui sera executé
		explicit Typed_main_binding(const typed_main_t& typed_main);

		//------------------------------------------------------------------ PRIVE
	private:
		//------------------------------------------------------- Méthodes privées

		//! spécialisation template utilisant SFINAE pour cibler les options ayant
		//! seulement un tag (validant le concept de 'option_with_tags')
		template<typename T, typename = typename std::enable_if<!option_has_value<T>::value && has_option_tag_getter<T>::value>::type>
		// C++14: template<typename T, typename = typename std::enable_if_t<!option_has_value<T>::value && has_option_tag_getter<T>::value>>
		std::experimental::optional<T> get_opt(int argc, char* argv[]);

		//! spécialisation template utilisant SFINAE pour cibler les options ayant
		//! un parametre (validant les concepts de 'option_with_tags' et 'option_with_value')
		template<typename T, typename = typename std::enable_if<option_has_value<T>::value && has_option_tag_getter<T>::value>::type, typename = void>
		std::experimental::optional<T> get_opt(int argc, char* argv[]);

		//! spécialisation template utilisant SFINAE pour cibler les options ne 
		//! disposant pas de tags (validant le concept de 'option_with_value')
		template<typename T, typename = typename std::enable_if<option_has_value<T>::value && !has_option_tag_getter<T>::value>::type, typename = void, typename = void>
		std::experimental::optional<T> get_opt(int argc, char* argv[]);

		// TODO: ajouter une spécialisation de get_opt pour gérer les paramètres multiples pour une même option

		//------------------------------------------------------- Attributs privés

		typed_main_t m_typed_main_func;
		std::vector<std::pair<size_t, int>> m_found_parameters;

		//---------------------------------------------------- Fonctions statiques

		//! Fonction permettant la construction d'un tableau des tags de tout les types Args...
		template<typename T, typename = typename std::enable_if<has_option_tag_getter<T>::value>::type>
		static std::vector<std::string> get_option_tags();

		//! Fonction permettant la construction d'un tableau des tags de tout les types Args...
		template<typename T, typename = typename std::enable_if<!has_option_tag_getter<T>::value>::type, typename = void>
		static std::vector<std::string> get_option_tags();
	};

	//--------------------------------------------------------- Fonctions globales

	//! Fonction créant un objet de type 'Typed_main_binding<Args...>' à partir d'un pointeur de fonction vers un main typé
	//! @remarks This function permits implicit template deduction by taking C-style function pointer instead of std::function<...>
	template<typename... Args>
	Typed_main_binding<Args...> make_typed_main_binding(void(*typed_main)(std::experimental::optional<Args>...) )
	{
		return Typed_main_binding<Args...>(std::function<void(std::experimental::optional<Args>...)> (typed_main));
	}

	//----- Implémentation de la classe template Typed_main_binding<Args...> -----

	template<typename... Args>
	Typed_main_binding<Args...>::Typed_main_binding(const typed_main_t& typed_main)
		: m_typed_main_func(typed_main) { }
	
	template<typename... Args>
	void Typed_main_binding<Args...>::exec(int argc, char* argv[])
	{
		if (argc > 0 && argv != nullptr)
		{
			int arg_processed_cout = 1;

			// Store an array of booleans indicating Args...'s option type (tag presence and value presence)
			std::array<std::pair<bool, bool>, sizeof...(Args)> options_types_info = decltype(options_types_info){ { std::make_pair(has_option_tag_getter<Args>::value, option_has_value<Args>::value)... }};
			// C++14: std::array<std::pair<bool, bool>, sizeof...(Args)> options_types_info = { std::make_pair(has_option_tag_getter<Args>::value, option_has_value<Args>::value)... };
			// Store an array of options tags
			std::array<std::vector<std::string>, sizeof...(Args)> options_tags = decltype(options_tags){ { get_option_tags<Args>()... }};
			// C++14: std::array<std::vector<std::string>, sizeof...(Args)> options_tags = { get_option_tags<Args>()... }; 

			// Find presence of options with tags in argv
			int previous_found_option_param_count = 0;
			int previous_found_option_idx = 0;
			std::array<bool, sizeof...(Args)> processed_template_arg_indices;
			processed_template_arg_indices.fill(false);
			for (auto arg_idx = 1; arg_idx < argc; ++arg_idx)
			{
				std::string cmd_str(argv[arg_idx]);
				bool found = false;

				for (size_t T_idx = 0; T_idx < sizeof...(Args) && !found; ++T_idx)
				{
					auto type_info = options_types_info[T_idx];
					if(type_info.first) // if T has option tag getter (ignore mandatory/tagless parameters for now)
					{
						auto T_tags = options_tags[T_idx];
						if (T_tags.size() == 0)
							throw std::invalid_argument("Option with tags don't have any tag");
						for (const auto& tag : T_tags)
						{
							if (tag == cmd_str)
							{
								if(arg_idx <= previous_found_option_param_count + previous_found_option_idx)
									throw std::invalid_argument("No parameter after an option tag which need one");
								previous_found_option_param_count = type_info.second ? 1 : 0; // if T has option parameter/value
								arg_processed_cout += 1 + previous_found_option_param_count;
								if (processed_template_arg_indices[T_idx])
									// (TODO: allow it) Don't allow multiple option usage for simplicity reasons
									throw std::invalid_argument("Multiple tag for the same option");
								m_found_parameters.emplace_back(T_idx, arg_idx);
								processed_template_arg_indices[T_idx] = true;
								previous_found_option_idx = arg_idx;
								found = true;
								break;
							}
						}
					}
				}
			}

			// Check mandatory/tagless parameters presence
			std::vector<std::pair<size_t, size_t>> found_tagless_options;
			for (size_t T_idx = 0; T_idx < sizeof...(Args); ++T_idx)
			{
				auto type_info = options_types_info[T_idx];
				if (!type_info.first) // if T has option tag getter
				{
					int idx = 1;
					bool reached_later_option = false;
					for(const auto& p : m_found_parameters)
					{
						if (reached_later_option && p.second == idx)
							// mandatory/tagless parameter index is actually used by an option with a tag
							throw std::invalid_argument("Missing mandatory tagless option");

						if(p.first < T_idx)
						{
							if (reached_later_option)
								throw std::invalid_argument("Invalid command shape (options order imposed by tagless option(s) not respected)");
							idx = p.second + type_info.second ? 2 : 1; // if T has option parameter/value
						}
						else if(p.first > T_idx && !reached_later_option)
						{
							if (p.second == idx)
								throw std::invalid_argument("Missing mandatory tagless option or invalid command shape");
							reached_later_option = true;
							found_tagless_options.emplace_back(T_idx, idx);
							arg_processed_cout++;
						}
					}
					if(!reached_later_option && idx < argc)
					{
						found_tagless_options.emplace_back(T_idx, idx);
						arg_processed_cout++;
					}
				}
			}
			if(arg_processed_cout < argc)
				throw std::invalid_argument("Invalid options");

			m_found_parameters.insert(std::end(m_found_parameters), std::begin(found_tagless_options), std::end(found_tagless_options));

			// We have verified command shape and found all options/parameters of the command, we can now parse parameters and call typed main:
			m_typed_main_func((get_opt<Args>(argc, argv))...);
		}
	}

	template<typename... Args>
	template<typename T, typename>
	std::experimental::optional<T> Typed_main_binding<Args...>::get_opt(int argc, char* argv[])
	{
		constexpr auto opt_template_idx = index_of<T, Args...>();

		for (const auto& p : m_found_parameters)
		{
			if(p.first == opt_template_idx)
				return std::experimental::optional<T>(T());
		}
		return std::experimental::nullopt;
	}

	template<typename... Args>
	template<typename T, typename, typename>
	std::experimental::optional<T> Typed_main_binding<Args...>::get_opt(int argc, char* argv[])
	{
		constexpr auto opt_template_idx = index_of<T, Args...>();

		for (const auto& p : m_found_parameters)
		{
			if (p.first == opt_template_idx)
			{
				T param;
				if (p.second+1 >= argc)
					throw std::invalid_argument("No parameter after an option tag which need one");
				param.value = parse<decltype(param.value), true>(argv[p.second+1]);
				return std::experimental::optional<T>(param);
			}
		}
		return std::experimental::nullopt;
	}

	template<typename... Args>
	template<typename T, typename, typename, typename>
	std::experimental::optional<T> Typed_main_binding<Args...>::get_opt(int argc, char* argv[])
	{
		constexpr auto opt_template_idx = index_of<T, Args...>();

		for (const auto& p : m_found_parameters)
		{
			if (p.first == opt_template_idx)
			{
				T tagless_option_param;
				tagless_option_param.value = parse<decltype(tagless_option_param.value), true>(argv[p.second]);
				return std::experimental::optional<T>(tagless_option_param);
			}
		}
		// This kind of option is actually mandatory
		throw std::invalid_argument("Missing tagless mandatory parameter");
	}

	template<typename ... Args>
	template<typename T, typename>
	std::vector<std::string> Typed_main_binding<Args...>::get_option_tags() {
		const auto& tags_array = T::get_option_tags();
		return std::vector<std::string>(std::begin(tags_array), std::end(tags_array));
	}

	template<typename ... Args>
	template<typename T, typename, typename>
	std::vector<std::string> Typed_main_binding<Args...>::get_option_tags() { return std::vector<std::string>(0); }
}

#endif

