#pragma once

#include "resource_manager.h"
#include "resource_identifier.h"
#include "scene_node.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>


class TextNode : public SceneNode
{
public:
	explicit TextNode(const FontHolder& fonts, const std::string& text);

	void set_string(const std::string& text);
private:
	virtual void draw_current(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Text m_text;
};