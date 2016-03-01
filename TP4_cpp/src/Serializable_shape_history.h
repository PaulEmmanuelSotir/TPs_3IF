/*********************************************************************************
									History
									-------
*********************************************************************************/

#ifndef HISTORY_H
#define HISTORY_H

#include <unordered_map>
#include <ostream>
#include <boost/smart_ptr/shared_ptr.hpp> //#include <memory>
#include <vector>

#include <boost/config.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/assume_abstract.hpp>

#include "Command.h"

//----------------------------------------------------------- Forward declarations
namespace TP4
{
	struct Rectangle;
	struct Segment;
	struct Polygon;

	template<bool is_union>
	struct Group;

	using Shape_union = Group<true>;
	using Shape_intersection = Group<false>;
}

namespace TP4
{
	//----------------------------------------------------------------------------
	//! Classe permettant le polymorphisme sur tout type T validant le concept de forme (ayant une surcharge de 'move' et 'Is_contained')
	//! Cette classe permet d'isoler le méchanisme de polymorphisme des types de formes géométrique.
	//! Ainsi, les formes géométriques sont des types simples sans héritage (et immutables), ce qui facilite l'ajout de nouvelles formes
	//! et rend le code plus clair.
	//! @see https://channel9.msdn.com/Events/GoingNative/2013/Inheritance-Is-The-Base-Class-of-Evil
	//! La classe est serialisable grâce à boost::serialization.
	//! @remarks boost gère également la serialisation des shared_ptr dans TP4::History_shape de manière à ce que seul une copie d'une 
	//! même forme soit en mémoire même si l'on déserialise plusieurs pointeurs vers cette forme.
	//----------------------------------------------------------------------------
	class History_shape final
	{
	public:
		History_shape() = default;
		//! Constructeur de la classe History_shape à partir d'une forme de type T.
		//! Ce constructeur permet en autre la convertion implicite d'un type validant le concept de forme vers 'History_shape'.
		template<typename Shape_t>
		History_shape(Shape_t shape) : m_self(boost::shared_ptr<shape_model<Shape_t>>(new shape_model<Shape_t>(std::move(shape)))) // Boost 60: std::make_shared<shape_model<Shape_t>>(std::move(shape))
		{ }

		History_shape clone() const;

		friend bool Is_contained(const History_shape& history_obj, Point point);
		friend History_shape Move(const History_shape& history_obj, coord_t dx, coord_t dy);
		friend void Print(const History_shape& history_obj);

	private:
		struct shape_concept
		{
			virtual ~shape_concept() = default;
			virtual bool polymorphic_is_contained(Point point) const = 0;
			virtual History_shape polymorphic_move(coord_t dx, coord_t dy) const = 0;
			virtual void polymorphic_print() const = 0;
			virtual History_shape polymorphic_clone() const = 0;

		private:
			friend class boost::serialization::access;

			template<typename Archive>
			void serialize(Archive& ar, const unsigned int version)
			{ }
		};

		//! Shape model forward declaration
		template<typename Shape_t>
		struct shape_model;

		//! Pointeur vers une forme quelquonque (par le quel les appels polymorphiques sont faits)
		//! @remarks C'est un shared_ptr car ce pointeur est propiétaire de la forme pointée et que
		//! l'historique peut contenir des mêmes formes à des moments différents (plusieurs shared_ptr
		//! pointent alors vers la même forme)
		//! @remarks on utilise boost::shared_ptr plutot que std::shared_ptr car la version de boost 
		//! installée en IF ne supporte pas la serialisation de std::shared_ptr.
		boost::shared_ptr<const shape_concept> m_self;

		friend class boost::serialization::access;

		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			// Ajoute au registre de l'archive de serialisation les types dérivés de 'shape_concept'. 
			// Cela permet à boost::serialization de gèrer le polymorphisme lors de la (de)serialisation.
			ar.template register_type<shape_model<Rectangle>>();
			ar.template register_type<shape_model<Segment>>();
			ar.template register_type<shape_model<Polygon>>();
			ar.template register_type<shape_model<Shape_union>>();
			ar.template register_type<shape_model<Shape_intersection>>();

			// Serialise le shared pointer
			ar & boost::serialization::make_nvp("shape_ptr", m_self);
		}
	};

	//! L'état d'un historique est une collection de 'History_shape' (History_state) et l'on copie cette collection à chaque étape 
	//! annulable (appel à 'commit'), mais les formes ne sont pas copiées (les shared_ptr sont copiés). Finalement seul les modifications
	//! sont retenues dans l'historique puisque les formes sont immutables (de nouvelles fomes sont crées si des modifications sont 
	//! nescessaires, elles ne seront présentes en mémoire q'une seule fois sinon).
	using History_state = std::unordered_map<name_t, History_shape>;

	struct Shape_history
	{
		const History_state& current() const;
		History_state& current();
		void commit();
		void undo();
		void redo();
		void clear();

	private:
		std::vector<History_state> m_history = { History_state() };
		decltype(m_history)::iterator m_current_state = std::begin(m_history);
	};

	bool Is_contained(const History_shape& history_obj, Point point);
	History_shape Move(const History_shape& history_obj, coord_t dx, coord_t dy);
}

//------------------------------------------ History_shape::shape_model inner type
namespace TP4
{
	template<typename Shape_t>
	struct History_shape::shape_model : shape_concept
	{
		shape_model() = default;
		explicit shape_model(Shape_t shape) : shape(std::move(shape))
		{ }

		bool polymorphic_is_contained(Point point) const override
		{
			return Is_contained(shape, std::move(point));
		}

		History_shape polymorphic_move(coord_t dx, coord_t dy) const override
		{
			return Move(shape, dx, dy);
		}

		void polymorphic_print() const override
		{
			std::cout << shape;
		}

		History_shape polymorphic_clone() const override
		{
			return shape;
		}

		Shape_t shape;

	private:
		friend class boost::serialization::access;

		template<typename Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::make_nvp("shape_concept", boost::serialization::base_object<shape_concept>(*this))
				& boost::serialization::make_nvp("shape", shape);
		}
	};
}

//------------------------------------------------------------ Boost serialization
namespace boost
{
	namespace serialization
	{
		//-------------------------------------------- History_state serialization
		template<typename Archive>
		void save(Archive& ar, const TP4::History_state& shapes, const unsigned int version)
		{
			// Serialisation manuelle de 'shapes' (la version de boost installée en IF ne supporte pas la serialisation des unordered_map)
			auto size = shapes.size();
			ar << make_nvp("shape_count", size);
			for (const auto& p : shapes)
			{
				ar <<  make_nvp("name", p.first)
					<< make_nvp("history_shape", p.second);
			}
		}

		template<typename Archive>
		void load(Archive& ar, TP4::History_state& shapes, const unsigned int version)
		{
			shapes.clear();

			// Deserialisation manuelle de 'shapes' (la version de boost installée en IF ne supporte pas la serialisation des unordered_map)
			TP4::History_state::size_type size;
			ar >> make_nvp("shape_count", size);
			shapes.reserve(size);

			while (size-- != 0)
			{
				TP4::History_shape shape;
				TP4::name_t name;
				ar >> make_nvp("name", name);
				ar >> make_nvp("history_shape", shape);
				shapes[std::move(name)] = std::move(shape);
			}
		}
	}
}

BOOST_SERIALIZATION_SPLIT_FREE(TP4::History_state)

#endif // !HISTORY_H
