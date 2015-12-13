#ifndef TYPED_MAIN_BINDING_H
#define TYPED_MAIN_BINDING_H

#include <vector>
#include <utility>
#include "optional.h"
#include <type_traits>

#include "Utils.h"

namespace TP3
{
	template<size_t N>
	using tags_t = std::array<std::string, N>;

	template<typename T, typename = void>
	struct option_has_value : std::false_type { };

	template<typename T>
	struct option_has_value<T, decltype(std::declval<T>().value, void())> : std::true_type { };

	template<typename T, typename = void>
	struct has_option_tag_getter : std::false_type { };

	template<typename T>
	struct has_option_tag_getter<T, decltype(std::declval<T>().get_option_tags(), void())> : std::true_type { };

	// TODO: verifier que T n'est pas tags_t<0>
/*	template<typename T>
	constexpr bool has_option_tag()
	{ return has_option_tag_getter<T>::value && std::is_same<decltype(std::declval<T>().get_option_tags()), tags_t<0>>::value; }*/

	//! ...
	//! @remarks
	//!		Uses 'TP3::parse<T,true>' to get options values from std:string. User could overload 'TP3::parse<T,true>' for its own types if needed.
	//! Les arguments templates 'Args' doivent être conformes au concept 'option_with_param' ou 'option'.
	//! Description du concept 'option' ...
	//! Description du concept 'option_with_param' ...
	template<typename... Args>
	class Typed_main_binding
	{
	public:
		using typed_main_t = std::function<void(std::experimental::optional<Args>...)>;

		explicit Typed_main_binding(const typed_main_t& typed_main);

		void exec(int argc, char* argv[]);

	private:
		template<typename T, typename = typename std::enable_if<!option_has_value<T>::value && has_option_tag_getter<T>::value>::type>
		std::experimental::optional<T> get_opt(int argc, char* argv[]);

		//! spécialisation template utilisant SFINAE pour cibler les options ayant un parametre (type T ayant un membre 'value')
		template<typename T, typename = typename std::enable_if<option_has_value<T>::value && has_option_tag_getter<T>::value>::type, typename = void>
		std::experimental::optional<T> get_opt(int argc, char* argv[]);

		//! spécialisation template utilisant SFINAE pour cibler les options ne disposant pas de getter 'get_option_tags()'
		template<typename T, typename = typename std::enable_if<option_has_value<T>::value && !has_option_tag_getter<T>::value>::type, typename = void, typename = void>
		std::experimental::optional<T> get_opt(int argc, char* argv[]);

		// TODO: ajouter une spécialisation de get_opt pour gérer les paramètres multiples pour une même option

		template<typename T, typename = typename std::enable_if<has_option_tag_getter<T>::value>::type>
		static std::vector<std::string> get_option_tags();

		template<typename T, typename = typename std::enable_if<!has_option_tag_getter<T>::value>::type, typename = void>
		static std::vector<std::string> get_option_tags();

		typed_main_t m_typed_main_func;
		std::vector<std::pair<size_t, int>> m_found_parameters;
	};

	//! ...
	//! @remarks This function permits implicit template deduction by taking C-style function pointer instead of std::function<...>
	template<typename... Args>
	Typed_main_binding<Args...> make_typed_main_binding(void(*typed_main)(std::experimental::optional<Args>...) )
	{
		return Typed_main_binding<Args...>(std::function<void(std::experimental::optional<Args>...)> (typed_main));
	}

	template<typename... Args>
	Typed_main_binding<Args...>::Typed_main_binding(const typed_main_t& typed_main)
		: m_typed_main_func(typed_main) { }
	
	//! ...
	//! @throw std::invalid_argument
	//! @throw std::out_of_range
	template<typename... Args>
	void Typed_main_binding<Args...>::exec(int argc, char* argv[])
	{
		if (argc > 0 && argv != nullptr)
		{
			int arg_processed_cout = 1;

			// Store an array of booleans indicating Args...'s option type (tag presence and value presence)
			std::array<std::pair<bool, bool>, sizeof...(Args)> options_types_info = decltype(options_types_info){ { std::make_pair(has_option_tag_getter<Args>::value, option_has_value<Args>::value)... }};
			// c++14: std::array<std::pair<bool, bool>, sizeof...(Args)> options_types_info = { std::make_pair(has_option_tag_getter<Args>::value, option_has_value<Args>::value)... };
			// Store an array of options tags
			std::array<std::vector<std::string>, sizeof...(Args)> options_tags = decltype(options_tags){ { get_option_tags<Args>()... }};
			// c++14: std::array<std::vector<std::string>, sizeof...(Args)> options_tags = { get_option_tags<Args>()... }; 

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
						for (const auto& tag : options_tags[T_idx])
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
			this->m_typed_main_func((get_opt<Args>(argc, argv))...);
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

