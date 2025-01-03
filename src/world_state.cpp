#include "world_state.h"


WorldState::WorldState(StateStack& stack, Context context)
	:
	State(stack, context),
	m_player(*context.m_player),
	m_window(*context.m_window),
	m_ldtk_project(*context.m_ldtk_project),
	m_world_view(sf::Vector2f{ 0.f, 0.f }, sf::Vector2f{ 640.f, 360.f }),
	m_textures(),
	m_scene_graph(),
	m_scene_layers(),
	m_world_bounds({ 0.f, 0.f }, { m_world_view.getSize().x, 2000.f }), // TODO
	m_spawn_position({ gui::p2px(6.f, m_window.get_gfx().resolution),
		gui::p2py(70.f, m_window.get_gfx().resolution) }),
	//m_scroll_speed(-50.f),
	m_player_entity(nullptr),
	m_tile_map()
{
	load_textures();
	build_scene();

	m_world_view.setCenter(m_spawn_position);
}

bool WorldState::update(sf::Time dt)
{
	// Scroll the world
	//m_world_view.move(0.f, m_scroll_speed * dt.asSeconds());
	m_player_entity->set_velocity(0.f, 0.f);

	m_player.handle_realtime_input(m_command_queue);

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

	return true;
}

bool WorldState::handle_event(const std::optional<sf::Event> event)
{
	// game input handling
	m_player.handle_event(event, m_command_queue);

	// Escape pressed, trigger the pause screen
	if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
		request_stack_push(States::Pause);

	return true;
}

void WorldState::draw()
{
	m_window.set_view(m_world_view);
	// Window class internally calls SceneNode::draw() function
	m_window.draw(m_scene_graph);
	m_window.draw(m_tile_map.get_layer("Terrain"));
}

void WorldState::load_textures()
{
	m_textures.load(Textures::WorldBackground, "assets/background/background0.png");
	m_textures.load(Textures::MAGIC0, "assets/sprites/magic0.png");
	m_textures.load(Textures::ENEMY, "assets/sprites/enemy.png");
}

void WorldState::build_scene()
{
	// https://github.com/Madour/LDtk-SFML-Game
	const auto& world = m_ldtk_project.getWorld();
	const auto& level = world.getLevel("Level_0");
	const auto& layer = level.getLayer("Terrain");
	//const auto& tiles_vector = layer.allTiles();

	const auto& layers = layer.getTileset();

	TileMap::path = m_ldtk_project.getFilePath().directory();
	m_tile_map.set_level(level);

	for (std::size_t i = 0; i < Layer::LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		m_scene_layers[i] = layer.get();
		m_scene_graph.attach_child(std::move(layer));
	}

	sf::Texture& texture = m_textures.get(Textures::WorldBackground);
	sf::IntRect texture_rect(m_world_bounds);
	texture.setRepeated(true);

	// Add background sprite
	std::unique_ptr<SpriteNode> background_sprite(new SpriteNode(texture, texture_rect));
	background_sprite->setPosition(m_world_bounds.position);
	m_scene_layers[Layer::Background]->attach_child(std::move(background_sprite));

	// Add player
	std::unique_ptr<PlayerMagic> magic(new PlayerMagic(m_textures));
	m_player_entity = magic.get();
	m_player_entity->setPosition(m_spawn_position);
	m_player_entity->set_velocity(100.f, 100.f);
	m_scene_layers[Layer::Ground]->attach_child(std::move(magic));
}

CommandQueue& WorldState::get_command_queue()
{
	return m_command_queue;
}

void WorldState::adapt_player_position()
{
	// Keep player's position inside the screen bounds, at least border_distance units from the border
	sf::FloatRect view_bounds(m_world_view.getCenter() - m_world_view.getSize() / 2.f, m_world_view.getSize());
	const float border_distance = 40.f;

	sf::Vector2f position = m_player_entity->getPosition();
	//position.x = std::max(position.x, view_bounds.left + border_distance);
	//position.x = std::min(position.x, view_bounds.left + view_bounds.width - border_distance);
	//position.y = std::max(position.y, view_bounds.top + border_distance);
	//position.y = std::min(position.y, view_bounds.top + view_bounds.height - border_distance);
	m_player_entity->setPosition(position);
}

void WorldState::adapt_player_velocity()
{
	sf::Vector2f velocity = m_player_entity->get_velocity();

	// if moving diagonally, reduce velocity (to have the same velocity)
	if (velocity.x != 0.f && velocity.y != 0.f)
		m_player_entity->set_velocity(velocity / std::sqrt(2.f));

	// add scrolling velocity
	m_player_entity->accelerate(0.f, 0.f);
}