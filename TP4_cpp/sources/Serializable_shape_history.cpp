#include "Serializable_shape_history.h"

namespace TP4
{
	const History_state& Shape_history::current() const
	{
		return *m_current_state;
	}

	History_state& Shape_history::current()
	{
		return *m_current_state;
	}

	void Shape_history::commit()
	{
		if(m_history.size() > 0)
		{
			if(std::distance(m_current_state, std::end(m_history)) > 1)
				m_history.erase(m_current_state + 1, std::end(m_history));
			m_history.push_back(m_history.back());
			if (m_history.size() > 2)
				m_history.erase(std::begin(m_history));
			m_current_state = std::end(m_history)-1;
		}
	}

	void Shape_history::undo()
	{
		if (m_history.size() > 0 && std::distance(std::begin(m_history), m_current_state) > 0)
			--m_current_state;
		else
			throw std::logic_error("Cannot undo anymore.");
	}

	void Shape_history::redo()
	{
		if (m_history.size() > 0 && std::distance(m_current_state, std::end(m_history)) > 1)
			++m_current_state;
		else
			throw std::logic_error("Cannot redo anymore.");
	}

	bool Is_contained(const History_shape& history_obj, Point point)
	{
		return history_obj.m_self->polymorphic_is_contained(std::move(point));
	}

	History_shape Move(const History_shape& history_obj, coord_t dx, coord_t dy)
	{
		return history_obj.m_self->polymorphic_move(dx, dy);
	}

	void Print(const History_shape& history_obj)
	{
		history_obj.m_self->polymorphic_print();
	}
}