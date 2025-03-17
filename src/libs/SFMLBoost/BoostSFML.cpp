#include "BoostSFML.hpp"

void SFMLBoost::CenterASprite(sf::Sprite *SpriteToCenter, const sf::Window* Window_Referance)
{        
    CenterATransformable(SpriteToCenter, Window_Referance, SpriteToCenter->getGlobalBounds(), SpriteToCenter->getOrigin());
}

void SFMLBoost::CenterATransformable(sf::Transformable *TransformableToCenter, const sf::Window* window_referance, sf::FloatRect object_bounds, sf::Vector2f object_origin)
{
    sf::Vector2f WindowMiddle = {window_referance->getSize().x / 2.0f, window_referance->getSize().y / 2.0f};
    WindowMiddle.x -= (object_bounds.width / 2) - object_origin.x;
    WindowMiddle.y -= (object_bounds.height / 2) - object_origin.y;

#ifdef BOOSTSFML_HPP_DEBUG 
    std::cout << "[DEBUG (SFMLBoost::CenterATransformable)] Centering sprite: Center minus the origin position -> " << WindowMiddle.x << ", " << WindowMiddle.y << std::endl;
#endif

    TransformableToCenter->setPosition(WindowMiddle);
}

// * Manager *
void SFMLBoost::SetTransformablePosition(sf::Transformable *TransformableToCenter, const sf::Window *window_referance, SFMLBoost::POSITION position_on_window, sf::FloatRect object_bounds, sf::Vector2f object_origin)
{
    switch (position_on_window)
    {
        
    case POSITION::TOP_LEFT:
        _SetTransformablePosition_TOPLEFT(TransformableToCenter, window_referance, object_bounds, object_origin);
        break;
        
    case POSITION::TOP_CENTER:
        _SetTransformablePosition_TOPCENTER(TransformableToCenter, window_referance, object_bounds, object_origin);
        break;
        
    case POSITION::TOP_RIGHT:
        _SetTransformablePosition_TOPRIGHT(TransformableToCenter, window_referance, object_bounds, object_origin);
        break;

    case POSITION::CENTER_LEFT:
        _SetTransformablePosition_CENTERLEFT(TransformableToCenter, window_referance, object_bounds, object_origin);    
        break;

    case POSITION::CENTER:
        CenterATransformable(TransformableToCenter, window_referance, object_bounds, object_origin);
        break;
        
    case POSITION::CENTER_RIGHT:
        _SetTransformablePosition_CENTERRIGHT(TransformableToCenter, window_referance, object_bounds, object_origin);    
        break;
        
    case POSITION::BOTTOM_LEFT:
        _SetTransformablePosition_BOTTOMLEFT(TransformableToCenter, window_referance, object_bounds, object_origin);    
        break;


    case POSITION::BOTTOM_CENTER:
        _SetTransformablePosition_BOTTOMCENTER(TransformableToCenter, window_referance, object_bounds, object_origin);    
        break;


    case POSITION::BOTTOM_RIGHT:
        _SetTransformablePosition_BOTTOMRIGHT(TransformableToCenter, window_referance, object_bounds, object_origin);    
        break;

    default:
        std::cerr << "[ERROR (SFMLBoost::SetTransformablePosition)] Unknown Position Delivered: " << position_on_window << std::endl;
        break;
    }
}

// * Toppers * 

void SFMLBoost::_SetTransformablePosition_TOPLEFT(sf::Transformable *TransformableToCenter, const sf::Window* window_referance, const sf::FloatRect& object_bounds, const sf::Vector2f& object_origin)
{
#ifdef DEBUG
    std::cout << "[DEBUG (SFMLBoost::_SetTransformablePosition_TOPLEFT)] Setting position: " << object_origin.x << ", " << object_origin.y << std::endl;
#endif

    TransformableToCenter->setPosition(object_origin);
}

void SFMLBoost::_SetTransformablePosition_TOPCENTER(sf::Transformable *TransformableToCenter, const sf::Window *window_referance, const sf::FloatRect& object_bounds, const sf::Vector2f &object_origin)
{
    sf::Vector2f WindowMiddle = {window_referance->getSize().x / 2.0f, window_referance->getSize().y / 2.0f};
    WindowMiddle.x -= (object_bounds.width / 2) - object_origin.x;
    WindowMiddle.y = object_origin.y;

#ifdef DEBUG
    std::cout << "[DEBUG (SFMLBoost::_SetTransformablePosition_TOPCENTER)] Setting position: " << WindowMiddle.x << ", " << WindowMiddle.y << std::endl;
#endif


    TransformableToCenter->setPosition(WindowMiddle);
}


