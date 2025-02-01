#pragma once
#include <memory>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Scene.hpp"
#include "SFMLBoost.hpp"

enum STATIC_SCENES_DEFINES
{
    SPLASH_SCREEN = 0x00,
    MENU,
    SETTINGS_MENU
};

/// @brief Singleton Scene manager
class SceneManager
{
private:
    std::unique_ptr<Scene> Active_Scene;
    std::unique_ptr<sf::Window> Active_window;

    /* data */
    SceneManager(/* args */);
    SceneManager(const SceneManager&) = delete;
    void operator=(const SceneManager&) = delete;

public:
    Scene* GetCurrentScene();
    void SetCurrentScene(Scene* new_scene);

    /// @brief Too allow singleton we used this function to create single static object of this class
    /// @return the Intance of the current SceneManager
    static SceneManager* GetIntance();
};