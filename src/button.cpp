#include "Button.h"


namespace GUI
{
	Button::Button(const FontHolder& fonts, const TextureHolder& textures)
		:
		m_callback(),
		m_idle_color(sf::Color(200, 200, 200, 200)),
		m_selected_color(sf::Color(255, 255, 255, 255)),
		m_pressed_color(sf::Color(20, 20, 20, 50)),
		m_shape(),
		m_text(fonts.get(Fonts::Main), "", 16),
		m_is_toggle(false)
	{
		m_shape.setFillColor(sf::Color::Transparent);
		m_shape.setOutlineThickness(1.f);
		m_shape.setOutlineColor(sf::Color::Transparent);

		sf::FloatRect bounds = m_shape.getLocalBounds();
		m_text.setPosition({ bounds.size.x / 2.f, bounds.size.y / 2.f });
		m_text.setFillColor(m_idle_color);
	}

	void Button::set_callback(Callback callback)
	{
		m_callback = std::move(callback);
	}

	void Button::set_text(const std::string& text)
	{
		m_text.setString(text);
		//gui::center_origin<sf::Text>(m_text);
	}

	void Button::set_characted_size(unsigned int size)
	{
		m_text.setCharacterSize(size);
	}

	void Button::set_toggle(bool flag)
	{
		m_is_toggle = flag;
	}

	bool Button::is_selectable() const
	{
		return true;
	}

	void Button::select()
	{
		Component::select();
		m_text.setFillColor(m_selected_color);
	}

	void Button::deselect()
	{
		Component::deselect();
		m_text.setFillColor(m_idle_color);
	}

	void Button::activate()
	{
		Component::activate();

		// if we are toggle then we should show that the button is pressed and thus "toggled"
		if (m_is_toggle)
			m_text.setFillColor(m_pressed_color);

		if (m_callback) m_callback();

		// if we are not a toggle then deactivate the button since we are just momentarily activated.
		if (!m_is_toggle) deactivate();
	}

	void Button::deactivate()
	{
		Component::deactivate();

		if (m_is_toggle)
		{
			// reset texture to right one depending on if we are selected or not
			if (is_selected())
				m_text.setFillColor(m_selected_color);
			else
				m_text.setFillColor(m_idle_color);
		}
	}

	void Button::handle_event(const std::optional<sf::Event> event)
	{
	}

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(m_shape, states);
		target.draw(m_text, states);
	}
}