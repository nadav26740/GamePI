#include "SceneManager.hpp"

Scene *SceneManager::GetCurrentScene()
{
    return Active_Scene.get();
}

SceneManager *SceneManager::GetIntance()
{
    static SceneManager INSTANCE;
    return &INSTANCE;
}

SceneManager::SceneManager()
{
    this->Active_window = std::make_unique<sf::Window>(sf::VideoMode({600,800}), "GamePI Window", sf::Style::Fullscreen);
}