#include "Scene.hpp"

Scene::Scene()
{

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


void Scene::Render_objects(std::shared_ptr<sf::RenderWindow> Scene_window)
{
    for (auto obj_itr : Objects_groups)
    {
        obj_itr.DrawGroup(*Scene_window);
    }

    for (auto drawable : m_drawables_objects)
    {
        Scene_window->draw(*drawable);
    }

    Scene_window->display();
}

std::vector<SFMLBoost::ObjectsGroup> *Scene::GetObjectsGroups()
{
    return &(this->Objects_groups);
}

