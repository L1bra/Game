#include "pause_state.h"

PauseState::PauseState(StateStack& stack, Context context)
	:
	State(stack, context),
	m_background_shape(),
	m_paused_text(context.m_fonts->get(Fonts::Main)),
	m_instruction_text(context.m_fonts->get(Fonts::Main))
{
	sf::Vector2f view_size = context.m_window->get_view().getSize();

	m_paused_text.setFont(context.m_fonts->get(Fonts::Main));
	m_paused_text.setString("Game Paused");
	m_paused_text.setCharacterSize(70);
	//gui::center_origin<sf::Text>(m_paused_text);
	m_paused_text.setPosition({ 0.5f * view_size.x, 0.4f * view_size.y });

	m_instruction_text.setFont(context.m_fonts->get(Fonts::Main));
	m_instruction_text.setString("(Press BACKSPACE to return to the main menu)");
	//gui::center_origin<sf::Text>(m_instruction_text);
	m_instruction_text.setPosition({ 0.5f * view_size.x, 0.6f * view_size.y });
}

void PauseState::draw()
{
	Window& window = *get_context().m_window;
	window.set_view(window.get_default_view());

	m_background_shape.setFillColor(sf::Color(0, 0, 0, 150));
	m_background_shape.setSize(window.get_view().getSize());

	window.draw(m_background_shape);
	window.draw(m_paused_text);
	window.draw(m_instruction_text);
}

bool PauseState::update(sf::Time dt)
{
	return false;
}

bool PauseState::handle_event(const std::optional<sf::Event> event)
{
	if (!event->is<sf::Event::KeyPressed>()) return false;

	if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
	{
		// remove itself to return to the game
		request_stack_pop();
	}

	if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Backspace)
	{
		// remove itself to return to the game
		request_state_clear();
		request_stack_push(States::Menu);
	}

	return false;
}