#include "ObjectsGroup.hpp"

namespace SFMLBoost
{
    Object_wrapper::Object_wrapper(std::shared_ptr<sf::Transformable> object_ptr)
    {
        this->object_ptr = object_ptr;
    }

    ObjectsGroup::ObjectsGroup(/* args */)
    {
    }

    ObjectsGroup::~ObjectsGroup()
    {
    }
}