void SFMLBoost::_SetTransformablePosition_TOPRIGHT(sf::Transformable *TransformableToCenter, const sf::Window *window_referance, const sf::FloatRect& object_bounds, const sf::Vector2f &object_origin)
{
    
    sf::Vector2f new_pos;
    new_pos.y = object_origin.y;
    new_pos.x = window_referance->getSize().x - object_bounds.width + object_origin.x;
    
#ifdef DEBUG
    std::cout << "[DEBUG (SFMLBoost::_SetTransformablePosition_TOPRIGHT)] Setting position: " << new_pos.x << ", " << new_pos.y << std::endl;
#endif

    TransformableToCenter->setPosition(new_pos);
}

// * Centers * 

void SFMLBoost::_SetTransformablePosition_CENTERLEFT(sf::Transformable *TransformableToCenter, const sf::Window *window_referance, const sf::FloatRect &object_bounds, const sf::Vector2f &object_origin)
{
    sf::Vector2f new_pos = {object_origin.x, window_referance->getSize().y / 2.0f};
    new_pos.y -= (object_bounds.height / 2) - object_origin.y;

#ifdef DEBUG
    std::cout << "[DEBUG (SFMLBoost::_SetTransformablePosition_CENTERLEFT)] Setting position: " << new_pos.x << ", " << new_pos.y << std::endl;
#endif

    TransformableToCenter->setPosition(new_pos);
}

void SFMLBoost::_SetTransformablePosition_CENTERRIGHT(sf::Transformable *TransformableToCenter, const sf::Window *window_referance, const sf::FloatRect &object_bounds, const sf::Vector2f &object_origin)
{
    sf::Vector2f new_pos;
    new_pos.x = window_referance->getSize().x - object_bounds.width + object_origin.x;
    new_pos.y = (window_referance->getSize().y / 2.0f) - ((object_bounds.height / 2) - object_origin.y);

#ifdef DEBUG
    std::cout << "[DEBUG (SFMLBoost::_SetTransformablePosition_CENTERRIGHT)] Setting position: " << new_pos.x << ", " << new_pos.y << std::endl;
#endif


    TransformableToCenter->setPosition(new_pos);
}

// * Bottoms *
void SFMLBoost::_SetTransformablePosition_BOTTOMLEFT(sf::Transformable *TransformableToCenter, const sf::Window *window_referance, const sf::FloatRect &object_bounds, const sf::Vector2f &object_origin)
{
    sf::Vector2f new_pos;
    new_pos.y = window_referance->getSize().y - object_bounds.height + object_origin.y;
    new_pos.x = object_origin.x;

#ifdef DEBUG
    std::cout << "[DEBUG (SFMLBoost::_SetTransformablePosition_BOTTOMLEFT)] Setting position: " << new_pos.x << ", " << new_pos.y << std::endl;
#endif

    TransformableToCenter->setPosition(new_pos);
}

void SFMLBoost::_SetTransformablePosition_BOTTOMRIGHT(sf::Transformable *TransformableToCenter, const sf::Window *window_referance, const sf::FloatRect &object_bounds, const sf::Vector2f &object_origin)
{
    sf::Vector2f new_pos;
    new_pos.y = window_referance->getSize().y - object_bounds.height + object_origin.y;
    new_pos.x = window_referance->getSize().x - object_bounds.width + object_origin.x;

#ifdef DEBUG
    std::cout << "[DEBUG (SFMLBoost::_SetTransformablePosition_BOTTOMRIGHT)] Setting position: " << new_pos.x << ", " << new_pos.y << std::endl;
#endif

    TransformableToCenter->setPosition(new_pos);
}

void SFMLBoost::_SetTransformablePosition_BOTTOMCENTER(sf::Transformable *TransformableToCenter, const sf::Window *window_referance, const sf::FloatRect &object_bounds, const sf::Vector2f &object_origin)
{
    sf::Vector2f new_pos;
    new_pos.y = window_referance->getSize().y - object_bounds.height + object_origin.y;
    new_pos.x = (window_referance->getSize().x / 2.0f) - ((object_bounds.width / 2) - object_origin.x);

#ifdef DEBUG
    std::cout << "[DEBUG (SFMLBoost::_SetTransformablePosition_BOTTOMCENTER)] Setting position: " << new_pos.x << ", " << new_pos.y << std::endl;
#endif

    TransformableToCenter->setPosition(new_pos);
}
