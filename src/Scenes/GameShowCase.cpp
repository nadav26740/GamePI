#include "GameShowCase.hpp"

const sf::Color& GameShowCase::ColorRotation(std::size_t index)
{
    return cm_colors_rotation[index % cm_colors_rotation.size()];
}

void GameShowCase::IncrementSelected()
{
    // Chacking if any games exists
    if(!this->m_LoadedGames.size())
        return;

    m_SelectedGame_Index++;
    m_SelectedGame_Index %= m_LoadedGames.size();

    // So The update game list will happpen
    m_SelectedGameChanged = true;
}

void GameShowCase::DecrementSelected()
{
    // Chacking if any games exists
    if(!this->m_LoadedGames.size())
        return;

    if(m_SelectedGame_Index)
        m_SelectedGame_Index--;
    else
        m_SelectedGame_Index = m_LoadedGames.size() - 1;
    
    // So The update game list will happpen
    m_SelectedGameChanged = true;
}

void GameShowCase::UpdateGamesList(std::shared_ptr<sf::RenderWindow> Scene_window)
{
    // Check if no games 
    if (m_LoadedGames.size() == 0)
        return;
    
    std::string Game_name;

    // Changing the background color
    this->m_Background_Color = this->ColorRotation(this->m_SelectedGame_Index);    
    
    // Making sure that we won't get memory access violation bug 
    std::size_t TempIndex = ((this->m_SelectedGame_Index - 2) + m_LoadedGames.size() * (LIST_NAME_SIZE_ON_SCREEN / 2));

    // Adding the games into the graphical list
    for (int i = 0; i < LIST_NAME_SIZE_ON_SCREEN; i++)
    {
        Game_name = this->m_LoadedGames[(TempIndex + i) % this->m_LoadedGames.size()].GameName;
        this->m_names_list_text[i].setString(Game_name);
//         std::cout << "[DEBUG (GameShowCase::UpdateGamesList)] " <<  i << ": " 
//                 << this->m_names_list_text[i].getPosition().x << ", " << this->m_names_list_text[i].getPosition().y 
//                 << " - " << Game_name << std::endl;
//    #endif
    }
    // TODO: Play Swipe Sound

    m_SelectedGameChanged = false;
}

void GameShowCase::CreateGamesList(std::shared_ptr<sf::RenderWindow> Scene_window)
{
    float GapBetweenNames = (Scene_window->getSize().y - LIST_GAP_FROM_TOP - LIST_GAP_FROM_BOTTOM) / LIST_NAME_SIZE_ON_SCREEN; 
    std::string Game_name;
    const sf::Font& text_font = AssetsCacheManager::GetIntance()->GetFont_ref();
    std::size_t middle_index_in_list = LIST_NAME_SIZE_ON_SCREEN / 2;

    // Changing the background color
    this->m_Background_Color = this->ColorRotation(this->m_SelectedGame_Index);
    
    
    // Showing error if no games 
    if (m_LoadedGames.size() == 0)
    {
        cpp_colors::colorful_print("[DEBUG ERROR (GameShowCase::UpdateGamesList)] No games found!", cpp_colors::foreground::bright_red, std::cerr);
        
        this->m_names_list_text.emplace_back();
        this->m_names_list_text[0].setFont(text_font);
        this->m_names_list_text[0].setString(std::string("No Games Found."));
        this->m_names_list_text[0].setFillColor(cm_text_color);
        this->m_names_list_text[0].setCharacterSize(cm_font_size);
        this->m_names_list_text[0].setPosition({LIST_GAP_FROM_LEFT, (GapBetweenNames * middle_index_in_list) + LIST_GAP_FROM_TOP + (cm_font_size / 2)});
        return;
    }
    
    // Pre allocating memory for optimization
    this->m_names_list_text.reserve(LIST_NAME_SIZE_ON_SCREEN);
    
    // Making sure that we won't get memory access violation bug 
    std::size_t TempIndex = ((this->m_SelectedGame_Index - 2) + m_LoadedGames.size() * (LIST_NAME_SIZE_ON_SCREEN / 2));

    // Adding the games into the graphical list
    for (int i = 0; i < LIST_NAME_SIZE_ON_SCREEN; i++)
    {
        Game_name = this->m_LoadedGames[(TempIndex + i) % this->m_LoadedGames.size()].GameName;
        this->m_names_list_text.emplace_back();
        this->m_names_list_text[i].setFont(text_font);
        this->m_names_list_text[i].setString(Game_name);
        this->m_names_list_text[i].setFillColor(cm_text_color);
        this->m_names_list_text[i].setCharacterSize(cm_font_size);
        this->m_names_list_text[i].setPosition({LIST_GAP_FROM_LEFT, (GapBetweenNames * i) + LIST_GAP_FROM_TOP + (cm_font_size / 2)});
    }

    this->m_names_list_text[middle_index_in_list].setStyle(sf::Text::Bold);
    this->m_names_list_text[middle_index_in_list].setOutlineThickness(4);
    this->m_names_list_text[middle_index_in_list].setOutlineColor(cm_Selected_color);

    m_SelectedGameChanged = false;
}

