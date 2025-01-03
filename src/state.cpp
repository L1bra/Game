#include "state.h"
#include "state_stack.h"


State::Context::Context(Window& window, TextureHolder& textures, FontHolder& fonts, Player& player, ldtk::Project& project)
	:
	m_window(&window),
	m_textures(&textures),
	m_fonts(&fonts),
	m_player(&player),
	m_ldtk_project(&project)
{
}

State::State(StateStack& stack, Context context)
	:
	m_stack(&stack),
	m_context(context)
{
}

State::~State()
{
}

void State::request_stack_push(States::ID state_id)
{
	m_stack->push_state(state_id);
}

void State::request_stack_pop()
{
	m_stack->pop_state();
}

void State::request_state_clear()
{
	m_stack->clear_states();
}

State::Context State::get_context() const
{
	return m_context;
}