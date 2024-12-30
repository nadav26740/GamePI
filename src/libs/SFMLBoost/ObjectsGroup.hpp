#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include "MacroFlags.hpp"

namespace SFMLBoost
{
    
    class Object_wrapper
   {
    private:
        const sf::Drawable* object_drawable;

    public:

        /// @brief Apparently SFML don't got any type of child parent position support
        /// * Oh mannn you know what happen next *
        /// @param object_ptr Shared ptr type to the object
        /// @param Object_draw Ptr to the object drawable form
        /// shared ptr cause i am not dumbass
        Object_wrapper(std::shared_ptr<sf::Transformable> object_ptr, const sf::Drawable* Object_draw);
        Object_wrapper();

        /* data */
        // shared ptr to the object 
         std::shared_ptr<sf::Transformable> object_ptr;
         
         /// @brief Getting a window to draw on and drawing the object on it
         /// @param Window to draw on
         void Draw(sf::RenderWindow&);
        
        // the position is related to the origin of the Group
         sf::Vector2f position;
         int z_position;
    };

    // todo:
    class ObjectsGroup
    {
    private:
        /* data */
        sf::Vector2f OriginPosition;
        sf::Vector2f Position; 

    public:
        // gets:

        // todo:
        /// @brief returning the Position of the group
        sf::Vector2f GetPosition();

        // todo:
        /// @brief returning the origin of the group
        sf::Vector2f GetOrigin();
        
        // sets:

        // todo:
        /// @brief sets the position based on the window position
        /// @param the position of the group to the window 
        void SetPosition(sf::Vector2f);
        
        // todo:
        /// @brief sets the origin position of the group
        /// @param The New origin
        void SetOrigin(sf::Vector2f);

        // todo:
        /// @brief Drawing the group elements into the window
        /// @param The Window to draw on 
        void DrawGroup(sf::Window);

        ObjectsGroup(/* args */);
        ~ObjectsGroup();
    };
}