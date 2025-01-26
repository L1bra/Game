#pragma once

#include "resource_identifier.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <vector>
#include <functional>


struct EntityData
{
    int hitpoints = 0;
    float speed = 0.0f;
    sf::VertexArray quad{ sf::PrimitiveType::Triangles, 6 };
};

std::vector<EntityData>      initialize_entity_data();