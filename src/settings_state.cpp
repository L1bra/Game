#include "settings_state.h"

SettingsState::SettingsState(StateStack& stack, Context context)
	:
	State(stack, context),
	m_gui_container()
{
	const sf::Vector2f view_size = context.m_window->get_view().getSize();
	const auto vm = context.m_window->get_gfx().resolution;

	m_background_shape.setSize(view_size);
	m_background_shape.setScale({ view_size.x / game_resolution.x, view_size.y / game_resolution.y });
	m_background_shape.setFillColor(sf::Color::Black);

	// build key binding button and lables
	add_button_label(PlayerController::MoveLeft, 150.f, "Move Left", context);
	add_button_label(PlayerController::MoveRight, 200.f, "Move Right", context);
	add_button_label(PlayerController::MoveUp, 250.f, "Move Up", context);
	add_button_label(PlayerController::MoveDown, 300.f, "Move Down", context);

	update_labels();

	auto back_button = std::make_shared<GUI::Button>(*context.m_fonts, *context.m_textures);
	back_button->setPosition({ 80.f, 375.f });
	back_button->set_text("Back");
	back_button->set_characted_size(gui::calc_char_size(vm));
	back_button->set_callback(std::bind(&SettingsState::request_stack_pop, this));

	m_gui_container.pack(back_button);
}

void SettingsState::draw()
{
	Window& window = *get_context().m_window;

	window.draw(m_background_shape);
	window.draw(m_gui_container);
}

bool SettingsState::update(sf::Time)
{
	return true;
}

bool SettingsState::handle_event(const std::optional<sf::Event> event)
{
	bool is_key_binding = false;

	// iterate through all key binding buttons to see if they are being pressed, waiting for the user to enter a key
	for (std::size_t action = 0; action < PlayerController::ActionCount; ++action)
	{
		if (m_binding_buttons[action]->is_active())
		{
			is_key_binding = true;
			if (event->is<sf::Event::KeyReleased>())
			{
				get_context().m_player_controller->assign_key(static_cast<PlayerController::Action>(action), event->getIf<sf::Event::KeyPressed>()->code);
				m_binding_buttons[action]->deactivate();
			}
			break;
		}
	}

	// if pressed button changed key binding, update labels; otherwise consider other buttons in container
	if (is_key_binding)
		update_labels();
	else
		m_gui_container.handle_event(event);

	return false;
}

void SettingsState::update_labels()
{
	PlayerController& player_controller = *get_context().m_player_controller;

	for (std::size_t i = 0; i < PlayerController::ActionCount; ++i)
	{
		sf::Keyboard::Key key = player_controller.get_assigned_key(static_cast<PlayerController::Action>(i));
		//m_binding_labels[i]->set_text(to_string(key));
	}
}

void SettingsState::add_button_label(PlayerController::Action action, float y, const std::string& text, Context context)
{
	const auto vm = context.m_window->get_gfx().resolution;

	m_binding_buttons[action] = std::make_shared<GUI::Button>(*context.m_fonts, *context.m_textures);
	m_binding_buttons[action]->setPosition({ 80.f, y });
	m_binding_buttons[action]->set_text(text);
	m_binding_buttons[action]->set_characted_size(gui::calc_char_size(vm));
	m_binding_buttons[action]->set_toggle(true);

	m_binding_labels[action] = std::make_shared<GUI::Label>("", *context.m_fonts);
	m_binding_labels[action]->setPosition({ 300.f, y + 15.f });
	m_binding_labels[action]->set_character_size(gui::calc_char_size(vm));

	m_gui_container.pack(m_binding_buttons[action]);
	m_gui_container.pack(m_binding_labels[action]);
}