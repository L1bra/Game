#include "world.h"

#include <cmath>
#include <cstdlib>

World::World(sf::RenderTarget& target, FontHolder& fonts)
	:
	m_target(target),
	m_player_entity(nullptr),
	m_textures(),
	m_fonts(fonts),
	m_scene_graph(),
	m_scene_layers(),
	m_background_shape({10000.f, 10000.f}),
	m_world_view({ 0.f, 0.f }, { static_cast<float>(m_target.getSize().x), static_cast<float>(m_target.getSize().y) }), // 640 360
	m_world_bounds({ 0.f, 0.f }, { m_world_view.getSize().x, 2000.f }),
    m_spawn_position({ m_background_shape.getSize().x / 2.f, m_background_shape.getSize().y / 2.f}),
	m_total_enemies(100),
	m_enemy_spawn_points(),
	m_active_enemies()
{
	m_active_enemies.reserve(m_total_enemies);
	m_enemy_spawn_points.reserve(m_total_enemies);

	load_textures();
	build_scene();

	m_world_view.setCenter(m_spawn_position);

	srand(static_cast<unsigned>(time(0))); // Seed for randomness
}

void  World::update(sf::Time dt)
{
    m_player_entity->set_velocity(0.f, 0.f);

	//m_player_controller.handle_realtime_input(m_command_queue);

	// Forward commands to the scene graph
	while (!m_command_queue.is_empty())
	{
		m_scene_graph.on_command(m_command_queue.pop(), dt);
	}

	adapt_player_velocity();

	spawn_enemies();

	// Apply movement
	m_scene_graph.update(dt);
    m_world_view.setCenter(m_player_entity->getPosition());
    //adapt_player_position();
}

void World::draw()
{
	m_target.setView(m_world_view);
	m_target.draw(m_background_shape);
	// Window class internally calls SceneNode::draw() function
	m_target.draw(m_scene_graph);
}

void World::load_textures()
{
    // m_textures.load(Textures::WorldBackground, "assets/background/background0.png");
    // m_textures.load(Textures::MAGIC0, "assets/sprites/magic.png");
    // m_textures.load(Textures::ENEMY, "assets/sprites/enemy.png");
}

void World::build_scene()
{
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
    std::unique_ptr<Square> magic = std::make_unique<Square>(Square::Type::Self, m_textures, m_fonts, true);
    m_player_entity = magic.get();
    m_player_entity->setPosition(m_spawn_position);
    m_player_entity->set_velocity(100.f, 100.f);
    m_scene_layers[Layer::Ground]->attach_child(std::move(magic));
	
	add_enemies();
}

CommandQueue& World::get_command_queue()
{
	return m_command_queue;
}

void World::add_enemy(Square::Type type, float rel_x, float rel_y)
{
	SpawnPoint point{ type, m_spawn_position.x + rel_x, m_spawn_position.y + rel_y };
	m_enemy_spawn_points.push_back(point);
}

void World::add_enemies()
{
	// TODO: replace rand with c++ random	
	for (int i = 1; i < m_total_enemies; i++)
	{
		float offset_x = (rand() % 2000) - 1000;
		float offset_y = (rand() % 2000) - 1000;
		add_enemy(Square::Type::Enemy0, offset_x, offset_y);
	}
}

void World::spawn_enemies()
{
	while (!m_enemy_spawn_points.empty())
	{
		SpawnPoint point = m_enemy_spawn_points.back();

		std::unique_ptr<Square> enemy = std::make_unique<Square>(point.type, m_textures, m_fonts);
		enemy->setPosition({ point.x, point.y });
		//enemy->setRotation(180.f);

		m_scene_layers[Layer::Ground]->attach_child(std::move(enemy));

		m_enemy_spawn_points.pop_back();
	}
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