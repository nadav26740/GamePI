#pragma once
#ifndef BOOSTSFML_HPP
#define BOOSTSFML_HPP

#define BOOSTSFML_SFML_VER_SUPPORT_2_5_1

#include <iostream>
#include <SFML/Graphics.hpp>
#include "MacroFlags.hpp"

#ifdef DEBUG
    #define BOOSTSFML_HPP_DEBUG
#endif

namespace SFMLBoost 
{
    enum POSITION 
    {
        TOP_LEFT,    TOP_CENTER,     TOP_RIGHT,
        CENTER_LEFT, CENTER,        CENTER_RIGHT,
        BOTTOM_LEFT, BOTTOM_CENTER, BOTTOM_RIGHT
    };

    /// @brief Getting a sprite and a window pointers and centering the sprite that will fit the window
    /// @attention Side effect Changing the origin to the middle
    /// @version 2.5.1 SFML
    /// @param SpriteToCenter Sprite to center
    /// @param Window_Referance Current window referance (The sprite will be center by this window size)
    void CenterASprite(sf::Sprite *SpriteToCenter,  const sf::Window* Window_Referance);

    /// @brief Getting a sprite and a window pointers and centering the sprite that will fit the window
    /// @attention Side effect Changing the origin to the middle
    /// @version 2.5.1 SFML
    /// @param TransformableToCenter object to center
    /// @param window_referance Current window referance (The sprite will be center by this window size)
    /// @param object_bounds object bounds (Default 0,0 (point))
    /// @param object_origin The object origin (Default 0,0 top left)
    void CenterATransformable(sf::Transformable *TransformableToCenter, const sf::Window* window_referance, sf::FloatRect object_bounds = sf::FloatRect(), sf::Vector2f object_origin = {0,0});

    /// @brief Setting the position of the transformable on the window based on the position_on_window delivered 
    /// @param position_on_window 
    /// @param TransformableToCenter object to center
    /// @param window_referance Current window referance (The sprite will be center by this window size)
    /// @param object_bounds object bounds (Default 0,0 (point))
    /// @param object_origin The object origin (Default 0,0 top left)
    void SetTransformablePosition(sf::Transformable *TransformableToCenter, const sf::Window* window_referance, SFMLBoost::POSITION position_on_window , sf::FloatRect object_bounds = sf::FloatRect(), sf::Vector2f object_origin = {0,0});

    // position setters

    // Toppers 
    
    void _SetTransformablePosition_TOPLEFT(sf::Transformable *TransformableToCenter, const sf::Window* window_referance, const sf::FloatRect& object_bounds = sf::FloatRect(), const sf::Vector2f& object_origin = {0,0});
    void _SetTransformablePosition_TOPRIGHT(sf::Transformable *TransformableToCenter, const sf::Window* window_referance, const sf::FloatRect& object_bounds = sf::FloatRect(), const sf::Vector2f& object_origin = {0,0});
    void _SetTransformablePosition_TOPCENTER(sf::Transformable *TransformableToCenter, const sf::Window* window_referance, const sf::FloatRect& object_bounds = sf::FloatRect(), const sf::Vector2f& object_origin = {0,0});

    // Centers
    void _SetTransformablePosition_CENTERLEFT(sf::Transformable *TransformableToCenter, const sf::Window* window_referance, const sf::FloatRect& object_bounds = sf::FloatRect(), const sf::Vector2f& object_origin = {0,0});
    void _SetTransformablePosition_CENTERRIGHT(sf::Transformable *TransformableToCenter, const sf::Window* window_referance, const sf::FloatRect& object_bounds = sf::FloatRect(), const sf::Vector2f& object_origin = {0,0});

    // Bottoms
    void _SetTransformablePosition_BOTTOMLEFT(sf::Transformable *TransformableToCenter, const sf::Window* window_referance, const sf::FloatRect& object_bounds = sf::FloatRect(), const sf::Vector2f& object_origin = {0,0});
    void _SetTransformablePosition_BOTTOMRIGHT(sf::Transformable *TransformableToCenter, const sf::Window* window_referance, const sf::FloatRect& object_bounds = sf::FloatRect(), const sf::Vector2f& object_origin = {0,0});
    void _SetTransformablePosition_BOTTOMCENTER(sf::Transformable *TransformableToCenter, const sf::Window* window_referance, const sf::FloatRect& object_bounds = sf::FloatRect(), const sf::Vector2f& object_origin = {0,0});

}

#endif