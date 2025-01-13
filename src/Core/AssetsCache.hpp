#pragma once
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <map>

#include "libs/nlohmann/json.hpp"
#define CONFIG_FILE_NAME "assets.conf"
#define CONFIG_FOLDER_NAME "Assets"

class AssetsCache
{
private:
    std::map<std::string, sf::Texture> m_Texture_map;
    std::map<std::string, sf::SoundBuffer> m_SoundBuffer_map;
    AssetsCache();
    AssetsCache(AssetsCache const&) = delete;       // Don't Implement
    void operator=(AssetsCache const&) = delete;    // Don't implement


public:
    //sf::SoundBuffer* LoadSoundBuffer(std::string name);
    static AssetsCache* GetIntance();
};