/*********************************************************************************
										Polygon
										-------
*********************************************************************************/

#ifndef POLYGON_H
#define POLYGON_H

#include <ostream>
#include <string>

#include <boost/serialization/utility.hpp>
#include <boost/serialization/unordered_set.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/unique_ptr.hpp>

#include "IShape.h"
#include "Utils.h"

namespace TP4 { class Polygon; }

namespace boost // C++ 17: namespace boost::serialization
{
	namespace serialization
	{
		template<class Archive>
		inline void save_construct_data(Archive& ar, const TP4::Polygon* shape, const unsigned int file_version);

		template<class Archive>
		inline void load_construct_data(Archive& ar, TP4::Polygon* shape, const unsigned int file_version);
	}
}

//! \namespace TP4
//! espace de nommage regroupant le code cr»e pour le TP4 de C++
namespace TP4
{
	class Polygon : public IShape
	{
	public:
		~Polygon() override = default;

		void Move(coord_t dx, coord_t dy) override;
		bool Is_contained(const Point& point) const override;

		//void Serialize_to(const std::ostream& output_stream) const override;
		//void Deserialize_from(const std::istream& input_stream) override;

	protected:
		std::vector<Point> m_vertices = { { 0U, 0U }, { 2U, 0U }, { 1U, 2U } };

		Polygon(std::string&& name, std::vector<Point>&& vertices);

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		friend class boost::serialization::access;
		friend std::unique_ptr<Polygon> make_polygon(std::string name, std::vector<Point> vertices);

		template<class Archive>
		friend void boost::serialization::save_construct_data(Archive& ar, const Polygon* shape, const unsigned int file_version);
		template<class Archive>
		friend void boost::serialization::load_construct_data(Archive& ar, Polygon* shape, const unsigned int file_version);
	};

	std::unique_ptr<Polygon> make_polygon(std::string name, std::vector<Point> vertices);

	template<class Archive>
	void Polygon::serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::make_nvp("IShape", boost::serialization::base_object<IShape>(*this));
	}

}

namespace boost
{
	namespace serialization
	{
		template<class Archive>
		inline void save_construct_data(Archive& ar, const TP4::Polygon* shape, const unsigned int file_version)
		{
			// Save data required to construct instance
			ar  << make_nvp("name", shape->m_name)
				<< make_nvp("vertices", shape->m_vertices);
		}

		template<class Archive>
		inline void load_construct_data(Archive& ar, TP4::Polygon* shape, const unsigned int file_version)
		{
			// Retrieve data from archive required to construct new instance
			TP4::name_t name;
			std::vector<TP4::Point> vertices;
			ar  >> make_nvp("name", name)
				>> make_nvp("vertices", vertices);

			// Invoke inplace constructor to initialize instance of TP4::Polygon
			::new(shape) TP4::Polygon(std::move(name), std::move(vertices));
		}
	}
}

#endif // POLYGON_H