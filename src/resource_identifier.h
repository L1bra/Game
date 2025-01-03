#pragma once

// Forward declaration of SFML types
namespace sf
{
	class Texture;
    class Font;
}

namespace Textures
{
	enum ID
	{
        // Tilesets
        Tileset,

        // background (temp)
        TitleScreen,
        MainMenuBackground,
        WorldBackground,
        LocalBackground,
        BattleBackground,

        // entities
        MAGIC0,
        MAGIC1,
        MAGIC2,
        ENEMY,

        // button
        ButtonNormal,
        ButtonSelected,
        ButtonPressed
	};
}

namespace Fonts
{
    enum ID
    {
        Main,
    };
}

// Forward declaration and few typedefs
template<typename Resource, typename Identifier>
class ResourceManager;

typedef ResourceManager<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceManager<sf::Font, Fonts::ID> FontHolder;