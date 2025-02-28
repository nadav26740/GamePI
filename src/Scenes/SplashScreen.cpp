#include "SplashScreen.hpp"

void SplashScreen::Start(std::shared_ptr<sf::RenderWindow> Scene_window)
{
    Scene::Start(Scene_window);

    std::cout << "[SplashScreen::Start] Running on window: " << Scene_window << std::endl;

    this->m_logo_sprite = std::make_shared<sf::Sprite>(*(AssetsCacheManager::GetIntance()->GetTexture(LOGO_ASSET_NAME)));
    this->m_logo_sprite->scale({4.0, 4.0});
    
    SFMLBoost::CenterASprite(this->m_logo_sprite.get(), Scene_window.get());

    this->m_drawables_objects.push_back(this->m_logo_sprite.get());
    
    // this->m_logo_sprite_wrapper = std::make_shared<SFMLBoost::Object_wrapper>(this->m_logo_sprite, this->m_logo_sprite.get());
    // this->m_Logo_group.SetPosition(this->m_logo_sprite->getPosition());
    
    // this->m_Logo_group.Objects_in_group.emplace_back(this->m_logo_sprite_wrapper);
    this->Objects_groups.push_back(this->m_Logo_group);
}

void SplashScreen::Frame_update()
{
}

void SplashScreen::Graphical_update()
{
}

void SplashScreen::Render_objects(std::shared_ptr<sf::RenderWindow> Scene_window)
{
    // std::cout << "Running! " << std::endl;
    Scene_window->clear(sf::Color(29, 180, 237));
    
    // ! TODO: Fix Bug unable to access the scene_window!
    Scene::Render_objects(Scene_window);
}
