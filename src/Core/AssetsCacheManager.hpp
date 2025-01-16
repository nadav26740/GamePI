#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "libs/nlohmann/json.hpp"

#define CONFIG_FILE_NAME "assets.conf"
#define CONFIG_FOLDER_NAME "Assets"

// * TODO: #define DEFAULT_ASSETS_JSON_PATH "TODO"

// TODO: Add a default texture and sound in case missing asset

namespace SOUND_NAMES {
    constexpr std::string_view BEEP = "beep_sound";
}

/// class to make sure that assets won't be needed to load twice
/// Will platform as Assets memory manager
/// Singleton
class AssetsCacheManager
{
private:
    std::map<std::string, sf::Texture> m_Texture_map;
    std::map<std::string, sf::SoundBuffer> m_SoundBuffer_map;
    AssetsCacheManager();
    AssetsCacheManager(AssetsCacheManager const&) = delete;       // Don't Implement
    void operator=(AssetsCacheManager const&) = delete;    // Don't implement

public:    
    /// @brief Too allow singleton we used this function to create single static object of this class
    /// @return the Intance of the current AssetsCache
    static AssetsCacheManager* GetIntance();

    // TODO: Load Assets From jsonfile (Like texture pack [Theme])
    void LoadFromJson(const std::string& path /* = DEFAULT_ASSETS_JSON_PATH */);
    
    // TODO: Get Soundbuffer pointer from the assets cache
    const sf::SoundBuffer* GetSoundBuffer(const std::string &name);
    
    // TODO: Get Texture pointer from the assets cache
    const sf::Texture* GetTexture(const std::string &name);
};