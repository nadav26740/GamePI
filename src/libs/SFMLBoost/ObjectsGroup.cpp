#include "ObjectsGroup.hpp"

namespace SFMLBoost
{
    bool Object_wrapper::CompareByZAxis(const Object_wrapper &obj1, const Object_wrapper &obj2)
    {
        return obj1.z_position < obj2.z_position;
    }

    Object_wrapper::Object_wrapper(std::shared_ptr<sf::Transformable> object_ptr, const sf::Drawable* Object_draw)
    {
        this->object_ptr = object_ptr;
        this->object_drawable = Object_draw;
        z_position = 0;
        
    }

    Object_wrapper::Object_wrapper()
    {
        z_position = 0;
        this->object_ptr.reset();
    }

    void Object_wrapper::Draw(sf::RenderWindow & win_Board)
    {
        win_Board.draw(*this->object_drawable);
    }

    bool ObjectsGroup::Compare_shared_ptr_object_z(std::shared_ptr<Object_wrapper> obj_ptr1, std::shared_ptr<Object_wrapper> obj_ptr2 )
    {
        return Object_wrapper::CompareByZAxis(*obj_ptr1.get(), *obj_ptr2.get());
    }

    sf::Vector2f ObjectsGroup::GetPosition()
    {
        return this->Position;
    }

    sf::Vector2f ObjectsGroup::GetOrigin()
    {
        return this->OriginPosition;
    }

    void ObjectsGroup::SetPosition(sf::Vector2f val)
    {
        this->Position = val;
    }

    void ObjectsGroup::SetOrigin(sf::Vector2f val)
    {
        this->OriginPosition = val;
    }

    void ObjectsGroup::DrawGroup(sf::RenderWindow& window)
    {
        std::vector<std::shared_ptr<Object_wrapper>> objects_to_draw(this->Objects_in_group);
        std::sort(objects_to_draw.begin(), objects_to_draw.end(), this->Compare_shared_ptr_object_z);
        
        for (auto itr = objects_to_draw.begin(); itr != objects_to_draw.end(); itr++)
        {
            itr->get()->Draw(window);
        }
    }

    ObjectsGroup::ObjectsGroup(/* args */)
    {
        
    }

    ObjectsGroup::~ObjectsGroup()
    {
    }
}