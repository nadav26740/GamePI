#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "CurrentMode.hpp"

#define GET_TIME std::chrono::steady_clock::now()

int main()
{
    
    sf::RenderWindow window(sf::VideoMode({200, 200}), "SFML works!");
    sf::CircleShape shape(100.0f);
    shape.setFillColor(sf::Color::Green);
    

    while (window.isOpen())
    {
        sf::Event event; // event varibale 
        while(window.pollEvent(event)) // getting the current event
        {
            // getting the Current event
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
                

        }

        // rendering the window
        window.clear();
        window.draw(shape);
        window.display();
        
    }
}