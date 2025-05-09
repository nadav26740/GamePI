#pragma once
#ifndef ASSETSCACHEMANAGER_HPP
#define ASSETSCACHEMANAGER_HPP

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
#define ASSETS_CONFIG_FILE_NAME "Theme.json"
#define CONFIG_FOLDER_NAME "Assets"

#define DEFAULT_TEXTURE_KEY "Error_texture"
#define DEFAULT_SOUNDBUFFER_KEY "Error_Sound"
#define DEFAULT_FONT_KEY "Default_Font"

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

    void Print_All_AssetsMap();

public:

    /// @brief will reset all the current loaded assets and unload them
    /// @warning This isn't a reverasble action!
    void HardResetAssets();

    /// @brief Too allow singleton we used this function to create single static object of this class
    /// @return the Intance of the current AssetsCache
    static AssetsCacheManager* GetIntance();

    // * Loaders

    /// @brief Getting theme folder path and loading assets as written in the json config
    /// @param dir_path theme folder path
    /// @attention Assets of the same type with similer paths will overwrite the loaded 
    /// @return Returning true if successed and false if failed!
    virtual bool LoadTheme(const std::filesystem::path dir_path = DEFAULT_ASSETS_PATH);

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
    virtual bool LoadSoundBuffer(const std::string& name, const std::filesystem::path& path);

    /// @brief Getting name and path and loading font to the cache with that name as key
    /// @param name that will saved in the font cache
    /// @param path the path of the font to load
    /// @return True if successed to load the font
    /// @attention Assets of the same type with similer paths will overwrite the loaded 
    virtual bool LoadFont(const std::string& name, const std::filesystem::path& path);
    
    // * Getters

    /// @brief Getting SoundBuffer from the mapped assets
    /// @param name of the soundbuffer to get
    /// @return Soundbuffer pointer or nullptr if soundbuffer not found
    virtual const sf::SoundBuffer* GetSoundBuffer(const std::string &name = DEFAULT_SOUNDBUFFER_KEY) const;

    /// @brief Getting SoundBuffer from the mapped assets
    /// @param name of the soundbuffer to get
    /// @return Soundbuffer const referance or nullptr if soundbuffer not found
    virtual const sf::SoundBuffer& GetSoundBuffer_ref(const std::string &name = DEFAULT_SOUNDBUFFER_KEY) const;

    
    /// @brief Getting Texture from the mapped assets
    /// @param name Key name of the Texture
    /// @return Texture Pointer or nullptr if Texture not found
    virtual const sf::Texture* GetTexture(const std::string &name = DEFAULT_TEXTURE_KEY) const;

    /// @brief Getting Texture from the mapped assets
    /// @param name Key name of the Texture
    /// @return Texture const referance or nullptr if Texture not found
    virtual const sf::Texture& GetTexture_ref(const std::string &name = DEFAULT_TEXTURE_KEY) const;


    /// @brief Getting Font from the mapped assets
    /// @param name Key name of the Font
    /// @return Font Pointer or nullptr if Texture not found
    virtual const sf::Font* GetFont(const std::string &name = DEFAULT_FONT_KEY) const;

    /// @brief Getting Font from the mapped assets
    /// @param name Key name of the Font
    /// @return Font referance or nullptr if Texture not found
    virtual const sf::Font& GetFont_ref(const std::string &name = DEFAULT_FONT_KEY) const;


    /// @todo Implement a status 
    virtual AssetsCacheStatus GetStatus() const;
};
#endif