#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <thread>
#include <filesystem>

#include "MacroFlags.hpp"

#include "libs/SFMLBoost/BoostSFML.hpp"
#include "libs/SFMLBoost/ObjectsGroup.hpp"

#include "Core/Scenes/SceneManager.hpp"
#include "Core/AssetsCacheManager.hpp"
#include "Core/ConfigLoader.hpp"

#include "Scenes/SplashScreen.hpp"

#define FRAME_LIMIT 30

#define ICON_PATH "../assets/GamePIicon.png"
#define FONT_PATH "../assets/GameFont.ttf"

#define GET_TIME std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now())

#define DEMO_LVL_2

#ifdef DEMO_LVL_2
int main()
{
    try 
    {
        std::cout << "================== RUNNING DEMO MAIN LVL2 ==================" << std::endl;
        AssetsCacheManager::GetIntance()->LoadTheme("../assets/");
        std::cout << cpp_colors::foreground::bright_green << "[MAIN] Texture Loaded!" << cpp_colors::style::reset << std::endl;
    
        SceneManager::GetIntance()->SetCurrentScene(new SplashScreen());
    
        //std::cout << std::_S_boolalpha << "Is Window Open: " << SceneManager::GetIntance()->GetCurrentWindow()->isOpen() << std::endl;
        while (SceneManager::GetIntance()->GetCurrentWindow()->isOpen())
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    catch (const std::exception& err)
    {
        std::cerr << "[MAIN ERROR CATCH] " << err.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...)
    {
        std::cerr << "[MAIN ERROR CATCH] Unknown error" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
#endif

#ifdef DEMO_LVL_1
int main()
{
    std::cout << "================== RUNNING DEMO MAIN ==================" << std::endl;
    
    sf::RenderWindow window(sf::VideoMode({640, 480}), "Demo GamePI!", sf::Style::Fullscreen);
    sf::Sprite icon_sprite;
    sf::Font Main_Font;
    sf::Vector2f temp;

    ConfigLoader::GetIntance()->SaveConfig();
    ConfigLoader::GetIntance()->LoadConfig();
    
    AssetsCacheManager::GetIntance()->LoadTheme("../assets/");

    sf::Text Logo_text("Demo Game PI", *AssetsCacheManager::GetIntance()->GetFont("GameFont"));

    AssetsCacheManager::GetIntance();
    
    icon_sprite.setTexture(*(AssetsCacheManager::GetIntance()->GetTexture("GamePI_Icon")));
    icon_sprite.scale(4.0f, 4.0f);
    SFMLBoost::CenterASprite(&icon_sprite, &window);

    Logo_text.setCharacterSize(35);

    SFMLBoost::CenterATransformable(&Logo_text, &window, Logo_text.getLocalBounds());
    temp = Logo_text.getPosition();
    temp.y += icon_sprite.getGlobalBounds().height / 2 + 20;
    Logo_text.setPosition(temp);

    // !TESTING THE OBJECT WRAPPER
    std::shared_ptr shared_sprite_tester = std::make_shared<sf::Sprite>();
    shared_sprite_tester->setTexture(*(AssetsCacheManager::GetIntance()->GetTexture("GamePI_Icon")));
    std::shared_ptr test_subject = std::make_shared<SFMLBoost::Object_wrapper>(shared_sprite_tester, shared_sprite_tester.get());

    std::shared_ptr circle_sprite = std::make_shared<sf::CircleShape>();
    circle_sprite->setRadius(5.0f);
    circle_sprite->setFillColor(sf::Color::Green);
    std::shared_ptr circle_wrapped = std::make_shared<SFMLBoost::Object_wrapper>(circle_sprite, circle_sprite.get());
    circle_wrapped->z_position = -1;

    // ! testing object grouper
    SFMLBoost::ObjectsGroup objects_group;
    objects_group.Objects_in_group.push_back(circle_wrapped);
    objects_group.Objects_in_group.push_back(test_subject);

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
            
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Right:
                    objects_group.SetPosition(objects_group.GetPosition() + sf::Vector2f({1, 0}));
                    break;
                
                case sf::Keyboard::Left:
                    objects_group.SetPosition(objects_group.GetPosition() + sf::Vector2f({-1, 0}));
                    break;
                
                case sf::Keyboard::Down:
                    objects_group.SetPosition(objects_group.GetPosition() + sf::Vector2f({0, 1}));
                    break;
                
                case sf::Keyboard::Up:
                    objects_group.SetPosition(objects_group.GetPosition() + sf::Vector2f({0, -1}));
                    break;
                        
                }
                break;

            default:
                break;
            }
        }

        // rendering the window

        window.clear();
        window.clear(sf::Color(29, 180, 237));
        window.draw(icon_sprite);
        window.draw(Logo_text);
        objects_group.DrawGroup(window);

        // window.draw(shape);
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

    return EXIT_SUCCESS;
}
#endif