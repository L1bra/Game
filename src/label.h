#pragma once

#include "component.h"
#include "resource_identifier.h"
#include "resource_manager.h"
#include "utility.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{
	class Label : public Component
	{
	public:
		typedef std::shared_ptr<Label> Ptr;
	public:
		Label(const std::string& text, const FontHolder& fonts);

		virtual bool is_selectable() const;
		void set_text(const std::string& text);
		void set_character_size(const unsigned int size);

		virtual void handle_event(const std::optional<sf::Event> event);
	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	private:
		sf::Text m_text;
	};
}