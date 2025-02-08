#pragma once
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <string_view>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/// third party libs
#include "libs/cpp-colors/colors.hpp"
#include "libs/nlohmann/json.hpp"

#include "MacroFlags.hpp"

#define DEFAULT_ASSETS_PATH "../Assets"
#define CONFIG_FILE_NAME "assets.conf"
#define CONFIG_FOLDER_NAME "Assets"

// * TODO: #define DEFAULT_ASSETS_JSON_PATH "TODO"

// TODO: Add a default texture and sound in case missing asset

namespace SOUND_NAMES {
    constexpr std::string_view BEEP = "beep_sound";
}

/// @brief Struct to present the current status of the AssetsCacheManager
struct AssetsCacheStatus {
    unsigned int textures_loaded;
    unsigned int Sounds_loaded;
    unsigned int fonts_loaded;

    std::vector<std::string> Loaded_assets;
    std::vector<std::string> Failed_To_Load;

    std::vector<std::string> json_loaded;

    // inline std::ostream& operator<<(std::ostream& os, const AssetsCacheManager& cache);
};


/// class to make sure that assets won't be needed to load twice
/// Will platform as Assets memory manager
/// Singleton
class AssetsCacheManager
{
protected:
    // # Textures
    /// @brief Cache map of all the textures loaded
    std::map<std::filesystem::path, sf::Texture> m_Texture_map;

    /// @brief Cache map referance to the Texture map
    std::map<std::string, std::filesystem::path> m_Texture_keys_map;

    sf::Texture *Error_texture;

    // # Sounds
    /// @brief Cache map of all the sounds loaded
    std::map<std::filesystem::path, sf::SoundBuffer> m_SoundBuffer_map;

    /// @brief Cache map referance to the soundbuffer map
    std::map<std::string, std::filesystem::path> m_SoundBuffer_keys_map;

    /// @brief Error sound buffer if failed to load
    sf::SoundBuffer* Error_SoundBuffer;


    // # Fonts
    /// @brief Cache map of all the Fonts loaded
    std::map<std::filesystem::path, sf::Font> m_Fonts_map;

    /// @brief Cache map referance to the Fonts map
    std::map<std::string, std::filesystem::path> m_Fonts_keys_map;

    /// @brief Default font if failed to load
    sf::Font* Default_Font;

    AssetsCacheManager();

    // [Singleton] too make sure no one can create another object of this type
    AssetsCacheManager(AssetsCacheManager const&) = delete;       // Don't Implement
    void operator=(AssetsCacheManager const&) = delete;    // Don't implement

    std::vector<std::string> Failed_To_Load;
    std::vector<std::string> json_loaded;

    void print_all_texturemap();

public:    

    /// @brief Too allow singleton we used this function to create single static object of this class
    /// @return the Intance of the current AssetsCache
    static AssetsCacheManager* GetIntance();

    // * Loaders

    /// @todo Load Assets From jsonfile (Like texture pack [Theme]) 
    /// @brief Getting theme folder path and loading assets as written in the json config
    /// @param path theme folder path
    /// @attention Assets of the same type with similer paths will overwrite the loaded 
    virtual bool LoadTheme(const std::filesystem::path dir_path /* = DEFAULT_ASSETS_JSON_PATH */);

    /// @brief Getting name and path and loading texture to the cache with that name as key
    /// @param name that will saved in the texture cache
    /// @param path the path of the texture to load
    /// @return True if successed to load the texture
    /// @attention Assets of the same type with similer paths will overwrite the loaded 
    virtual bool LoadTexture(const std::string& name, const std::filesystem::path& path);
    
    /// @todo *!!!
    /// @brief Getting name and path and loading Soundbuffer to the cache with that name as key
    /// @param name the key name that will be saved in the soundbuffer cache
    /// @param path of the soundbuffer
    /// @return True if successed to load the soundbuffer
    /// @attention Assets of the same type with similer paths will overwrite the loaded 
    virtual void LoadSoundBuffer(const std::string& name, const std::filesystem::path& path);
    
    // * Getters

    /// @todo Get Soundbuffer pointer from the assets cache
    /// @brief Getting SoundBuffer from the mapped assets
    /// @param name of the soundbuffer to get
    /// @return Soundbuffer or nullptr if soundbuffer not found
    virtual const sf::SoundBuffer* GetSoundBuffer(const std::string &name);
    
    /// @brief Getting Texture from the mapped assets
    /// @param name of the Texture to get
    /// @return Texture or nullptr if Texture not found
    virtual const sf::Texture* GetTexture(const std::string &name);

    /// @todo Implement a status 
    virtual AssetsCacheStatus GetStatus();
};