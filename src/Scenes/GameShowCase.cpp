#include "GameShowCase.hpp"

void GameShowCase::Start(std::shared_ptr<sf::RenderWindow> Scene_window)
{
    // * Creating Button Background color
    this->m_button_background = std::make_shared<sf::RectangleShape>();
    this->m_button_background->setSize({140, 50});
    this->m_button_background->setFillColor(sf::Color(59, 120, 255));
    this->m_button_background->setOutlineColor(sf::Color(72, 180, 236));
    this->m_button_background->setOutlineThickness(3);
    SFMLBoost::CenterATransformable(m_button_background.get(), Scene_window.get(), m_button_background->getGlobalBounds());    

    // * Adding Button Text
    this->m_button_text = std::make_shared<sf::Text>();
    this->m_button_text->setString("Play");
    this->m_button_text->setCharacterSize(22);
    this->m_button_text->setFont(AssetsCacheManager::GetIntance()->GetFont_ref());
    SFMLBoost::CenterATransformable(m_button_text.get(), Scene_window.get(), m_button_text->getGlobalBounds());

    // * Connecting the button elements togheter
    this->m_button_group.Objects_in_group.push_back(std::make_shared<SFMLBoost::Object_wrapper>(this->m_button_background, this->m_button_background.get()));
    this->m_button_group.Objects_in_group.push_back(std::make_shared<SFMLBoost::Object_wrapper>(this->m_button_text, this->m_button_text.get()));
    
    this->m_button_group.move({0, 200});
    this->Objects_groups.push_back(&this->m_button_group);

    // TODO Add load all the games 

    // * Setting the cover image
    this->m_showcase_texture = AssetsCacheManager::GetIntance()->GetTexture_ref("Cartridge");
    this->m_img_showcase.setTexture(this->m_showcase_texture);
    sf::FloatRect size_vec = this->m_img_showcase.getGlobalBounds();
    this->m_img_showcase.setScale( { this->cm_cover_width / size_vec.width, this->cm_cover_height / size_vec.height } );\
    SFMLBoost::CenterASprite(&(this->m_img_showcase), Scene_window.get());
    this->m_img_showcase.move({0, -200});
    this->m_drawables_objects.push_back(&m_img_showcase);

    // * Adding game text
    this->m_Game_name = "Missing Game";
    this->m_Game_name_text = std::make_shared<sf::Text>();
    this->m_Game_name_text->setFont(AssetsCacheManager::GetIntance()->GetFont_ref());
    this->m_Game_name_text->setString(this->m_Game_name);
    
    // * Setting text position
    SFMLBoost::CenterATransformable(this->m_Game_name_text.get(), Scene_window.get(), this->m_Game_name_text->getGlobalBounds());
    this->m_Game_name_text->setPosition({this->m_Game_name_text->getPosition().x,
         (this->m_img_showcase.getPosition().y + this->m_img_showcase.getGlobalBounds().height + 20)});
    
         this->m_drawables_objects.push_back(this->m_Game_name_text.get());

}

void GameShowCase::Frame_update(std::queue<sf::Event> events_queue)
{
    // switch (rand() % 3)
    // {
    // case 0:
    //     SFMLBoost::SetTransformablePosition(&(this->m_img_showcase), )
    //     /* code */
    //     break;
    
    // default:
    //     break;
    // }
}

void GameShowCase::Graphical_update(std::shared_ptr<sf::RenderWindow> Scene_window)
{
    
    Scene::Graphical_update(Scene_window);
}

void GameShowCase::Render_objects(std::shared_ptr<sf::RenderWindow> Scene_window)
{
    
    Scene::Render_objects(Scene_window);
}
