#include "entity.h"

Entity::Entity(int hitpoints)
    :
    m_hitpoints(hitpoints)
{
}

void Entity::heal(int points)
{
    m_hitpoints += points;
}

void Entity::damage(int points)
{
    m_hitpoints -= points;
}

void Entity::destroy()
{
}

int Entity::get_hitpoints() const
{
    return m_hitpoints;
}

bool Entity::is_destroyed() const
{
    return false;
}

void Entity::update_current(sf::Time dt)
{
    move(m_velocity * dt.asSeconds());
}


void Entity::set_velocity(sf::Vector2f velocity)
{
    m_velocity = velocity;
}

void Entity::set_velocity(float vx, float vy)
{
    m_velocity.x = vx;
    m_velocity.y = vy;
}

sf::Vector2f Entity::get_velocity() const
{
    return m_velocity;
}

void Entity::accelerate(sf::Vector2f velocity)
{
    m_velocity += velocity;
}

void Entity::accelerate(float vx, float vy)
{
    m_velocity.x += vx;
    m_velocity.y += vy;
}