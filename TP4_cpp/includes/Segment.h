#ifndef SEGMENT_H
#define SEGMENT_H

#include <ostream>
#include <string>

#include <boost/serialization/export.hpp>

#include "Utils.h"
#include "IShape.h"
#include "Command.h"

namespace TP4 { class Segment; }

namespace boost // C++ 17: namespace boost::serialization
{
	namespace serialization
	{
		template<class Archive>
		inline void save_construct_data(Archive& ar, const TP4::Segment* shape, const unsigned int file_version);

		template<class Archive>
		inline void load_construct_data(Archive& ar, TP4::Segment* shape, const unsigned int file_version);
	}
}

namespace TP4
{
	class Segment : public IShape
	{
	public:
		~Segment() override = default;

		void Move(coord_t dx, coord_t dy) override;
		bool Is_contained(const Point& point) const override;

		/*void Serialize_to(const std::ostream& output_stream) const override;
		void Deserialize_from(const std::istream& input_stream) override;*/

	protected:
		Point m_first_point = { 0U, 0U };
		Point m_second_point = { 1U, 0U };

		Segment(std::string&& name, Point&& first_point, Point&& second_point);

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		friend class boost::serialization::access;
		friend std::unique_ptr<Segment> make_segment(std::string name, Point first_point, Point second_point);

		template<class Archive>
		friend void boost::serialization::save_construct_data(Archive& ar, const Segment* shape, const unsigned int file_version);
		template<class Archive>
		friend void boost::serialization::load_construct_data(Archive& ar, Segment* shape, const unsigned int file_version);
	};

	template<class Archive>
	void Segment::serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::make_nvp("IShape", boost::serialization::base_object<IShape>(*this));
	}

	std::unique_ptr<Segment> make_segment(std::string name, Point first_point, Point second_point);
}

namespace boost
{
	namespace serialization
	{
		template<class Archive>
		inline void save_construct_data(Archive& ar, const TP4::Segment* shape, const unsigned int file_version)
		{
			// Save data required to construct instance
			ar << make_nvp("name", shape->m_name)
				<< make_nvp("first_point", shape->m_first_point)
				<< make_nvp("second_point", shape->m_second_point);
		}

		template<class Archive>
		inline void load_construct_data(Archive& ar, TP4::Segment* shape, const unsigned int file_version)
		{
			// Retrieve data from archive required to construct new instance
			TP4::name_t name;
			TP4::Point first_point, second_point;
			ar >> make_nvp("name", name)
				>> make_nvp("first_point", first_point)
				>> make_nvp("second_point", second_point);

			// Invoke inplace constructor to initialize instance of TP4::Segment
			::new(shape) TP4::Segment(std::move(name), std::move(first_point), std::move(second_point));
		}
	}
}

#endif //SEGMENT_H
