#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include "MacroFlags.hpp"

namespace SFMLBoost
{

    struct Object_wrapper
    {

        /// @brief Apparently SFML don't got any type of child parent position support
        /// * Oh mannn you know what happen next *
        /// @param object_ptr Shared ptr type to the object
        /// shared ptr cause i am not dumbass
        Object_wrapper(std::shared_ptr<sf::Transformable> object_ptr);

        /* data */
        // shared ptr to the object 
        std::shared_ptr<sf::Transformable> object_ptr;
        sf::Vector2f position;
        int z_position;
    };

    class ObjectsGroup
    {
    private:
        /* data */
    public:
        ObjectsGroup(/* args */);
        ~ObjectsGroup();
    };
}