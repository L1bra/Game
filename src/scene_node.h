#pragma once

#include "category.h"
#include "command.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <memory>
#include <vector>
#include <cassert>


class SceneNode : public sf::Transformable, public sf::Drawable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;
private:
	std::vector<Ptr> m_children;
	SceneNode* m_parent;
private:
	virtual void update_current(sf::Time dt);
	void update_children(sf::Time dt);
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void draw_current(sf::RenderTarget& target, sf::RenderStates states) const;
	void draw_children(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	SceneNode();

	void attach_child(Ptr child);
	Ptr detach_child(const SceneNode& node);

	void update(sf::Time dt);

	sf::Vector2f get_world_position() const;
	sf::Transform get_world_transform() const;

	void on_command(const Command& command, sf::Time dt);
	virtual unsigned int get_category() const;
};