#include "data_tables.h"
#include "magic.h"


std::vector<EntityData> initialize_entity_data()
{
    std::vector<EntityData> data(GameActor::TypeCount);

    //data[GameActor::Self].hitpoints = 100;
    //data[GameActor::Self].speed = 200.f;
    //data[GameActor::Self].shape.setFillColor(sf::Color::Yellow);

    data[GameActor::Enemy0].hitpoints = 100;
    data[GameActor::Enemy0].speed = 200.f;
    data[GameActor::Enemy0].shape.setSize({16.f, 16.f});
    data[GameActor::Enemy0].shape.setFillColor(sf::Color::Red);

    data[GameActor::Enemy1].hitpoints = 100;
    data[GameActor::Enemy1].speed = 200.f;
    data[GameActor::Enemy1].shape.setSize({ 16.f, 16.f });
    data[GameActor::Enemy1].shape.setFillColor(sf::Color::Blue);

    data[GameActor::Enemy2].hitpoints = 100;
    data[GameActor::Enemy2].speed = 200.f;
    data[GameActor::Enemy2].shape.setSize({ 16.f, 16.f });
    data[GameActor::Enemy2].shape.setFillColor(sf::Color::Magenta);

    return data;
}