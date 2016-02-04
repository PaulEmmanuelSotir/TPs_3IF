/*********************************************************************************
									Rectangle
									---------
*********************************************************************************/

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <string>

#include "Utils.h"
#include "IShape.h"

//----------------------------------------------------------- forward declarations
namespace TP4
{
	//--------------------------------------- Serialized class forward declaration
	class Rectangle;
}

namespace boost // C++ 17: namespace boost::serialization
{
	namespace serialization
	{
		template<class Archive>
		inline void save_construct_data(Archive& ar, const TP4::Rectangle* shape, const unsigned int file_version);

		template<class Archive>
		inline void load_construct_data(Archive& ar, TP4::Rectangle* shape, const unsigned int file_version);
	}
}

//! \namespace TP4
//! espace de nommage regroupant le code crée pour le TP4 de C++
namespace TP4
{
	//----------------------------------------------------------------------------
	//! Classe représentant un rectangle définit à partir de son coin superieur 
	//! gauche et de son coin inferieur bas. La classe est serialisable grâce à 
	//! boost::serialization.
	//----------------------------------------------------------------------------
	class Rectangle : public IShape
	{
	public:
		~Rectangle() override = default;

		void Move(coord_t dx, coord_t dy) override;
		bool Is_contained(const Point& point) const override;

	protected:
		Point m_top_left_corner = { 0U, 1U };
		Point m_bottom_right_corner = { 1U, 0U };

		Rectangle(name_t&& name, Point&& top_left_corner, Point&& bottom_right_corner);

		friend std::unique_ptr<Rectangle> make_rectangle(name_t name, Point top_left_corner, Point bottom_right_corner);

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version);

		template<class Archive>
		friend void boost::serialization::save_construct_data(Archive& ar, const Rectangle* shape, const unsigned int file_version);
		template<class Archive>
		friend void boost::serialization::load_construct_data(Archive& ar, Rectangle* shape, const unsigned int file_version);
	};

	std::unique_ptr<Rectangle> make_rectangle(name_t name, Point top_left_corner, Point bottom_right_corner);

	template<class Archive>
	void Rectangle::serialize(Archive& ar, const unsigned int version)
	{
		ar & boost::serialization::make_nvp("IShape", boost::serialization::base_object<IShape>(*this));
	}
}

namespace boost
{
	namespace serialization
	{
		template<class Archive>
		inline void save_construct_data(Archive& ar, const TP4::Rectangle* shape, const unsigned int file_version)
		{
			// Save data required to construct instance
			ar << make_nvp("name", shape->m_name)
				<< make_nvp("top_left_corner", shape->m_top_left_corner)
				<< make_nvp("bottom_right_corner", shape->m_bottom_right_corner);
		}

		template<class Archive>
		inline void load_construct_data(Archive& ar, TP4::Rectangle* shape, const unsigned int file_version)
		{
			// Retrieve data from archive required to construct new instance
			TP4::name_t name;
			TP4::Point top_left_corner, bottom_right_corner;
			ar >> make_nvp("name", name)
				>> make_nvp("top_left_corner", top_left_corner)
				>> make_nvp("bottom_right_corner", bottom_right_corner);

			// Invoke inplace constructor to initialize instance of TP4::Rectangle
			::new(shape) TP4::Rectangle(std::move(name), std::move(top_left_corner), std::move(bottom_right_corner));
		}
	}
}

#endif // RECTANGLE_H
