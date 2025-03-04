#include "GameShowCase.hpp"

void GameShowCase::Start(std::shared_ptr<sf::RenderWindow> Scene_window)
{
    this->m_button_background.setSize({140, 50});
    this->m_button_background.setFillColor(sf::Color(59, 120, 255));
    this->m_button_background.setOutlineColor(sf::Color(72, 180, 236));
    this->m_button_background.setOutlineThickness(3);
    SFMLBoost::CenterATransformable(&m_button_background, Scene_window.get(), m_button_background.getGlobalBounds());
    this->m_button_background.move({0, 50});
    
    this->m_drawables_objects.push_back(&m_button_background);

    this->m_button_text.setString("Play");
    this->m_button_text.setCharacterSize(22);
    this->m_button_text.setFont(AssetsCacheManager::GetIntance()->GetFont_ref());
    SFMLBoost::CenterATransformable(&m_button_text, Scene_window.get(), m_button_text.getGlobalBounds());
    this->m_button_text.move({0, 50});
    
    this->m_drawables_objects.push_back(&m_button_text);

}

void GameShowCase::Frame_update(std::queue<sf::Event> events_queue)
{
}

void GameShowCase::Graphical_update()
{
    
    Scene::Graphical_update();
}

void GameShowCase::Render_objects(std::shared_ptr<sf::RenderWindow> Scene_window)
{
    
    Scene::Render_objects(Scene_window);
}
