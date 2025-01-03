#pragma once

#include "scene_node.h"

#include <SFML/Graphics.hpp>
#include <LDtkLoader/Level.hpp>

#include <vector>
#include <map>


class TileMap
{
public:
	class Textures
	{
	private:
		Textures() = default;
		std::map<std::string, sf::Texture> data;
		static Textures& instance();
	public:
		Textures(const Textures&) = delete;
		static sf::Texture& get(const std::string& name);
	};

	class Layer : public sf::Drawable
	{
	private:
		friend TileMap;
		Layer(const ldtk::Layer& layer, sf::RenderTexture& render_texture);
		
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	private:
		sf::Texture* m_tileset_texture;
		sf::RenderTexture& m_render_texture;
		sf::VertexArray m_vertex_array;
	};
public:
	TileMap() = default;
	explicit TileMap(const ldtk::Level& level);
	
	void load(const ldtk::Level& level);
	void set_level(const ldtk::Level& level);
	const Layer& get_layer(const std::string& name) const;
	const std::size_t get_layers_size() const;
public:
	static std::string path;
private:
	mutable sf::RenderTexture m_render_texture;
	std::map<std::string, Layer> m_layers;
};