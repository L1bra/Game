#pragma once

#include "scene_node.h"

class Entity : public SceneNode
{
public:
    explicit Entity(int hitpoints);

    void heal(int points);
    void damage(int points);
    void destroy();

    int get_hitpoints() const;
    virtual bool is_destroyed() const;

    void set_velocity(sf::Vector2f velocity);
    void set_velocity(float vx, float vy);
    sf::Vector2f get_velocity() const;

    void accelerate(sf::Vector2f velocity);
    void accelerate(float vx, float xy);
protected:
    virtual void update_current(sf::Time dt) override;
private:
    sf::Vector2f m_velocity;
    int m_hitpoints;
};