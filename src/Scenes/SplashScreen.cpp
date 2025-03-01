#include "SplashScreen.hpp"

void SplashScreen::Start(std::shared_ptr<sf::RenderWindow> Scene_window)
{
    Scene::Start(Scene_window);

#ifdef DEBUG
    std::cout << "[DEBUG (SplashScreen::Start)] Running on window: " << Scene_window << std::endl;
#endif

    this->m_logo_sprite = std::make_shared<sf::Sprite>(*(AssetsCacheManager::GetIntance()->GetTexture(LOGO_ASSET_NAME)));
    this->m_logo_sprite->scale({4.0, 4.0});
    
    SFMLBoost::CenterASprite(this->m_logo_sprite.get(), Scene_window.get());

    this->m_drawables_objects.push_back(this->m_logo_sprite.get());
    
    this->Objects_groups.push_back(this->m_Logo_group);

#ifdef DEBUG
    std::cout << "[DEBUG (SplashScreen::Start)] Logo added to render list: " << this->m_logo_sprite.get() << std::endl; 
#endif

    // setting the text
    this->m_logo_text = std::make_shared<sf::Text>();
    this->m_logo_text->setFont(AssetsCacheManager::GetIntance()->GetFont_ref());

    this->m_logo_text->setCharacterSize(34);
    this->m_logo_text->setString(SPLASH_SCREEN_TEXT);

#ifdef DEBUG
    std::cout << "[DEBUG (SplashScreen::Start)] Logo text centered: [" << this->m_logo_text->getPosition().x << ',' << this->m_logo_text->getPosition().y << ']' << std::endl; 
#endif
    
    // setting the positon of the text
    SFMLBoost::CenterATransformable(this->m_logo_text.get(), Scene_window.get(), this->m_logo_text->getGlobalBounds());
    this->m_logo_text->move({0, (this->m_logo_sprite->getGlobalBounds().height + 1)});
    
    // adding to the render list
    this->m_drawables_objects.push_back(this->m_logo_text.get());

#ifdef DEBUG
    std::cout << "[DEBUG (SplashScreen::Start)] Logo text added to render list: " << this->m_logo_text.get() << std::endl; 
#endif

    // Changing scene after 3 seconds delay
    std::thread([]{
        std::this_thread::sleep_for(std::chrono::seconds(3));
        SceneManager::GetIntance()->SetCurrentScene(new MainMenu());
    }).detach();
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
    
    // ! TODO: Fix Bug unable to access the scene_window!
    Scene::Render_objects(Scene_window);
}
