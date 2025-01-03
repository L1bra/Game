#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <memory>


namespace sf
{
	class Event;
}

namespace GUI
{
	class Component : public sf::Drawable, public sf::Transformable
	{
	public:
		typedef std::shared_ptr<Component> Ptr;

	public:
		Component();
		virtual ~Component();

		virtual bool is_selectable() const = 0;
		bool is_selected() const;
		virtual void select();
		virtual void deselect();

		virtual bool is_active() const;
		virtual void activate();
		virtual void deactivate();

		virtual void handle_event(const std::optional<sf::Event> event) = 0;
	private:
		bool m_is_selected;
		bool m_is_active;
	};

}