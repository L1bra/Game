#pragma once

#include "scene_node.h"

class Entity : public SceneNode
{
private:
    sf::Vector2f m_velocity;
private:
    virtual void update_current(sf::Time dt);
public:
    void set_velocity(sf::Vector2f velocity);
    void set_velocity(float vx, float vy);
    sf::Vector2f get_velocity() const;

    void accelerate(sf::Vector2f velocity);
    void accelerate(float vx, float xy);
};