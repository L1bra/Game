#pragma once

#include "component.h"
#include "resource_identifier.h"
#include "resource_manager.h"
#include "utility.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include <vector>
#include <string>
#include <memory>
#include <functional>


namespace GUI
{
	class Button : public Component
	{
	public:
		typedef std::shared_ptr<Button> Ptr;
		typedef std::function<void()> Callback;

	public:
		Button(const FontHolder& fonts, const TextureHolder& texture);

		void set_callback(Callback callback);
		void set_text(const std::string& text);
		void set_characted_size(unsigned size);
		void set_toggle(bool flag);

		virtual bool is_selectable() const;
		virtual void select();
		virtual void deselect();

		virtual void activate();
		virtual void deactivate();

		virtual void handle_event(const std::optional<sf::Event> event);
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	private:
		Callback m_callback;

		sf::RectangleShape m_shape;
		const sf::Color m_idle_color;
		const sf::Color m_selected_color;
		const sf::Color m_pressed_color;

		sf::Text m_text;

		bool m_is_toggle;
	};
}