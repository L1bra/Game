#pragma once

#include "state.h"
#include "player_controller.h"
#include "utility.h"
#include "sprite_node.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class World
{
public:
    explicit World(sf::RenderTarget& target, FontHolder& fonts);

    void draw();
    void update(sf::Time dt);

    void load_textures();
    void build_scene();

    void adapt_player_position();
    void adapt_player_velocity();
    // TODO:
    CommandQueue& get_command_queue();
private:
    void add_enemy(Square::Type type, float x, float y);
    void add_enemies();
    void spawn_enemies();

private:
    enum Layer
    {
        Background,
        Ground,
        LayerCount
    };

    struct SpawnPoint
    {
        SpawnPoint(Square::Type type, float x, float y)
            :
            type(type),
            x(x),
            y(y)
        {
        }

        Square::Type type;
        float x;
        float y;
    };
private:
    // ldtk::Project& m_ldtk_project;
    // TileMap m_tile_map;

    //PlayerController& m_player_controller;
    Square* m_player_entity;

    sf::RenderTarget& m_target;
    TextureHolder m_textures;
    FontHolder& m_fonts;

    SceneNode m_scene_graph;
    std::array<SceneNode*, Layer::LayerCount> m_scene_layers;
    CommandQueue m_command_queue;

    sf::FloatRect m_world_bounds;
    sf::RectangleShape m_background_shape;
    sf::View m_world_view;
    sf::Vector2f m_spawn_position;
    float m_scroll_speed;

    int m_total_enemies;
    std::vector<SpawnPoint> m_enemy_spawn_points;
    std::vector<Square*> m_active_enemies;
};