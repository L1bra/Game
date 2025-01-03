#include "sprite_node.h"

SpriteNode::SpriteNode(const sf::Texture& texture)
	:
	m_sprite(texture)
{
}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& texture_rect)
	:
	m_sprite(texture, texture_rect)
{
}

void SpriteNode::draw_current(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}