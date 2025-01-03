#pragma once

#include "state.h"
#include "window.h"
#include "utility.h"
#include "resource_manager.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/View.hpp>

class PauseState : public State
{
public:
	PauseState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handle_event(const std::optional<sf::Event> event);

private:
	sf::RectangleShape m_background_shape;
	sf::Text m_paused_text;
	sf::Text m_instruction_text;
};