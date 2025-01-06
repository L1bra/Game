#include "container.h"

namespace GUI
{
	Container::Container()
		:
		m_children(),
		m_selected_child(-1)
	{
	}

	void Container::pack(Component::pComponent component)
	{
		m_children.push_back(component);

		if (!has_selection() && component->is_selectable())
			select(m_children.size() - 1);
	}

	bool Container::is_selectable() const
	{
		return false;
	}

	void Container::handle_event(const std::optional<sf::Event> event)
	{
		// if we have selected a child then give it events
		if (has_selection() && m_children[m_selected_child]->is_active())
		{
			m_children[m_selected_child]->handle_event(event);
		}
		else if (event->is<sf::Event::KeyReleased>())
		{
            switch(event->getIf<sf::Event::KeyReleased>()->code)
            {
    			case sf::Keyboard::Key::Up:
    			{
    				select_previous();
    			} break;

    			case sf::Keyboard::Key::Down:
    			{
    				select_next();
    			} break;

    			case sf::Keyboard::Key::Enter:
    			{
    				if (has_selection()) m_children[m_selected_child]->activate();
    			} break;

    			default: break;
    		}
        }
	}

	void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		for (const Component::pComponent& child : m_children)
			target.draw(*child, states);
	}

	bool Container::has_selection() const
	{
		return m_selected_child >= 0;
	}

	void Container::select(std::size_t index)
	{
		if (m_children[index]->is_selectable())
		{
			if (has_selection())
				m_children[m_selected_child]->deselect();

			m_children[index]->select();
			m_selected_child = index;
		}
	}

	void Container::select_next()
	{
		if (!has_selection()) return;

		// search next component that is selectable, wrap around if necessary
		int next = m_selected_child;
		do
		{
			next = (next + 1) % m_children.size();
		} while (!m_children[next]->is_selectable());

		// select that component
		select(next);
	}

	void Container::select_previous()
	{
		if (!has_selection()) return;

		// search next
		int prev = m_selected_child;
		do
		{
			prev = (prev + m_children.size() - 1) % m_children.size();
		} while (!m_children[prev]->is_selectable());

		// select
		select(prev);
	}
}