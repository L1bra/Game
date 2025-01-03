#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

#include <SFML/Graphics.hpp>

enum class Options
{
    unknown = -1,
    title,
    resolution_height,
    resolution_width,
    fullscreen,
    vsync,
    framerate
};


static const std::map<std::string, Options> opt_strings
{
    {"title", Options::title},
    {"resolution_height", Options::resolution_height},
    {"resolution_width", Options::resolution_width},
    {"fullscreen", Options::fullscreen},
    {"vsync", Options::vsync},
    {"framerate", Options::framerate},
};


class GFX
{
private:
    Options resolve(const std::string& input);
public:
    GFX();
    ~GFX();

    std::string title;
    sf::VideoMode resolution;
    std::vector<sf::VideoMode> vms;

    bool fullscreen;
    bool vsync;

    unsigned int framerate;

    bool save(const std::string& path);
    bool load(const std::string& path);
};