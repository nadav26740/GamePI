#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "CurrentMode.hpp"

#define GET_TIME std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()).time_since_epoch()

int main()
{
    
    sf::RenderWindow window(sf::VideoMode({640, 480}), "SFML works!");
    sf::CircleShape shape(100.0f);
    shape.setFillColor(sf::Color::Green);
    
    window.setPosition({0,0});

    while (window.isOpen())
    {
        sf::Event event; // event varibale 
        while(window.pollEvent(event)) // getting the current event
        {
            // getting the Current event
        #ifdef DEBUG
            auto event_start_pt = GET_TIME;
        #endif

            switch (event.type)
            {
                case sf::Event::Closed:

                    window.close();
                    break;
                
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Space)
                    {
                        shape.setRadius(70.0f);
                    }

                default:
                    break;
            }

        #ifdef DEBUG
            std::cout << "[(main.cpp) DEBUG] Event Calculation time: " << GET_TIME.count() - event_start_pt.count() << "ms" << std::endl;
        #endif
                

        }

        // rendering the window
        window.clear();
        window.draw(shape);
        window.display();
        
    }
}