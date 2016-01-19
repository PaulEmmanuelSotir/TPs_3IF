#ifndef SEGMENT_H
#define SEGMENT_H

#include <ostream>
#include <string>

#include "Utils.h"
#include "IShape.h"
#include "Command.h"

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
		void serialize(Archive & ar, const unsigned int version);

		friend class boost::serialization::access;
		friend std::unique_ptr<Segment> make_segment(std::string name, Point first_point, Point second_point);
	};

	template<class Archive>
	void Segment::serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<IShape>(*this);
		ar & m_first_point;
		ar & m_second_point;
	}

	std::unique_ptr<Segment> make_segment(std::string name, Point first_point, Point second_point);
}

#endif //SEGMENT_H
