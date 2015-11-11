#include <iostream>

#include "capteur_event.h"
#include "utils.h"

namespace TP2
{
	capteur_event::capteur_event(sensor_t id, sensor_t d7, sensor_t hour, sensor_t min, traffic state)
	{
#ifdef MAP
		cout << "Appel au constructeur de 'capteur_event'" << endl;
#endif

		this->id = id;
		this->d7 = d7;
		this->hour = hour;
		this->min = min;
		set_traffic(state);
	}

	void capteur_event::set_traffic(traffic state)
	{
		switch (state)
		{
		case traffic::vert:
			traff = 0;
			return;
		case traffic::rouge:
			traff = 1;
			return;
		case traffic::orange:
			traff = 2;
			return;
		case traffic::noir:
			traff = 3;
			return;
		}
	}

	traffic capteur_event::get_traffic() const
	{
		switch (traff)
		{
		case 0:
			return traffic::vert;
		case 1:
			return traffic::rouge;
		case 2:
			return traffic::orange;
		case 3:
			return traffic::noir;
		}
		return traffic::vert; // impossible
	}

	//------------------------------------------------------- Surcharges d'opérateurs

	void swap(capteur_event& lhs, capteur_event& rhs) noexcept
	{
		// if one of the following swap calls isn't noexcept, we raise a static_assert
// Commenté car is_nothrow_swappable ne fonctionne pas avec gcc installé en IF
//		static_assert(is_nothrow_swappable<uint32_t&>(), "'Swap(capteur_event&, capteur_event&)' function could throw !");

		// enable ADL (following lines will use custom implementation of swap or std::swap if there isn't custom implementation)
		using std::swap;

		swap(reinterpret_cast<uint32_t&>(lhs), reinterpret_cast<uint32_t&>(rhs));
	}

	bool operator==(const capteur_event& lhs, const capteur_event& rhs) {
		return (reinterpret_cast<const uint32_t&>(lhs) & capteur_event::COMPARISION_MASK)
			== (reinterpret_cast<const uint32_t&>(rhs) & capteur_event::COMPARISION_MASK);
	}
	bool operator!=(const capteur_event& lhs, const capteur_event& rhs) { return !(lhs == rhs); }

	bool operator<(const capteur_event& lhs, const capteur_event& rhs) {
		return (reinterpret_cast<const uint32_t&>(lhs) & capteur_event::COMPARISION_MASK)
			< (reinterpret_cast<const uint32_t&>(rhs) & capteur_event::COMPARISION_MASK);	// exploite l'ordre des membres de la strucutre 'sensor_event' (et ignore l'attribut traff)
	}
	bool operator>(const capteur_event& lhs, const capteur_event& rhs) { return rhs < lhs; }
	bool operator<=(const capteur_event& lhs, const capteur_event& rhs) { return !(rhs < lhs); }
	bool operator>=(const capteur_event& lhs, const capteur_event& rhs) { return !(lhs < rhs); }

	std::ostream& operator<<(std::ostream& os, const traffic& state)
	{
		os << static_cast<char>(state);
		return os;
	}

	std::istream& operator>>(std::istream& is, traffic& state)
	{
		auto c = static_cast<char>(traffic::noir);
		is >> c;
		state = static_cast<traffic>(c);
		return is;
	}
}