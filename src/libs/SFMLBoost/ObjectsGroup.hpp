#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include <queue>
#include <vector>

#include "MacroFlags.hpp"

namespace SFMLBoost
{
    
    /// @brief Class to wrap objects to allow them to be in objects_group
    class Object_wrapper
   {
    protected:
        const sf::Drawable* object_drawable;
        std::shared_ptr<sf::Transformable> object_ptr;

    public:

        static bool CompareByZAxis(const Object_wrapper &obj1, const Object_wrapper &obj2);

        /// @brief Apparently SFML don't got any type of child parent position support
        /// * Oh mannn you know what happen next *
        /// @param object_ptr Shared ptr type to the object
        /// @param Object_draw Ptr to the object drawable form
        /// shared ptr cause i am not dumbass
        Object_wrapper(std::shared_ptr<sf::Transformable> object_ptr, const sf::Drawable* Object_draw);
        Object_wrapper();

        /* data */
        /// shared ptr to the object 
        /// The position of the object_ptr is meaningless  
         
        /// @brief Getting a window to draw on and drawing the object on it
        /// @param Window to draw on
        void Draw(sf::RenderWindow&);
        
        // the position is relative to the origin of the Group
        sf::Vector2f position;

        // the z position is relative to the objects in the group only
        int z_position;

        friend class ObjectsGroup;
    };

    // group of objects that have relative position and size
    class ObjectsGroup
    {
    private:
        
        /* data */
        sf::Vector2f OriginPosition;
        sf::Vector2f Position; 
        static bool Compare_shared_ptr_object_z(std::shared_ptr<Object_wrapper> obj_ptr1, std::shared_ptr<Object_wrapper> obj_ptr2 );

        int last_draw_group_count;

    public:

        std::vector<std::shared_ptr<SFMLBoost::Object_wrapper>> Objects_in_group;

        // gets:

        /// @brief returning the Position of the group
        sf::Vector2f GetPosition();

        /// @brief returning the origin of the group
        sf::Vector2f GetOrigin();
        
        // sets:

        /// @brief sets the position based on the window position
        /// @param the position of the group to the window 
        void SetPosition(sf::Vector2f);
        
        /// @brief sets the origin position of the group
        /// @param The New origin
        void SetOrigin(sf::Vector2f);

        // TODO: Optimizations
        /// @brief Drawing the group elements into the window
        /// @param The Window to draw on 
        void DrawGroup(sf::RenderWindow&);

        ObjectsGroup(/* args */);
        ~ObjectsGroup();
    };
}