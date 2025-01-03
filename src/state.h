#pragma once

#include "window.h"
#include "state_identifier.h"
#include "resource_identifier.h"

#include <LDtkLoader/Project.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

class StateStack;
class Player;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	struct Context
	{
		Context(Window& window, TextureHolder& textures, FontHolder& fonts, Player& player, ldtk::Project& project);

		Window* m_window;
		TextureHolder* m_textures;
		FontHolder* m_fonts;
		Player* m_player;
		ldtk::Project* m_ldtk_project;
	};

public:
	State(StateStack& stack, Context context);
	virtual ~State();

	virtual void draw() = 0;
	virtual bool update(sf::Time dt) = 0;
	virtual bool handle_event(const std::optional<sf::Event> event) = 0;

protected:
	void request_stack_push(States::ID state_id);
	void request_stack_pop();
	void request_state_clear();

	Context get_context() const;
private:
	StateStack* m_stack;
	Context m_context;
};