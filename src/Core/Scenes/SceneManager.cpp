#include "SceneManager.hpp"

Scene *SceneManager::GetCurrentScene()
{
    return m_Active_Scene.get();
}

void SceneManager::SetCurrentScene(Scene *new_scene)
{
    this->m_Active_Scene = std::make_unique<Scene>(std::move(new_scene));
    this->m_Active_Scene->Start(this->m_Active_window.get());
}

SceneManager *SceneManager::GetIntance()
{
    static SceneManager INSTANCE;
    return &INSTANCE;
}

SceneManager::SceneManager()
{
    this->m_Active_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(DEFAULT_RESOLUTION), "GamePI Window", sf::Style::Fullscreen);
    
    // limiting the frames by calculating the minimum gap between frames in miliseconds
    running = true;
}


void SceneManager::FrameLoaderThread()
{
    std::chrono::milliseconds interval = std::chrono::milliseconds(1000 / FRAMES_LIMIT);
    
    while (running)
    {
        std::chrono::steady_clock::time_point next_t_point = interval + std::chrono::steady_clock::now();
        static bool IsSceneLoaded = this->m_Active_Scene.get() != nullptr;
        if (!IsSceneLoaded)
        {
            cpp_colors::colorful_print("[ERROR (SceneManager::FrameLoaderThread)] Missing Scene!", cpp_colors::foreground::bright_red, std::cerr);
        }
    
        // calling logical update
        this->m_Active_Scene->Frame_update();
        
        // calling graphical update 
        this->m_Active_Scene->Graphical_update();
    
        // calling rendering function to the window
        this->m_Active_Scene->Render_objects();
        std::this_thread::sleep_until(next_t_point);
    }
    
}

SceneManager::~SceneManager()
{
    running = false;
}
