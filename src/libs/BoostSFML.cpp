#include "BoostSFML.hpp"

void SFMLBoost::CenterASprite(sf::Sprite *SpriteToCenter, sf::Texture* SpriteTexture, sf::Window* Window_Referance)
{
    sf::Vector2f WindowMiddle = {Window_Referance->getSize().x / 2.0f, Window_Referance->getSize().y / 2.0f};
    
    sf::Vector2f OriginSprite_Original = SpriteToCenter->getOrigin();

    #ifdef BOOSTSFML_HPP_DEBUG 
        std::cout << "[(BoostSFML) DEBUG] Centering sprite: Center before the origin position" << WindowMiddle.x << ", " << WindowMiddle.y << std::endl;
        std::cout << "[(BoostSFML) DEBUG] Texture size: " << SpriteTexture->getSize().x << ", " << SpriteTexture->getSize().y << std::endl;
        std::cout << "[(BoostSFML) DEBUG] Sprite Origin: " << OriginSprite_Original.x << ", " << OriginSprite_Original.y << std::endl;
        std::cout << "[(BoostSFML) DEBUG] window size: " << Window_Referance->getSize().x << ", " << Window_Referance->getSize().y << std::endl;
    #endif

    WindowMiddle.x -= (SpriteToCenter->getGlobalBounds().width / 2) - OriginSprite_Original.x;
    WindowMiddle.y -= (SpriteToCenter->getGlobalBounds().height / 2) - OriginSprite_Original.y;

    #ifdef BOOSTSFML_HPP_DEBUG 
        std::cout << "[(BoostSFML) DEBUG] Centering sprite: Center minus the origin position -> " << WindowMiddle.x << ", " << WindowMiddle.y << std::endl;
    #endif
    
    
    // SpriteToCenter->setOrigin({SpriteTexture->getSize().x / 2.0f, SpriteTexture->getSize().y / 2.0f});
    SpriteToCenter->setPosition(WindowMiddle);
    // SpriteToCenter->setOrigin(OriginSprite_Original);
}