#include "Scene.hpp"

Scene::Scene()
{

}

void Scene::Graphical_update(sf::RenderWindow& window_Handler)
{
    for (auto obj_itr : Objects_groups)
    {
        obj_itr.DrawGroup(window_Handler);
    }
}
