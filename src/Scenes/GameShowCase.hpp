#pragma once
#ifndef GAMESHOWCASE_HPP
#define GAMESHOWCASE_HPP

#include <iostream>
#include <memory>
#include "Core/Scenes/Scene.hpp"
#include "libs/SFMLBoost.hpp"
#include "Core/Scenes/SceneManager.hpp"
#include "Core/AssetsCacheManager.hpp"

#define LIST_NAME_SIZE_ON_SCREEN 5
#define LIST_GAP_FROM_LEFT 20
#define LIST_GAP_FROM_TOP 40
#define LIST_GAP_FROM_BOTTOM 40


class GameShowCase : public Scene
{
private:
    /* data */
    std::shared_ptr<sf::Text> m_button_text; 
    std::shared_ptr<sf::RectangleShape> m_button_background;
    SFMLBoost::ObjectsGroup m_button_group;

    sf::Sprite m_img_showcase;
    sf::Texture m_showcase_texture;
    std::shared_ptr<sf::Text> m_Game_name_text;
    std::string m_Game_name;

    const float cm_cover_height = 400;
    const float cm_cover_width = 400;
    const sf::Color cm_Selected_color = sf::Color(234, 208, 92);
    const sf::Color cm_text_color = sf::Color(255, 255, 255);
    
    const float cm_font_size = 32;
    const SFMLBoost::POSITION cm_list_Start_position = SFMLBoost::POSITION::TOP_LEFT;
    std::vector<std::string> m_Games_names;
    std::vector<sf::Text> m_names_list_text;

    // TODO: change current game shown 
    void AddGamesList(std::shared_ptr<sf::RenderWindow> Scene_window);

public:
    virtual void Start(std::shared_ptr<sf::RenderWindow> Scene_window);

    /// @brief Runs every frame responsible for the logical part of the frame
    virtual void Frame_update(std::queue<sf::Event> events_queue);

    /// @brief Runs every frame responsible for the graphical part of the frame
    virtual void Graphical_update(std::shared_ptr<sf::RenderWindow> Scene_window);

    virtual void Render_objects(std::shared_ptr<sf::RenderWindow> Scene_window);
    
    
};

#endif