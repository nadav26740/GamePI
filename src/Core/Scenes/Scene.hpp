#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "libs/SFMLBoost.hpp"

// interface For scene class
class Scene
{
protected:
    /* data */
    std::vector<SFMLBoost::ObjectsGroup> Objects_groups;
    sf::RenderWindow* m_Scene_window;

public:
    Scene();

    /// @brief Runs when scene loaded 
    virtual void Start(sf::RenderWindow* Scene_window);

    /// @brief Runs every frame responsible for the logical part of the frame
    virtual void Frame_update() = 0;

    /// @brief Runs every frame responsible for the graphical part of the frame
    virtual void Graphical_update() = 0;
    
    /// @brief Runs every frame responsible to render the object into the screen
    virtual void Render_objects();
};
#endif