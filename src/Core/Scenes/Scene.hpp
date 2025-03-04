#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <SFML/Graphics.hpp>

#include "libs/SFMLBoost.hpp"
#include "MacroFlags.hpp"

// interface For scene class
class Scene
{
protected:
    /* data */
    std::vector<sf::Drawable*> m_drawables_objects;
    std::vector<SFMLBoost::ObjectsGroup> Objects_groups;
    sf::Color m_Background_Color = sf::Color(29, 180, 237);
    
    // Return true if it is last iteration
    // if true has been returned removing it from the vector
    std::vector<std::function<bool()>> animations;
public:
    Scene();
    ~Scene();

    /// @brief Runs when scene loaded 
    /// @param Scene_window the main window for rendering
    virtual void Start(std::shared_ptr<sf::RenderWindow> Scene_window);

    /// @brief Runs every frame responsible for the logical part of the frame
    /// @param events_queue queue contains the inputs between frames
    virtual void Frame_update(std::queue<sf::Event> events_queue) = 0;

    /// @brief Runs every frame responsible for the graphical part of the frame
    /// @note Also runs the animations
    virtual void Graphical_update();
    
    /// @brief Runs every frame responsible to render the object into the screen
    /// @attention Also clearing the window
    /// @param Scene_window the main window for rendering
    virtual void Render_objects(std::shared_ptr<sf::RenderWindow> Scene_window);
};
#endif