#include "entity.h"
#include "resource_identifier.h"
#include "resource_manager.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>


class PlayerMagic : public Entity
{
private:
    sf::Sprite m_sprite;
    enum Type
    {
        Magic0,
        Magic1,
        Magic2
    };
public:
    Type m_type;
private:
    virtual void draw_current(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    PlayerMagic(const TextureHolder& textures);
    ~PlayerMagic();

    virtual unsigned int get_category() const;
};