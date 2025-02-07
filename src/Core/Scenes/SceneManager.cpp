#include "SceneManager.hpp"

Scene *SceneManager::GetCurrentScene()
{
    return m_Active_Scene.get();
}

void SceneManager::SetCurrentScene(Scene *new_scene)
{
    this->m_Active_Scene = std::make_unique<Scene>(std::move(new_scene));
    
}

SceneManager *SceneManager::GetIntance()
{
    static SceneManager INSTANCE;
    return &INSTANCE;
}

SceneManager::SceneManager()
{
    this->m_Active_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(DEFAULT_RESOLUTION), "GamePI Window", sf::Style::Fullscreen);
}