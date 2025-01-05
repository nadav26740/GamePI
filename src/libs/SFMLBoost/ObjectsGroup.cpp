#include "ObjectsGroup.hpp"

namespace SFMLBoost
{
    Object_wrapper::Object_wrapper(std::shared_ptr<sf::Transformable> object_ptr, const sf::Drawable* Object_draw)
    {
        this->object_ptr = object_ptr;
        this->object_drawable = Object_draw;
        z_position = 0;

        #ifdef DEBUG
        std::cout << "New Object wrapped Memory addresses [transform, draw]: [" << object_ptr.get() << ", " << object_drawable << "]" << std::endl;
        #endif
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

    ObjectsGroup::ObjectsGroup(/* args */)
    {

    }

    ObjectsGroup::~ObjectsGroup()
    {
    }
}