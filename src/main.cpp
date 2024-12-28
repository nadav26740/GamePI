#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <thread>
#include "MacroFlags.hpp"
#include "libs/BoostSFML.hpp"

#define FRAME_LIMIT 59

#define ICON_PATH "../assets/GamePIicon.png"

#define GET_TIME std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now())

int main()
{

    sf::RenderWindow window(sf::VideoMode({640, 480}), "SFML works!");
    sf::Texture icon_texture;
    sf::Sprite icon_sprite;

    if (!icon_texture.loadFromFile(ICON_PATH))
    {
        std::cerr << "Failed to load icon Texture" << std::endl;
        exit(EXIT_FAILURE);
    }

    icon_texture.setSmooth(false);
    
    icon_sprite.setTexture(icon_texture);
    icon_sprite.scale(4.0f, 4.0f);
    SFMLBoost::CenterASprite(&icon_sprite, &window);
    

    // icon_sprite.setOrigin({icon_texture.getSize().x / 2.0f, icon_texture.getSize().y / 2.0f});
    // icon_sprite.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    //shape.setFillColor(sf::Color::Green);
    
#ifdef DEBUG
    auto last_epoch = GET_TIME;
    unsigned int frame_counter = 0;
#endif

    std::chrono::steady_clock::time_point next_frame;
    std::chrono::milliseconds interval = std::chrono::milliseconds(1000 / FRAME_LIMIT);


    while (window.isOpen())
    {   
        next_frame = std::chrono::steady_clock::now() + interval;
        sf::Event event;                // event varibale
        while (window.pollEvent(event)) // getting the current event
        {
            // getting the Current event
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            default:
                break;
            }
        }

        // rendering the window

        window.clear();
        window.clear(sf::Color(29, 180, 237));
        window.draw(icon_sprite);
        //window.draw(shape);
        window.display();

    #ifdef DEBUG
        frame_counter++;
        if (GET_TIME.time_since_epoch().count() - last_epoch.time_since_epoch().count() >= 1000 )
        {
            last_epoch = GET_TIME;
            std::cout << "[DEBUG (Main)]FPS: " << frame_counter << std::endl;
            frame_counter = 0;
        }
    #endif

        std::this_thread::sleep_until(next_frame);
    }
}