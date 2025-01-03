#pragma once

#include "window.h"
#include "state.h"
#include "utility.h"
#include "resource_manager.h"

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"


class TitleState : public State
{
public:
	TitleState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handle_event(const std::optional<sf::Event> event);

private:
	//sf::Sprite m_background_sprite;
	sf::RectangleShape m_background_shape;
	sf::Text m_text;

	bool m_show_text;
	sf::Time m_text_effect_time;
};