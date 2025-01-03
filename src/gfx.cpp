#include "gfx.h"


GFX::GFX()
    :
    title("Title"),
    resolution(sf::VideoMode::getDesktopMode()),
    vms(sf::VideoMode::getFullscreenModes()),
    fullscreen(false),
    vsync(false),
    framerate(60)
{
}

GFX::~GFX()
{
}

Options GFX::resolve(const std::string& input)
{
    auto it = opt_strings.find(input);
    if (it != opt_strings.end())
        return it->second;

    return Options::unknown;
}


bool GFX::save(const std::string& path)
{
    std::ofstream ofs(path);
    if (!ofs)
    {
        std::cout << "Unable to open file: " << path << std::endl;
        return false;
    }

    ofs << "title=" << title << std::endl;
    ofs << "resolution_width=" << resolution.size.x << std::endl;
    ofs << "resolution_height=" << resolution.size.y << std::endl;
    ofs << "fullscreen=" << fullscreen << std::endl;
    ofs << "vsync=" << vsync << std::endl;
    ofs << "framerate=" << framerate << std::endl;

    ofs.close();

    return true;
}


bool GFX::load(const std::string& path)
{
    std::ifstream ifs(path);
    if (!ifs)
    {
        std::cout << "Unable to open file: " << path << std::endl;
        return false;
    }

    std::string del = "=";
    std::string tmp = "";
    std::string token = "";

    while (std::getline(ifs, tmp))
    {
        token = tmp.substr(0, tmp.find(del));
        switch (resolve(token))
        {
        case Options::title:
        {
            token = tmp.substr(tmp.find(del) + 1);
            title = token;
        } break;

        case Options::resolution_width:
        {
            token = tmp.substr(tmp.find(del) + 1);
            resolution.size.x = std::stoi(token);
        } break;

        case Options::resolution_height:
        {
            token = tmp.substr(tmp.find(del) + 1);
            resolution.size.y = std::stoi(token);
        } break;

        case Options::fullscreen:
        {
            token = tmp.substr(tmp.find(del) + 1);
            fullscreen = std::stoi(token);
        } break;

        case Options::vsync:
        {
            token = tmp.substr(tmp.find(del) + 1);
            vsync = std::stoi(token);
        } break;

        case Options::framerate:
        {
            token = tmp.substr(tmp.find(del) + 1);
            framerate = std::stoi(token);
        } break;

        default:
        {
            std::cout << "Unable to parse: " << token << std::endl;
        }
        }
    }

    return true;
}