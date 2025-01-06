#pragma once

#include "state.h"
#include "world.h"
#include "player_controller.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class GameState : public State
{
public:
    GameState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handle_event(const std::optional<sf::Event> event);
private:
    World m_world;
    PlayerController& m_player_controller;
};