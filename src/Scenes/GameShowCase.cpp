#include "GameShowCase.hpp"

void GameShowCase::AddGamesList(std::shared_ptr<sf::RenderWindow> Scene_window)
{
    float GapBetweenNames = (Scene_window->getSize().y - LIST_GAP_FROM_TOP - LIST_GAP_FROM_BOTTOM) / LIST_NAME_SIZE_ON_SCREEN; 
    std::string Game_name;

    this->m_names_list_text.reserve(LIST_NAME_SIZE_ON_SCREEN);
    for (int i = 0; i < LIST_NAME_SIZE_ON_SCREEN; i++)
    {
        Game_name = "Game " + std::to_string(i);
        this->m_names_list_text.emplace_back();
        this->m_names_list_text[i].setFont(AssetsCacheManager::GetIntance()->GetFont_ref());
        this->m_names_list_text[i].setString(Game_name);
        this->m_names_list_text[i].setFillColor(cm_text_color);
        this->m_names_list_text[i].setCharacterSize(cm_font_size);
        this->m_names_list_text[i].setPosition({LIST_GAP_FROM_LEFT, (GapBetweenNames * i) + LIST_GAP_FROM_TOP + (cm_font_size / 2)});

#ifdef DEBUG
        std::cout << "[DEBUG (GameShowCase::AddGamesList)] " <<  i << ": " 
                << this->m_names_list_text[i].getPosition().x << ", " << this->m_names_list_text[i].getPosition().y 
                << " - " << Game_name << std::endl;
#endif
    }

    this->m_names_list_text[LIST_NAME_SIZE_ON_SCREEN / 2].setStyle(sf::Text::Bold);
    this->m_names_list_text[LIST_NAME_SIZE_ON_SCREEN / 2].setOutlineThickness(4);
    this->m_names_list_text[LIST_NAME_SIZE_ON_SCREEN / 2].setOutlineColor(cm_Selected_color);
}

void GameShowCase::Start(std::shared_ptr<sf::RenderWindow> Scene_window)
{
    // * Creating Button Background color
    // this->m_button_background = std::make_shared<sf::RectangleShape>();
    // this->m_button_background->setSize({140, 50});
    // this->m_button_background->setFillColor(sf::Color(59, 120, 255));
    // this->m_button_background->setOutlineColor(sf::Color(72, 180, 236));
    // this->m_button_background->setOutlineThickness(3);
    // SFMLBoost::CenterATransformable(m_button_background.get(), Scene_window.get(), m_button_background->getGlobalBounds());    

    // // * Adding Button Text
    // this->m_button_text = std::make_shared<sf::Text>();
    // this->m_button_text->setString("Play");
    // this->m_button_text->setCharacterSize(22);
    // this->m_button_text->setFont(AssetsCacheManager::GetIntance()->GetFont_ref());
    // SFMLBoost::CenterATransformable(m_button_text.get(), Scene_window.get(), m_button_text->getGlobalBounds());

    // // * Connecting the button elements togheter
    // this->m_button_group.Objects_in_group.push_back(std::make_shared<SFMLBoost::Object_wrapper>(this->m_button_background, this->m_button_background.get()));
    // this->m_button_group.Objects_in_group.push_back(std::make_shared<SFMLBoost::Object_wrapper>(this->m_button_text, this->m_button_text.get()));
    
    // this->m_button_group.move({0, 200});
    // this->Objects_groups.push_back(&this->m_button_group);

    // TODO Add load all the games 

    // * Setting the cover image
    this->m_showcase_texture = AssetsCacheManager::GetIntance()->GetTexture_ref("Cartridge");
    this->m_img_showcase.setTexture(this->m_showcase_texture);
    sf::FloatRect size_vec = this->m_img_showcase.getGlobalBounds();
    this->m_img_showcase.setScale( { this->cm_cover_width / size_vec.width, this->cm_cover_height / size_vec.height } );
    // Setting position
    SFMLBoost::SetTransformablePosition(&(this->m_img_showcase), Scene_window.get(), SFMLBoost::POSITION::CENTER_RIGHT, this->m_img_showcase.getGlobalBounds(), this->m_img_showcase.getOrigin());
    this->m_img_showcase.move({-40, 0});

    this->m_drawables_objects.push_back(&m_img_showcase);
    
    AddGamesList(Scene_window);
}

void GameShowCase::Frame_update(std::queue<sf::Event> events_queue)
{
}

void GameShowCase::Graphical_update(std::shared_ptr<sf::RenderWindow> Scene_window)
{
    Scene::Graphical_update(Scene_window);
}

void GameShowCase::Render_objects(std::shared_ptr<sf::RenderWindow> Scene_window)
{
    Scene::Render_objects(Scene_window);
    for (auto itr : m_names_list_text)
    {
        Scene_window->draw(itr);
    }
}
