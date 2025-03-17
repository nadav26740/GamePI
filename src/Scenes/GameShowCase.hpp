#pragma once
#ifndef GAMESHOWCASE_HPP
#define GAMESHOWCASE_HPP

#include <iostream>
#include <memory>
#include "libs/SFMLBoost.hpp"

#include "Core/ConfigLoader.hpp"
#include "Core/Scenes/Scene.hpp"
#include "Core/Scenes/SceneManager.hpp"
#include "Core/AssetsCacheManager.hpp"

#define LIST_NAME_SIZE_ON_SCREEN 5
#define LIST_GAP_FROM_LEFT 40
#define LIST_GAP_FROM_TOP 40
#define LIST_GAP_FROM_BOTTOM 40

class GameShowCase : public Scene
{
private:

    /// Color Rotation:
    const std::vector<sf::Color> cm_colors_rotation {sf::Color(4, 59, 92), sf::Color(40, 67, 135), sf::Color(36, 37, 42), sf::Color(65, 147, 169)};

    /// @brief Getting index and return background color for that specific index
    /// @param index current selected index
    /// @return Color
    const sf::Color& ColorRotation(std::size_t index);

    // * Games
    struct LoadedGame
    {
        // Constructor
        LoadedGame(std::string GameName,
            std::filesystem::path CoverIMG,
            std::filesystem::path GameFile);

        /* data */
        std::string GameName;
        std::filesystem::path CoverIMG;
        std::filesystem::path GameFile;
    };

    std::vector<LoadedGame> m_LoadedGames;
    std::size_t m_SelectedGame_Index = 0;
    bool m_SelectedGameChanged = false;
    
    /// Changing selected game by one
    void IncrementSelected();
    
    // Changing selected game
    void DecrementSelected();

    // * Games Showcase IMG
    sf::Sprite m_img_showcase;
    sf::Texture m_showcase_texture;
    std::shared_ptr<sf::Text> m_Game_name_text;
    std::string m_Game_name;

    const float cm_cover_height = 300;
    const float cm_cover_width = 300;
    
    // * Games List
    const sf::Color cm_Selected_color = sf::Color(108, 122, 137);
    const sf::Color cm_text_color = sf::Color(247, 249, 247);
    const float cm_font_size = 32;
    std::vector<std::string> m_Games_names;
    std::vector<sf::Text> m_names_list_text;

    // The timepoint where we allowed to take inptu
    std::chrono::steady_clock::time_point m_DelayInput;
    
    /// @brief Update game list to the screen
    /// @param Scene_window The scene's render window
    void UpdateGamesList(std::shared_ptr<sf::RenderWindow> Scene_window);

    /// @brief Create game list to the screen
    /// @param Scene_window The scene's render window
    void CreateGamesList(std::shared_ptr<sf::RenderWindow> Scene_window);
    
    /// @brief getting all the games in the config path
    void LoadGamesListFromConfig();

    void RunGame();

    static std::filesystem::path FindGameFile(const std::filesystem::path& dir_path, const std::string& extension);

public:
    virtual void Start(std::shared_ptr<sf::RenderWindow> Scene_window);

    /// @brief Runs every frame responsible for the logical part of the frame
    virtual void Frame_update(std::queue<sf::Event> events_queue);

    /// @brief Runs every frame responsible for the graphical part of the frame
    virtual void Graphical_update(std::shared_ptr<sf::RenderWindow> Scene_window);

    virtual void Render_objects(std::shared_ptr<sf::RenderWindow> Scene_window);
    
    
};

#endif