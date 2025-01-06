#include "world.h"
#include <cmath>


World::World(sf::RenderTarget& target, FontHolder& fonts)
	:
	m_target(target),
    // m_ldtk_project(*context.m_ldtk_project),
    // m_tile_map(),
	//m_player_controller(*context.m_player_controller),
	m_player_entity(nullptr),
	//m_window(*context.m_window),
	m_textures(),
	m_fonts(fonts),
	m_scene_graph(),
	m_scene_layers(),
	m_background_shape({2000.f, 2000.f}),
	m_world_view(sf::Vector2f{ 0.f, 0.f }, sf::Vector2f{ 640.f, 360.f }),
	m_world_bounds({ 0.f, 0.f }, { m_world_view.getSize().x, 2000.f }), // TODO
    m_spawn_position({ m_background_shape.getSize().x / 2.f, m_background_shape.getSize().y / 2.f})
{
	load_textures();
	build_scene();

	m_world_view.setCenter(m_spawn_position);
}

void  World::update(sf::Time dt)
{
	// Scroll the world
	//m_world_view.move({ 0.f, m_scroll_speed * dt.asSeconds() });
    m_player_entity->set_velocity(0.f, 0.f);

	//m_player_controller.handle_realtime_input(m_command_queue);

	// Forward commands to the scene graph
	while (!m_command_queue.is_empty())
	{
		m_scene_graph.on_command(m_command_queue.pop(), dt);
	}

	adapt_player_velocity();

	// Apply movement
	m_scene_graph.update(dt);
    m_world_view.setCenter(m_player_entity->getPosition());
    //adapt_player_position();
}

void World::draw()
{
	//m_window.set_view(m_world_view);
	// Window class internally calls SceneNode::draw() function
	m_target.draw(m_background_shape);
	m_target.draw(m_scene_graph);
	//m_window.draw(m_tile_map.get_layer("Terrain"));
}

void World::load_textures()
{
    // m_textures.load(Textures::WorldBackground, "assets/background/background0.png");
    // m_textures.load(Textures::MAGIC0, "assets/sprites/magic.png");
    // m_textures.load(Textures::ENEMY, "assets/sprites/enemy.png");
}

void World::build_scene()
{
    // const auto& world = m_ldtk_project.getWorld();
    // const auto& level = world.getLevel("World_Level_0");
    // const auto& layer = level.getLayer("Terrain");
	//const auto& tiles_vector = layer.allTiles();

    // const auto& layers = layer.getTileset();

    // TileMap::path = m_ldtk_project.getFilePath().directory();
    // m_tile_map.set_level(level);

    m_background_shape.setPosition({0.f, 0.f});
	m_background_shape.setFillColor(sf::Color::Black);

    for (std::size_t i = 0; i < Layer::LayerCount; ++i)
    {
    	SceneNode::pNode layer = std::make_unique<SceneNode>();
    	m_scene_layers[i] = layer.get();
    	m_scene_graph.attach_child(std::move(layer));
    }

    // sf::Texture& texture = m_textures.get(Textures::WorldBackground);
    // sf::IntRect texture_rect(m_world_bounds);
    // texture.setRepeated(true);

	// Add background sprite
    // std::unique_ptr<SpriteNode> background_sprite(new SpriteNode(texture, texture_rect));
    // background_sprite->setPosition(m_world_bounds.position);
    // m_scene_layers[Layer::Background]->attach_child(std::move(background_sprite));

	// Add player
    std::unique_ptr<GameActor> magic = std::make_unique<GameActor>(GameActor::Type::Self, m_textures, m_fonts);
    m_player_entity = magic.get();
    m_player_entity->setPosition(m_spawn_position);
    m_player_entity->set_velocity(100.f, 100.f);
    m_scene_layers[Layer::Ground]->attach_child(std::move(magic));
}

CommandQueue& World::get_command_queue()
{
	return m_command_queue;
}

void World::adapt_player_position()
{
	// Keep player's position inside the screen bounds, at least border_distance units from the border
	sf::FloatRect view_bounds(m_world_view.getCenter() - m_world_view.getSize() / 2.f, m_world_view.getSize());
	const float border_distance = 40.f;

	sf::Vector2f position = m_player_entity->getPosition();
	position.x = std::max(position.x, view_bounds.position.x + border_distance);
	position.x = std::min(position.x, view_bounds.position.x + view_bounds.size.x - border_distance);
	position.y = std::max(position.y, view_bounds.position.y + border_distance);
	position.y = std::min(position.y, view_bounds.position.y + view_bounds.size.y - border_distance);
	m_player_entity->setPosition(position);
}

void World::adapt_player_velocity()
{
	sf::Vector2f velocity = m_player_entity->get_velocity();

	// if moving diagonally, reduce velocity (to have the same velocity)
	if (velocity.x != 0.f && velocity.y != 0.f)
		m_player_entity->set_velocity(velocity / std::sqrt(2.f));

	// add scrolling velocity
	m_player_entity->accelerate(0.f, 0.f);
}