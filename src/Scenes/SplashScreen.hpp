#pragma once
#ifndef SCENES_SPLASHSCREEN_HPP
#define SCENES_SPLASHSCREEN_HPP

#define LOGO_ASSET_NAME "GamePI_Icon"

#include <iostream>
#include <memory>
#include <string>
#include "SFML/Graphics.hpp"

#include "Core/Scenes/Scene.hpp"
#include "Core/AssetsCacheManager.hpp"

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

public:
    virtual void Start(std::shared_ptr<sf::RenderWindow> Scene_window);

    /// @brief Runs every frame responsible for the logical part of the frame
    virtual void Frame_update();

    /// @brief Runs every frame responsible for the graphical part of the frame
    virtual void Graphical_update();

    virtual void Render_objects(std::shared_ptr<sf::RenderWindow> Scene_window);
    
};
#endif