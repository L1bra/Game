#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <map>  // unordered ?
#include <assert.h>

template<typename Resource, typename Identifier>
class ResourceManager
{
private:
    std::map<Identifier, std::unique_ptr<Resource>> m_resource_map;
public:
    Resource& load(Identifier id, const std::string& filename);

    // idk why but SFML devs renamed function from sf::Font::loadFromFile to sf::Font::openFromFile...
    Resource& loadFont(Identifier id, const std::string& filename);

    // sf::Shader
    template<typename Parameter>
    Resource& load(Identifier id, const std::string& filename, const Parameter& parameter);

    Resource& get(Identifier id);
    const Resource& get(Identifier id) const;
};


template<typename Resource, typename Identifier>
Resource& ResourceManager<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(filename))
        throw std::runtime_error("ResourceManager::load - Failed to load: " + filename);

    auto inserted = m_resource_map.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);

    return this->get(id);
}

template<typename Resource, typename Identifier>
Resource& ResourceManager<Resource, Identifier>::loadFont(Identifier id, const std::string& filename)
{
    std::unique_ptr<sf::Font> font = std::make_unique<sf::Font>();
    if(!font->openFromFile(filename))
        throw std::runtime_error("ResourceManager::loadFront - Failed to load: " + filename);

    auto inserted = m_resource_map.insert(std::make_pair(id, std::move(font)));
    assert(inserted.second);

    return this->get(id);
}

template<typename Resource, typename Identifier>
template<typename Parameter>
Resource& ResourceManager<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& parameter)
{
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(filename, parameter))
        throw std::runtime_error("ResourceManager::load - Failed to load: " + filename);

    auto inserted = m_resource_map.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);

    return this->get(id);
}

template<typename Resource, typename Identifier>
Resource& ResourceManager<Resource, Identifier>::get(Identifier id)
{
    auto found = m_resource_map.find(id);
    assert(found != m_resource_map.end());

    return *found->second;
}

template<typename Resource, typename Identifier>
const Resource& ResourceManager<Resource, Identifier>::get(Identifier id) const
{
    auto found = m_resource_map.find(id);
    assert(found != m_resource_map.end());

    return *found->second;
}