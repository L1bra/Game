#include "text_node.h"

#include "utility.h"

TextNode::TextNode(const FontHolder& fonts, const std::string& text)
	:
	m_text(fonts.get(Fonts::Main), text, 20)
{
}

void TextNode::set_string(const std::string& text)
{
	m_text.setString(text);
	gui::center_origin<sf::Text>(m_text);
}

void TextNode::draw_current(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_text, states);
}
