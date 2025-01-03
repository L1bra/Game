#pragma once

#include "scene_node.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class SpriteNode : public SceneNode
{
private:
	sf::Sprite m_sprite;
private:
	virtual void draw_current(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	explicit SpriteNode(const sf::Texture& texture);
	SpriteNode(const sf::Texture& texture, const sf::IntRect& texture_rect);

};