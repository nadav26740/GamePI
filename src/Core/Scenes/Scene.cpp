#include "Scene.hpp"

Scene::Scene()
{

}

void Scene::Start(sf::RenderWindow *Scene_window)
{
    this->m_Scene_window = Scene_window;

}

void Scene::Render_objects()
{
    for (auto obj_itr : Objects_groups)
    {
        obj_itr.DrawGroup(*this->m_Scene_window);
    }
}
