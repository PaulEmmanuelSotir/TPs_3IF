
#include "ville.h"
#include "capteur.h"

namespace TP2
{
	ville::ville()
	{
		//TODO: init m_capteurs

		for (size_t i = 0; i < DAYS_COUNT; i++)
			for (size_t j = 0; j < DAYS_COUNT; i++)
				m_weekTrafficDistribution[i][j] = pair<unsigned int, unsigned int>(0, 0);
	}

	void ville::ajouter_capteur(const capteur & sensor)
	{
		m_capteurs[m_size++] = sensor;

		if (sensor.getTraffic() == capteur::traffic::noir || sensor.getTraffic() == capteur::traffic::orange)
		{

		}
	}

	capteur ville::getSensorById(capteur::ID_t id)
	{
		for (size_t i = 0; i < m_size; i++)
		{
			auto capt = m_capteurs[i];
			if (capt.getID() == id)
				return capt;
		}
	}
}