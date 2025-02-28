#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "MacroFlags.hpp"

#ifdef DEBUG
    #define BOOSTSFML_HPP_DEBUG
#endif

namespace SFMLBoost 
{
    /// @brief Getting a sprite and a window pointers and centering the sprite that will fit the window
    /// @attention Side effect Changing the origin to the middle
    /// @version 2.5.1 SFML
    /// @param SpriteToCenter Sprite to center
    /// @param Window_Referance Current window referance (The sprite will be center by this window size)
    void CenterASprite(sf::Sprite *SpriteToCenter, const sf::Window* Window_Referance);

    /// @brief Getting a sprite and a window pointers and centering the sprite that will fit the window
    /// @attention Side effect Changing the origin to the middle
    /// @version 2.5.1 SFML
    /// @param TransformableToCenter object to center
    /// @param window_referance Current window referance (The sprite will be center by this window size)
    /// @param object_bounds object bounds (Default 0,0 (point))
    /// @param object_origin The object origin (Default 0,0 top left)
    void CenterATransformable(sf::Transformable *TransformableToCenter, const sf::Window* window_referance, sf::FloatRect object_bounds = sf::FloatRect(), sf::Vector2f object_origin = {0,0});
}