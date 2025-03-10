#include "Scene.hpp"

Scene::Scene()
{
    std::cout << cpp_colors::foreground::bright_green << "[Scene::Constructor] " << "Scene Created: " << this << cpp_colors::style::reset << std::endl;
}

Scene::~Scene()
{
    std::cout << cpp_colors::foreground::bright_magenta << "[Scene::Destructor] " << "Scene destroyed: " << this << cpp_colors::style::reset << std::endl;
}

void Scene::Start(std::shared_ptr<sf::RenderWindow> Scene_window)
{
    // Initialize or set up the scene with the given window
    // If you want to initialize other parts of the scene (e.g., objects), do so here
    // For example:
    Objects_groups.clear();
}

// void Scene::Frame_update()
// {
//     std::cout << "Frame parent Update";
// }

// void Scene::Graphical_update()
// {
// }

void Scene::Graphical_update(std::shared_ptr<sf::RenderWindow> Scene_window)
{
    auto itr = this->animations.begin();
    while (itr != animations.end())
    {
        if ((*itr)())
        {
            animations.erase(itr);
        }
        else
        {
            itr++;
        }
    }
}

void Scene::Render_objects(std::shared_ptr<sf::RenderWindow> Scene_window)
{
    Scene_window->clear(m_Background_Color);

    for (auto obj_itr : Objects_groups)
    {
        obj_itr->DrawGroup(*Scene_window);
    }

    for (auto drawable : m_drawables_objects)
    {
        Scene_window->draw(*drawable);
    }
}