#include "title_state.h"

TitleState::TitleState(StateStack& stack, Context context)
	:
	State(stack, context),
	m_text(context.m_fonts->get(Fonts::Main)),
	m_show_text(true),
	m_text_effect_time(sf::Time::Zero)
{
	const sf::Vector2f view_size = context.m_window->get_view().getSize();
	m_background_shape.setSize(view_size);
	m_background_shape.setFillColor(sf::Color::Black);

	m_text.setFont(context.m_fonts->get(Fonts::Main));
	m_text.setFillColor(sf::Color::White);
	m_text.setString("Press any key to start");

	gui::center_origin<sf::Text>(m_text);
	m_text.setPosition(context.m_window->get_view().getSize() / 2.f);
}

void TitleState::draw()
{
	Window& window = *get_context().m_window;
	window.draw(m_background_shape);

	if (m_show_text) window.draw(m_text);
}

bool TitleState::update(sf::Time dt)
{
	m_text_effect_time += dt;

	if (m_text_effect_time >= sf::seconds(0.5f))
	{
		m_show_text = !m_show_text;
		m_text_effect_time = sf::Time::Zero;
	}

	return true;
}

bool TitleState::handle_event(const std::optional<sf::Event> event)
{
	// if any key is pressed, trigger the next screen
	if (event->is<sf::Event::KeyReleased>())
	{
		request_stack_pop();
		request_stack_push(States::Menu);
	}

	return true;
}