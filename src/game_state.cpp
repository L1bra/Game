#include "game_state.h"



GameState::GameState(StateStack& stack, Context context)
    :
    State(stack, context),
    m_world(context.m_window->get_SFML_window(), *context.m_fonts),
    m_player_controller(*context.m_player_controller)
{
}


void GameState::draw()
{
    m_world.draw();
}

bool GameState::update(sf::Time dt)
{
    m_world.update(dt);

    CommandQueue& commands = m_world.get_command_queue();
    m_player_controller.handle_realtime_input(commands);

    return true;
}


bool GameState::handle_event(const std::optional<sf::Event> event)
{
    // Game input handling
    CommandQueue& commands = m_world.get_command_queue();
    m_player_controller.handle_event(event, commands);

    if(event->is<sf::Event::FocusLost>())
    {
        request_stack_push(States::Pause);
    }

	// Escape pressed, trigger the pause screen
	if (const auto* key_pressed = event->getIf<sf::Event::KeyPressed>())
	{
		if(key_pressed->code == sf::Keyboard::Key::Escape)
		{
            request_stack_push(States::Pause);
		}
	}

    return true;
}