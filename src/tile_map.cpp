#include "tile_map.h"

TileMap::Textures& TileMap::Textures::instance()
{
	static Textures instance;
	return instance;
}

sf::Texture& TileMap::Textures::get(const std::string& name)
{
	auto& data = instance().data;
	if (data.count(name) == 0)
		data[name].loadFromFile(TileMap::path + name);

	return instance().data.at(name);
}

TileMap::Layer::Layer(const ldtk::Layer& layer, sf::RenderTexture& render_texture)
	:
	m_render_texture(render_texture)
{
	m_tileset_texture = &Textures::get(layer.getTileset().path);
	m_vertex_array.resize(layer.allTiles().size() * 4);
	m_vertex_array.setPrimitiveType(sf::PrimitiveType::Triangles);

	int i = 0;
	for (const auto& tile : layer.allTiles())
	{
		for (int j = 0; j < 4; ++j)
		{
			auto vertices = tile.getVertices();
			m_vertex_array[i * 4 + j].position.x = vertices[j].pos.x;
			m_vertex_array[i * 4 + j].position.y = vertices[j].pos.y;
			m_vertex_array[i * 4 + j].texCoords.x = static_cast<float>(vertices[j].tex.x);
			m_vertex_array[i * 4 + j].texCoords.y = static_cast<float>(vertices[j].tex.y);
		}
		i++;
	}
}

void TileMap::Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = m_tileset_texture;
	m_render_texture.clear(sf::Color::Transparent);
	m_render_texture.draw(m_vertex_array, states);
	m_render_texture.display();
	target.draw(sf::Sprite(m_render_texture.getTexture()), states);
}

std::string TileMap::path;

TileMap::TileMap(const ldtk::Level& level)
{
	load(level);
}

// ???
void TileMap::set_level(const ldtk::Level& level)
{
	load(level);
}

void TileMap::load(const ldtk::Level& level)
{
	m_layers.clear();
	for (const auto& layer : level.allLayers())
	{
		m_layers.insert({ layer.getName(), {layer, m_render_texture} });
	}
	//m_render_texture.resize({ level.size.x, level.size.y });
}

const TileMap::Layer& TileMap::get_layer(const std::string& name) const
{
	return m_layers.at(name);
}

const std::size_t TileMap::get_layers_size() const
{
	return m_layers.size();
}