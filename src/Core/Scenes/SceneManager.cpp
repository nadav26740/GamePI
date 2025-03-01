#include "SceneManager.hpp"

Scene *SceneManager::GetCurrentScene()
{
    return m_Active_Scene.get();
}

void SceneManager::SetCurrentScene(Scene *new_scene)
{
    // Lock guard to make sure the scene loader won't run while changing
    std::lock_guard<std::mutex> scene_guard(m_scene_mutex);

    // Setting the new scene
    this->m_Active_Scene = std::unique_ptr<Scene>(std::move(new_scene));
    this->m_Active_Scene->Start(this->m_Active_window);
    
#ifdef DEBUG
    std::cout << "[DEBUG (SceneManager::SetCurrentScene)]Scene Loaded " << this->m_Active_Scene.get() << std::endl;
#endif 

    if (this->m_Scene_Thread.get() == nullptr)
    {
        // Transfering the window ownership to the frameloader
        this->m_Active_window->setActive(false);

        this->m_Scene_Thread = std::make_unique<sf::Thread>([this] 
        {
            this->m_Active_window->setActive(true);

            this->FrameLoaderThread();
        });
     
        std::cout << "Scene Thread Loaded " << this->m_Scene_Thread.get() << std::endl;
        this->m_Scene_Thread->launch();
    }  

    // m_Active_window->clear(sf::Color(29, 180, 237));    
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
    running = true;
}


void SceneManager::FrameLoaderThread()
{
    // interval - the minimum gap between each frame
    std::chrono::milliseconds interval = std::chrono::milliseconds(1000 / FRAMES_LIMIT);
    std::cout << "[SceneManager::FrameLoaderThread] " <<  "Frame Loader starting | Interval - " << interval.count() << std::endl;
    bool IsSceneLoaded = false;

    while (this->m_Active_window.get() != nullptr && 
            this->m_Active_window->isOpen() && running)
    {
        // Locking the mutex of the scene 
        this->m_scene_mutex.lock();
        
        // calculating the next frame time point
        std::chrono::steady_clock::time_point next_t_point = interval + std::chrono::steady_clock::now();

        IsSceneLoaded = this->m_Active_Scene.get() != nullptr;
        
        // // Checking if scene loaded
        if (!IsSceneLoaded)
        {
            cpp_colors::colorful_print("[ERROR (SceneManager::FrameLoaderThread)] Missing Scene!", cpp_colors::foreground::bright_red, std::cerr);
            std::this_thread::sleep_for(std::chrono::seconds(1));
            continue;
        }

    
        // calling logical update
        this->m_Active_Scene->Frame_update();
        
        // calling graphical update 
        this->m_Active_Scene->Graphical_update();

        // Rendering the frame
        // ! takes most resources
        this->m_Active_Scene->Render_objects(this->m_Active_window);
    
        // Display the new frame
        this->m_Active_window->display();

        // * unlocking the mutex
        this->m_scene_mutex.unlock();

        // std::cout << "Full Rush" << std::endl;
        std::this_thread::sleep_until(next_t_point);
    }
    
}

SceneManager::~SceneManager()
{
    running = false;
    this->m_Scene_Thread->terminate();
}
