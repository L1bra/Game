#pragma once

#include "window.h"
#include "resource_manager.h"
#include "resource_identifier.h"
#include "player_controller.h"
#include "state_stack.h"

#include "title_state.h"
#include "menu_state.h"
#include "settings_state.h"
#include "game_state.h"
#include "pause_state.h"


class Application
{
public:
    Application();
    ~Application();

    bool init();
    void start();
private:
    void input();
    void update(sf::Time et);
    void draw();

    void update_statistic(sf::Time dt);
    void register_states();

    bool is_running() const;
private:
    Window m_window;
    TextureHolder m_textures;
    FontHolder m_fonts;
    PlayerController m_player_controller;

    StateStack m_state_stack;

    // Statistic stuff
    sf::Font m_statistic_font;
    sf::Text m_statistic_text;
    sf::Time m_statistic_update_time;
    std::size_t m_statistic_num_frames;

    static const sf::Time time_per_frame;
};