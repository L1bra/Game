#include "label.h"


namespace GUI
{
	Label::Label(const std::string& text, const FontHolder& fonts)
		:
		m_text(fonts.get(Fonts::Main), text, 16)
	{
	}

	bool Label::is_selectable() const
	{
		return false;
	}

	void Label::handle_event(const std::optional<sf::Event> event)
	{
	}

	void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(m_text, states);
	}

	void Label::set_text(const std::string& text)
	{
		m_text.setString(text);
	}

	void Label::set_character_size(const unsigned int size)
	{
		m_text.setCharacterSize(size);
	}
}