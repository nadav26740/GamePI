#pragma once
#ifndef GAMESHOWCASE_HPP
#define GAMESHOWCASE_HPP

#include <iostream>
#include <memory>
#include "Core/Scenes/Scene.hpp"
#include "libs/SFMLBoost.hpp"
#include "Core/Scenes/SceneManager.hpp"
#include "Core/AssetsCacheManager.hpp"

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

    const float cm_cover_height = 200;
    const float cm_cover_width = 200;

    // TODO: change current game shown 

public:
    virtual void Start(std::shared_ptr<sf::RenderWindow> Scene_window);

    /// @brief Runs every frame responsible for the logical part of the frame
    virtual void Frame_update(std::queue<sf::Event> events_queue);

    /// @brief Runs every frame responsible for the graphical part of the frame
    virtual void Graphical_update(std::shared_ptr<sf::RenderWindow> Scene_window);

    virtual void Render_objects(std::shared_ptr<sf::RenderWindow> Scene_window);
    
    
};

#endif