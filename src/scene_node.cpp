#include "scene_node.h"

#include <SFML/Graphics/RenderStates.hpp>

SceneNode::SceneNode()
	:
	m_children(),
	m_parent(nullptr)
{

}


void SceneNode::attach_child(Ptr child)
{
	child->m_parent = this;
	m_children.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detach_child(const SceneNode& node)
{
	auto found = std::find_if(m_children.begin(), m_children.end(), [&](Ptr& p) { return p.get() == &node; });
	assert(found != m_children.end());

	Ptr result = std::move(*found);
	result->m_parent = nullptr;
	m_children.erase(found);
	return result;
}

void SceneNode::update(sf::Time dt)
{
	update_current(dt);
	update_children(dt);
}

void SceneNode::update_current(sf::Time dt)
{
	//
}

void SceneNode::update_children(sf::Time dt)
{
	for (auto& child : m_children)
		child->update(dt);
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply transform of current node
	states.transform *= getTransform();

	// draw node and children with changed transform
	draw_current(target, states);
	draw_children(target, states);
}

void SceneNode::draw_current(sf::RenderTarget& target, sf::RenderStates states) const
{
	// 
}

void SceneNode::draw_children(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& child : m_children)
		child->draw(target, states);
}

sf::Vector2f SceneNode::get_world_position() const
{
	return get_world_transform() * sf::Vector2f();
}

sf::Transform SceneNode::get_world_transform() const
{
	sf::Transform transform = sf::Transform::Identity;
	for (const SceneNode* node = this; node != nullptr; node = node->m_parent)
		transform = node->getTransform() * transform;

	return transform;
}

void SceneNode::on_command(const Command& command, sf::Time dt)
{
	// Command current node if category matched
	if (command.category & get_category())
		command.action(*this, dt);

	for (auto& child : m_children)
		child->on_command(command, dt);
}

// Return Scene category by default
unsigned int SceneNode::get_category() const
{
	return Category::Scene;
}