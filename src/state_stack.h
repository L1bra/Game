#pragma once

#include "state.h"
#include "state_identifier.h"
#include "resource_identifier.h"

#include <SFML/System/Time.hpp>

#include <vector>
#include <utility>
#include <functional>
#include <map>


class StateStack
{
public:
	enum Action
	{
		Push,
		Pop,
		Clear
	};

public:
	explicit StateStack(State::Context context);

	template<typename T>
	void register_state(States::ID state_id);

	void update(sf::Time dt);
	void draw();
	void handle_event(const std::optional<sf::Event> event); // sf::Event

	void push_state(States::ID state_id);
	void pop_state();
	void clear_states();

	bool is_empty() const;
private:
	State::pState create_state(States::ID state_id);
	void apply_pending_changes();
private:
	struct PendingChange
	{
		explicit PendingChange(Action action, States::ID state_id = States::None);

		Action action;
		States::ID state_id;
	};

private:
	std::vector<State::pState> m_stack;
	std::vector<PendingChange> m_pending_list;

	State::Context m_context;
	std::map<States::ID, std::function<State::pState()>> m_factories;
};


template<typename T>
void StateStack::register_state(States::ID state_id)
{
	m_factories[state_id] = [this]()
	{
		return State::pState(new T(*this, m_context));
	};
}