#include "BoostSFML.hpp"

void SFMLBoost::CenterASprite(sf::Sprite *SpriteToCenter, const sf::Window* Window_Referance)
{    
    sf::Vector2f OriginSprite_Original = SpriteToCenter->getOrigin();
    
    CenterATransformable(SpriteToCenter, Window_Referance, SpriteToCenter->getGlobalBounds(), SpriteToCenter->getOrigin());
}

void SFMLBoost::CenterATransformable(sf::Transformable *TransformableToCenter, const sf::Window *window_referance, sf::FloatRect object_bounds, sf::Vector2f object_origin)
{
    sf::Vector2f WindowMiddle = {window_referance->getSize().x / 2.0f, window_referance->getSize().y / 2.0f};

    
#ifdef BOOSTSFML_HPP_DEBUG 
    std::cout << "[DEBUG (BoostSFML)] Centering sprite: Center before the origin position" << WindowMiddle.x << ", " << WindowMiddle.y << std::endl;
    std::cout << "[DEBUG (BoostSFML)] Sprite Origin: " << object_origin.x << ", " << object_origin.y << std::endl;
    std::cout << "[DEBUG (BoostSFML)] window size: " << window_referance->getSize().x << ", " << window_referance->getSize().y << std::endl;
#endif

    WindowMiddle.x -= (object_bounds.width / 2) - object_origin.x;
    WindowMiddle.y -= (object_bounds.height / 2) - object_origin.y;

    

#ifdef BOOSTSFML_HPP_DEBUG 
    std::cout << "[DEBUG (BoostSFML)] Centering sprite: Center minus the origin position -> " << WindowMiddle.x << ", " << WindowMiddle.y << std::endl;
#endif

    TransformableToCenter->setPosition(WindowMiddle);


}
