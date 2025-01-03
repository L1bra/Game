#pragma once

#include "state.h"
#include "window.h"
#include "container.h"
#include "Button.h"
#include "utility.h"
#include "resource_manager.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/View.hpp>


class MenuState : public State
{
public:
	MenuState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handle_event(const std::optional<sf::Event> event);
private:
	sf::RectangleShape m_background_shape;
	GUI::Container m_gui_container;
};