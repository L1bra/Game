#include "magic.h"

#include "data_tables.h"


namespace
{
    const std::vector<EntityData> DataTable = initialize_entity_data();
}


GameActor::GameActor(Type type, const TextureHolder& textures, const FontHolder& fonts)
	:
    Entity(DataTable[type].hitpoints),
    m_type(type),
    m_shape({16.f, 16.f})
{
    m_shape.setFillColor(sf::Color::Yellow);
    sf::FloatRect bounds = m_shape.getLocalBounds();
	m_shape.setOrigin({ bounds.size.x / 2.f, bounds.size.y / 2.f });

    std::unique_ptr<TextNode> health_display = std::make_unique<TextNode>(fonts, "");
    m_health_display = health_display.get();
    this->attach_child(std::move(health_display));
}

GameActor::~GameActor()
{
}

void GameActor::update_current(sf::Time dt)
{
    (this->get_velocity().x || this->get_velocity().y) ? m_shape.setFillColor(sf::Color::Red) : m_shape.setFillColor(sf::Color::Yellow);

    Entity::update_current(dt);

    update_texts();
}

void GameActor::draw_current(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_shape, states);
}

void GameActor::update_texts()
{
    m_health_display->set_string(std::to_string(get_hitpoints()) + "HP");
    m_health_display->setPosition({ 0.f, 20.f });
    //m_health_display->setRotation(-getRotation());
}

sf::RectangleShape& GameActor::get_character_sprite()
{
    return m_shape;
}

unsigned int GameActor::get_category() const
{
     switch (m_type)
     {
        case Self:      return Category::PlayerEntity;
     	case Enemy0:
        case Enemy1:
        case Enemy2:
     	                return Category::EnemyEntity;
        default:        return Category::None;
     }

    return Category::PlayerEntity;
}