#include "square.h"

#include "data_tables.h"


namespace
{
    const std::vector<EntityData> DataTable = initialize_entity_data();
}


Square::Square(Type type, const TextureHolder& textures, const FontHolder& fonts, bool is_player)
	:
    Entity(DataTable[type].hitpoints),
    m_type(type),
    m_vertices(DataTable[type].quad),
    is_player(is_player)
{
    std::unique_ptr<TextNode> health_display = std::make_unique<TextNode>(fonts, "");
    m_health_display = health_display.get();
    this->attach_child(std::move(health_display));
}

Square::~Square()
{
}

void Square::update_current(sf::Time dt)
{
    Entity::update_current(dt);

    if (!is_player) return;

    if (this->get_velocity().x || this->get_velocity().y)
    {
        m_vertices[0].color = sf::Color::Red;
        m_vertices[1].color = sf::Color::Red;
        m_vertices[2].color = sf::Color::Red;
        m_vertices[3].color = sf::Color::Red;
        m_vertices[4].color = sf::Color::Red;
        m_vertices[5].color = sf::Color::Red;
    }
    else
    {
        m_vertices[0].color = sf::Color::Yellow;
        m_vertices[1].color = sf::Color::Yellow;
        m_vertices[2].color = sf::Color::Yellow;
        m_vertices[3].color = sf::Color::Yellow;
        m_vertices[4].color = sf::Color::Yellow;
        m_vertices[5].color = sf::Color::Yellow;
    }
        
    update_texts();
}

void Square::draw_current(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_vertices, states);
}

void Square::update_texts()
{
    m_health_display->set_string(std::to_string(get_hitpoints()) + "HP");
    m_health_display->setPosition({ 7.f, 15.f });
    //m_health_display->setRotation(-getRotation());
}


unsigned int Square::get_category() const
{
     switch (m_type)
     {
        case Self:      return Category::PlayerEntity;
     	case Enemy0:
     	                return Category::EnemyEntity;
        default:        return Category::None;
     }

    return Category::PlayerEntity;
}