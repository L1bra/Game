#pragma once

#include "component.h"

#include <vector>
#include <memory>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{
	class Container : public Component
	{
	public:
		typedef std::shared_ptr<Container> pContainer;

	public:
		Container();

		void pack(Component::pComponent component);

		virtual bool is_selectable() const;
		virtual void handle_event(const std::optional<sf::Event> event);
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		bool has_selection() const;
		void select(std::size_t index);
		void select_next();
		void select_previous();
	private:
		std::vector<Component::pComponent> m_children;
		int m_selected_child;
	};
}