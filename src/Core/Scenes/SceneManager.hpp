#pragma once
#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <iostream>
#include <thread>
#include <memory>
#include <mutex>
#include <queue>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Scene.hpp"

#include "libs/cpp-colors/colors.hpp"
#include "libs/SFMLBoost.hpp"

#include "SystemDefines.hpp"
#include "MacroFlags.hpp"

/// Singleton Scene manager
/// @brief responsible to Load and control the scenes in runtime
class SceneManager
{
private:
    std::mutex m_scene_mutex;

    std::unique_ptr<Scene> m_Active_Scene;
    std::shared_ptr<sf::RenderWindow> m_Active_window;
    std::unique_ptr<sf::Thread> m_Scene_Thread;

    /* data */
    SceneManager(/* args */);
    SceneManager(const SceneManager&) = delete;
    void operator=(const SceneManager&) = delete;
    
    /// @brief Frame loader thread running automaticly 
    void FrameLoaderThread();
    
    /// @brief calling frame update on the scene
    bool running;
    
public:
    
    ~SceneManager();
    
    /// @return Pointer to the current Scene
    Scene* GetCurrentScene();
    
    /// @brief Getting scene pointer and Setting it as the active scene and running start function
    /// @param new_scene The scene to load (the pointer will be set into unique_ptr and will handle the delete memory)
    /// @attention Will relocate the new_scene memory
    /// @note if you call this function from scene make sure to call it with *detached* std::thread
    void SetCurrentScene(Scene* new_scene);

    /// @brief Too allow singleton we used this function to create single static object of this class
    /// @return the Intance of the current SceneManager
    static SceneManager* GetIntance();

    sf::RenderWindow* GetCurrentWindow();
};
#endif