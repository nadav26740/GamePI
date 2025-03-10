#pragma once
#ifndef SCENES_SPLASHSCREEN_HPP
#define SCENES_SPLASHSCREEN_HPP

#define SPLASH_SCREEN_TEXT "Welocme to GamePI"

#include <iostream>
#include <memory>
#include <string>
#include "SFML/Graphics.hpp"

#include "SystemDefines.hpp"

#include "Core/Scenes/SceneManager.hpp"
#include "Core/Scenes/Scene.hpp"
#include "Core/AssetsCacheManager.hpp"
#include "Scenes/MainMenu.hpp"

/// @brief 
/// Fix undefined reference
class SplashScreen : public Scene
{
protected:
    /* data */
    SFMLBoost::ObjectsGroup m_Logo_group;

    std::shared_ptr<SFMLBoost::Object_wrapper> m_logo_sprite_wrapper;
    std::shared_ptr<sf::Sprite> m_logo_sprite;
    
    std::shared_ptr<sf::Text> m_logo_text;

    std::unique_ptr<sf::RectangleShape> m_black_rect;
    std::chrono::steady_clock::time_point m_scene_start_point;

public:
    virtual void Start(std::shared_ptr<sf::RenderWindow> Scene_window);

    /// @brief Runs every frame responsible for the logical part of the frame
    virtual void Frame_update(std::queue<sf::Event> events_queue);

    /// @brief Runs every frame responsible for the graphical part of the frame
    virtual void Graphical_update(std::shared_ptr<sf::RenderWindow> Scene_window);

    virtual void Render_objects(std::shared_ptr<sf::RenderWindow> Scene_window);
    
};
#endif