void GameShowCase::LoadGamesListFromConfig()
{
    std::filesystem::path games_directory = ConfigLoader::GetIntance()->GetGamesDirectory();
    std::string game_extension = ConfigLoader::GetIntance()->GetGamesExtension();
    
    if (!std::filesystem::exists(games_directory))
    {
        cpp_colors::colorful_print("[ERROR (GameShowCase::LoadGamesListFromConfig)] " + games_directory.string() + ": NOT FOUND", cpp_colors::foreground::bright_red, std::cerr);
        return;
    }
    else if (!std::filesystem::is_directory(games_directory))
    {
        cpp_colors::colorful_print("[ERROR (GameShowCase::LoadGamesListFromConfig)] " + games_directory.string() + ": isn't a directory", cpp_colors::foreground::bright_red, std::cerr);
        return;
    }

    for (const auto& dir_paths : std::filesystem::directory_iterator(games_directory))
    {
        if (dir_paths.is_directory())
        {
        #ifdef DEBUG
            std::cout << "[GameShowCase::LoadGamesListFromConfig] Loading Game Directory: " << dir_paths << std::endl;
        #endif
            this->m_LoadedGames.emplace_back(LoadedGame(dir_paths.path().filename().string(), // Getting game name from folder name
                                                        std::filesystem::path(), // Getting Img cover
                                                        this->FindGameFile(dir_paths, game_extension))); // Finding the game file
        }
    }
}

void GameShowCase::RunGame()
{
    // Checking if any games loaded
    if (!this->m_LoadedGames.size())
    {
        std::cerr << "[ERROR (GameShowCase::RunGame)] No games loaded!" << std::endl; 
        // TODO: Play ERROR sound!
        return;
    }

    std::string Run_Command = ConfigLoader::GetIntance()->GetEmulatorName() + " " + this->m_LoadedGames[this->m_SelectedGame_Index].GameFile.string() + " " +  ConfigLoader::GetIntance()->GetEmulatorFlags();
    std::cout << "[GameShowCase::RunGame] Run game command: " << Run_Command << std::endl; 
    // TODO: Add popen (process open)

    // TODO: move to monitor scene!
}

std::filesystem::path GameShowCase::FindGameFile(const std::filesystem::path& dir_path, const std::string& extension)
{
    for (const auto& file_path : std::filesystem::directory_iterator(dir_path))
    {
        if (!file_path.is_directory() && file_path.exists() &&
                file_path.path().extension() == extension)
        {
        #ifdef DEBUG
            std::cout << "[GameShowCase::FindGameFile] Found game file: " << file_path << std::endl;
        #endif

            return file_path;
        }
    }

    cpp_colors::colorful_print("[ERROR (GameShowCase::FindGameFile)] Game File has been found: " + dir_path.string(), cpp_colors::foreground::bright_magenta, std::cerr);
    return std::filesystem::path();
}

void GameShowCase::Start(std::shared_ptr<sf::RenderWindow> Scene_window)
{
    // TODO Add load all the games 
    LoadGamesListFromConfig();
    CreateGamesList(Scene_window);
    this->m_Background_Color = this->ColorRotation(0);

    // * Setting the cover image
    this->m_showcase_texture = AssetsCacheManager::GetIntance()->GetTexture_ref("Cartridge");
    this->m_img_showcase.setTexture(this->m_showcase_texture);
    sf::FloatRect size_vec = this->m_img_showcase.getGlobalBounds();
    this->m_img_showcase.setScale( { this->cm_cover_width / size_vec.width, this->cm_cover_height / size_vec.height } );
    
    // Setting position
    SFMLBoost::SetTransformablePosition(&(this->m_img_showcase), Scene_window.get(), SFMLBoost::POSITION::CENTER_RIGHT, this->m_img_showcase.getGlobalBounds(), this->m_img_showcase.getOrigin());
    this->m_img_showcase.move({-40, 0});

    this->m_drawables_objects.push_back(&m_img_showcase);
}

void GameShowCase::Frame_update(std::queue<sf::Event> events_queue)
{
    // Adding movment in the game
    // Using event to change only on press and not on hold
    while (!events_queue.empty())
    {
        if (events_queue.back().type == sf::Event::KeyPressed)
        {
            switch (events_queue.back().key.code)
            {
            case sf::Keyboard::Up:
                // std::cout << "[GameShowCase::Frame_update] Changing selected game Up" << std::endl;
                DecrementSelected();
                return;
                break;

            case sf::Keyboard::Down:
                // std::cout << "[GameShowCase::Frame_update] Changing selected game Down" << std::endl;
                IncrementSelected();
                return;
                break;

            case sf::Keyboard::Enter:
                std::cout << "Enter Pressed!" << std::endl;
                return;
                break;
            }
        }
        events_queue.pop();
    }
}

void GameShowCase::Graphical_update(std::shared_ptr<sf::RenderWindow> Scene_window)
{
    if (m_SelectedGameChanged)
    {
        this->UpdateGamesList(Scene_window);
    }

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

GameShowCase::LoadedGame::LoadedGame(std::string GameName, std::filesystem::path CoverIMG, std::filesystem::path GameFile)
{
    this->CoverIMG = CoverIMG;
    this->GameFile = GameFile;
    this->GameName = GameName;
}
