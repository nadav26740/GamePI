#include "Scene.hpp"

Scene::Scene()
{

}

void Scene::Graphical_update()
{
    for (auto obj_itr : Objects_groups)
    {
        obj_itr.DrawGroup(*this->Scene_window);
    }
}
