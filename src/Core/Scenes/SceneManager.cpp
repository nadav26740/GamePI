#include "SceneManager.hpp"

Scene *SceneManager::GetCurrentScene()
{
    return m_Active_Scene.get();
}

void SceneManager::SetCurrentScene(Scene *new_scene)
{
    this->m_Active_Scene = std::unique_ptr<Scene>(std::move(new_scene));
    this->m_Active_Scene->Start(this->m_Active_window);

    if (this->m_Scene_Thread.get() == nullptr)
    {
        this->m_Active_window->setActive(false);

        this->m_Scene_Thread = std::make_unique<sf::Thread>([this] 
        {
            this->FrameLoaderThread();
        });
     
        this->m_Scene_Thread->launch();
    }  

    // m_Active_window->clear(sf::Color(29, 180, 237));
    
    std::cout << "Scene Loaded addr: " << this->m_Active_Scene.get() << std::endl;
}

SceneManager *SceneManager::GetIntance()
{
    static SceneManager INSTANCE;
    return &INSTANCE;
}

sf::RenderWindow* SceneManager::GetCurrentWindow()
{
    return this->m_Active_window.get();
}

SceneManager::SceneManager()
{
    this->m_Active_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(DEFAULT_RESOLUTION), "GamePI Window", sf::Style::Fullscreen);
    // this->m_Active_window->clear(sf::Color::Cyan);
    // limiting the frames by calculating the minimum gap between frames in miliseconds
    running = true;
}


void SceneManager::FrameLoaderThread()
{
    this->m_Active_window->setActive(true);

    std::chrono::milliseconds interval = std::chrono::milliseconds(1000 / FRAMES_LIMIT);
    std::cout << "[SceneManager::FrameLoaderThread] " <<  "Frame Loader starting | Interval - " << interval.count() << std::endl;
    bool IsSceneLoaded = false;

    while (this->m_Active_window->isOpen() && running)
    {
        std::chrono::steady_clock::time_point next_t_point = interval + std::chrono::steady_clock::now();
        // std::cout << "[SceneManager::FrameLoaderThread] Timestamp (" << std::chrono::steady_clock::now().time_since_epoch().count() << ")" << std::endl;
        IsSceneLoaded = this->m_Active_Scene.get() != nullptr;
        
        if (!IsSceneLoaded)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            cpp_colors::colorful_print("[ERROR (SceneManager::FrameLoaderThread)] Missing Scene!", cpp_colors::foreground::bright_red, std::cerr);
            continue;
        }

        if (this->m_Active_window.get() == nullptr)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            cpp_colors::colorful_print("[ERROR (SceneManager::FrameLoaderThread)] Window isn't loaded!", cpp_colors::foreground::bright_red, std::cerr);
            continue;
        }
    
        // calling logical update
        this->m_Active_Scene->Frame_update();
        
        // calling graphical update 
        this->m_Active_Scene->Graphical_update();
    
        // calling rendering function to the window
        // this->m_Active_window->clear(sf::Color::Red);
        // this->m_Active_window->display();
        this->m_Active_Scene->Render_objects(this->m_Active_window);


        // std::cout << "Full Rush" << std::endl;
        std::this_thread::sleep_until(next_t_point);
    }
    
}

SceneManager::~SceneManager()
{
    running = false;
    this->m_Scene_Thread->terminate();
}
