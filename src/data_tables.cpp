#include "data_tables.h"
#include "square.h"


std::vector<EntityData> initialize_entity_data()
{
    std::vector<EntityData> data(Square::TypeCount);

    // Player
    data[Square::Self].quad[0].position = sf::Vector2f({ 0.f, 0.f });
    data[Square::Self].quad[1].position = sf::Vector2f({ 16.f, 0.f });
    data[Square::Self].quad[2].position = sf::Vector2f({ 16.f, 16.f });
    data[Square::Self].quad[3].position = sf::Vector2f({ 0.f, 16.f });
    data[Square::Self].quad[4].position = sf::Vector2f({ 0.f, 0.f });
    data[Square::Self].quad[5].position = sf::Vector2f({ 16.f, 16.f });

    data[Square::Self].quad[0].color = sf::Color::Yellow;
    data[Square::Self].quad[1].color = sf::Color::Yellow;
    data[Square::Self].quad[2].color = sf::Color::Yellow;
    data[Square::Self].quad[3].color = sf::Color::Yellow;
    data[Square::Self].quad[4].color = sf::Color::Yellow;
    data[Square::Self].quad[5].color = sf::Color::Yellow;

    data[Square::Self].hitpoints = 100;
    data[Square::Self].speed = 200.f;

    // Enemy 0
    data[Square::Enemy0].quad[0].position = sf::Vector2f({0.f, 0.f });
    data[Square::Enemy0].quad[1].position = sf::Vector2f({16.f, 0.f });
    data[Square::Enemy0].quad[2].position = sf::Vector2f({16.f, 16.f });
    data[Square::Enemy0].quad[3].position = sf::Vector2f({0.f, 16.f });
    data[Square::Enemy0].quad[4].position = sf::Vector2f({0.f, 0.f });
    data[Square::Enemy0].quad[5].position = sf::Vector2f({16.f, 16.f });

    data[Square::Enemy0].quad[0].color = sf::Color::Red;
    data[Square::Enemy0].quad[1].color = sf::Color::Red;
    data[Square::Enemy0].quad[2].color = sf::Color::Red;
    data[Square::Enemy0].quad[3].color = sf::Color::Red;
    data[Square::Enemy0].quad[4].color = sf::Color::Red;
    data[Square::Enemy0].quad[5].color = sf::Color::Red;

    data[Square::Enemy0].hitpoints = 100;
    data[Square::Enemy0].speed = 200.f;

    return data;
}