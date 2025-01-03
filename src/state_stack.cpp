#include "state_stack.h"

#include <cassert>

StateStack::StateStack(State::Context context)
	:
	m_stack(),
	m_pending_list(),
	m_context(context),
	m_factories()
{
}

void StateStack::update(sf::Time dt)
{
	for (auto it = m_stack.rbegin(); it != m_stack.rend(); ++it)
	{
		if (!(*it)->update(dt)) break;
	}

	apply_pending_changes();
}

void StateStack::draw()
{
	for (State::Ptr& state : m_stack)
	{
		state->draw();
	}
}

void StateStack::handle_event(const std::optional<sf::Event> event)
{
	for (auto it = m_stack.rbegin(); it != m_stack.rend(); ++it)
	{
		if (!(*it)->handle_event(event)) break;
	}

	apply_pending_changes();
}

void StateStack::push_state(States::ID state_id)
{
	m_pending_list.push_back(PendingChange(Push, state_id));
}

void StateStack::pop_state()
{
	m_pending_list.push_back(PendingChange(Pop));
}

void StateStack::clear_states()
{
	m_pending_list.push_back(PendingChange(Clear));
}

bool StateStack::is_empty() const
{
	return m_stack.empty();
}

State::Ptr StateStack::create_state(States::ID state_id)
{
	auto found = m_factories.find(state_id);
	assert(found != m_factories.end());

	return found->second();
}

void StateStack::apply_pending_changes()
{
	for (PendingChange change : m_pending_list)
	{
		switch (change.action)
		{
			case Push:
			{
				m_stack.push_back(create_state(change.state_id));
			} break;

			case Pop:
			{
				m_stack.pop_back();
			} break;

			case Clear:
			{
				m_stack.clear();
			} break;
		}
	}

	m_pending_list.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::ID state_id)
	:
	action(action),
	state_id(state_id)
{

}