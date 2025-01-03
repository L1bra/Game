#include "entity.h"


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