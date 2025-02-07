#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include <SFML/Graphics.hpp>
#include "libs/SFMLBoost.hpp"

// interface
class Scene
{
protected:
    /* data */
    std::vector<SFMLBoost::ObjectsGroup> Objects_groups;
    sf::RenderWindow* Scene_window;

public:
    Scene();

    /// @brief Runs when scene loaded 
    virtual void Start(sf::RenderWindow* Scene_window) = 0;

    /// @brief Runs every frame responsible for the logical part of the frame
    virtual void Frame_update() = 0;

    /// @brief Runs every frame responsible for the render part of the frame
    virtual void Graphical_update();

    virtual ~Scene() = 0;
};