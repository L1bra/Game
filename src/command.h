#pragma once

#include "category.h"

#include <SFML/System/Time.hpp>

#include <functional>
#include <cassert>


class SceneNode;

struct Command
{
public:
	std::function<void(SceneNode&, sf::Time)> action;
	unsigned int category;
public:
	Command();
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derived_action(Function fn)
{
	return [=] (SceneNode& node, sf::Time dt)
	{
		// Check if cast is safe
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		// Downcast node and invoke function on it
		fn(static_cast<GameObject&>(node), dt);
	};
}