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
    void CenterASprite(sf::Sprite *SpriteToCenter, sf::Window* Window_Referance);
}