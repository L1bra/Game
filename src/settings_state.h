#pragma once

#include "state.h"
#include "window.h"
#include "player_controller.h"
#include "container.h"
#include "button.h"
#include "label.h"
#include "utility.h"
#include "resource_manager.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>

class SettingsState : public State
{
public:
	SettingsState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handle_event(const std::optional<sf::Event> event);

private:
	void update_labels();
	void add_button_label(PlayerController::Action action, float y, const std::string& text, Context context);
private:
	sf::RectangleShape m_background_shape;
	GUI::Container m_gui_container;

	std::array<GUI::Button::pButton, PlayerController::ActionCount> m_binding_buttons;
	std::array<GUI::Label::pLabel, PlayerController::ActionCount> m_binding_labels;
};