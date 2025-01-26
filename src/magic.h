#include "entity.h"
#include "resource_identifier.h"
#include "resource_manager.h"
#include "text_node.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>


class Square : public Entity
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
    Square(Type type, const TextureHolder& textures, const FontHolder& fonts, bool is_player = false);
    ~Square();

    virtual unsigned int get_category() const;

    virtual void update_current(sf::Time dt) override;
    virtual void draw_current(sf::RenderTarget& target, sf::RenderStates states) const override;

    void update_texts();
public:
    Type m_type;
private:
    sf::VertexArray m_vertices;
    TextNode* m_health_display;

    bool is_player = false;
};
