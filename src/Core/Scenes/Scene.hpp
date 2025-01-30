#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include <SFML/Graphics.hpp>
#include "SFMLBoost.hpp"

// interface
class Scene
{
protected:
    /* data */
    std::vector<SFMLBoost::ObjectsGroup> Objects_groups;


public:
    Scene();

    /// @brief Runs when scene loaded 
    virtual void Start() = 0;

    /// @brief Runs every frame responsible for the logical part of the frame
    virtual void Frame_update() = 0;

    /// @brief Runs every frame responsible for the render part of the frame
    virtual void Graphical_update(sf::Window window_Handler) = 0;

    virtual ~Scene() = 0;
};