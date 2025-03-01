#include "MainMenu.hpp"

void MainMenu::Start(std::shared_ptr<sf::RenderWindow> Scene_window)
{
    // Creating the text
    this->m_logo_text = std::make_shared<sf::Text>();
    
    // Setting text font and string
    this->m_logo_text->setFont(*(AssetsCacheManager::GetIntance()->GetFont()));
    this->m_logo_text->setString("Main Menu Running");

    m_fps_text.setFont(*(AssetsCacheManager::GetIntance()->GetFont()));
    m_fps_text.setColor(sf::Color::Black);

    SFMLBoost::CenterATransformable(this->m_logo_text.get(), Scene_window.get(), this->m_logo_text->getLocalBounds());

    this->m_drawables_objects.push_back(this->m_logo_text.get());
    this->m_drawables_objects.push_back(&m_fps_text);

}

void MainMenu::Frame_update()
{
    static std::chrono::steady_clock::time_point last_epoch;
    int frame_Rate = 1000 / (std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()).time_since_epoch().count() - 
                    std::chrono::time_point_cast<std::chrono::milliseconds>(last_epoch).time_since_epoch().count());

    last_epoch = std::chrono::steady_clock::now();
    m_fps_text.setString("Fps: " + std::to_string(frame_Rate));
}


void MainMenu::Graphical_update()
{
}

void MainMenu::Render_objects(std::shared_ptr<sf::RenderWindow> Scene_window)
{
    Scene::Render_objects(Scene_window);
}
