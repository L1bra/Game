#include "entity.h"
#include "resource_identifier.h"
#include "resource_manager.h"
#include "text_node.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>


class GameActor : public Entity
{
public:
    enum Type
    {
        Self,
        Enemy0,
        Enemy1,
        Enemy2,
        TypeCount
    };
public:
    GameActor(Type type, const TextureHolder& textures, const FontHolder& fonts);
    ~GameActor();

    virtual unsigned int get_category() const;
    sf::RectangleShape& get_character_sprite();
private:
    virtual void update_current(sf::Time dt) override;
    virtual void draw_current(sf::RenderTarget& target, sf::RenderStates states) const override;

    void update_texts();
public:
    Type m_type;
private:
    // sf::Sprite m_sprite;
    sf::RectangleShape m_shape;

    TextNode* m_health_display;
};
