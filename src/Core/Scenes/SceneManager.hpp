#pragma once
#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <iostream>
#include <thread>
#include <memory>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Scene.hpp"

#include "libs/cpp-colors/colors.hpp"
#include "libs/SFMLBoost.hpp"

#include "SystemDefines.hpp"

/// Singleton Scene manager
/// @brief responsible to Load and control the scenes in runtime
class SceneManager
{
private:
    std::unique_ptr<Scene> m_Active_Scene;
    std::shared_ptr<sf::RenderWindow> m_Active_window;
    std::unique_ptr<sf::Thread> m_Scene_Thread;

    /* data */
    SceneManager(/* args */);
    SceneManager(const SceneManager&) = delete;
    void operator=(const SceneManager&) = delete;
    
    void FrameLoaderThread();
    
    /// @brief calling frame update on the scene
    bool running;
    
public:
    
    ~SceneManager();
    
    /// @return Pointer to the current Scene
    Scene* GetCurrentScene();
    
    /// @brief Frame loader thread running automaticly 
    
    /// @brief Getting scene pointer and Setting it as the active scene and running start function
    /// @param new_scene The scene to load (the pointer will be set into unique_ptr and will handle the delete memory)
    /// @note Will relocate the new_scene memory
    void SetCurrentScene(Scene* new_scene);

    /// @brief Too allow singleton we used this function to create single static object of this class
    /// @return the Intance of the current SceneManager
    static SceneManager* GetIntance();

    sf::RenderWindow* GetCurrentWindow();
};
#endif