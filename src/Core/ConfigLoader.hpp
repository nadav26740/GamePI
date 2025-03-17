#pragma once
#ifndef CONFIGLOADER_HPP
#define CONFIGLOADER_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <regex>

// third party libs
#include "libs/nlohmann/json.hpp"
#include "libs/cpp-colors/colors.hpp"

// Compile debug/release flag
#include "MacroFlags.hpp"
#include "SystemDefines.hpp"

// Defines
#define DEFAULT_CONFIG_LOADER_PATH HOME_PATH + "/" + DATA_DIRECTORY + "/GamePI.config"
#define CONFIG_LOADER_VER 0.1
#define CONFIG_LOADER_VER_0_1

#define DEFAULT_DEFAULT_ASSETS_PATH HOME_PATH + "/" + DATA_DIRECTORY + "/Assets"
#define DEFAULT_THEME_PATH ""
#define DEFAULT_EMULATOR_NAME "mgba"
#define DEFAULT_EMULATOR_FLAGS "-f"
#define DEFAULT_GAMES_DIRECTORY HOME_PATH + "/" + DATA_DIRECTORY + "/EMULATOR_GAMES"
#define DEFAULT_GAMES_EXTENSION ".gba"

#define KEY_DEFAULT_ASSETS_PATH "Assets_Directory"
#define KEY_THEME_PATH "Theme"
#define KEY_EMULATOR_NAME "Emulator_Name"
#define KEY_EMULATOR_FLAGS "Emulator_Flags"
#define KEY_GAMES_DIRECTORY "Games_Directory"
#define KEY_CONFIG_VER "Config_version"
#define KEY_GAMES_EXTENSION "Games_Extension"

/// @brief class to make sure that assets won't be needed to load twice
/// Will platform as Assets memory manager
/// @attention Singleton class
class ConfigLoader
{
private:
    /// @brief Getting json field referance and key and inserting the json in that key to the field 
    /// @tparam T int, string, char, bool
    /// @param js json to load from
    /// @param field the field to insert the data in
    /// @param name key name
    template<typename T>
    void JsonIntoField(nlohmann::json& js, T& field, std::string name);

    // Creating Basic Config 
    ConfigLoader();

    // removing copy constructors
    ConfigLoader(ConfigLoader& other) = delete;
    void operator=(ConfigLoader& other) = delete;

protected:
    std::filesystem::path m_Theme_path;
    std::filesystem::path m_Default_assets_path;
    std::string m_Emulator_Flags;
    std::string m_Emulator_name;
    std::filesystem::path m_games_directory;
    std::string m_Games_Extension;

    bool m_Config_Changed;

public:
    // Setting default parameters of the config
    void ResetToDefault();

    /// @brief Too allow singleton we used this function to create single static object of this class
    /// @return the Intance of the current ConfigLoader
    static ConfigLoader* GetIntance();

    /// @todo this shit
    /// @brief Loading config file formated in json and saving data in the config
    /// @param config_path The Path to load
    /// @return True if successfuly loaded the file (excludning missing fields) 
    bool LoadConfig(const std::filesystem::path& config_path = DEFAULT_CONFIG_LOADER_PATH, bool Set_missings_to_default = true);
    
    /// @todo this shit
    /// @brief Creating/Overwritting the given path and creating json file contains the current config
    /// @param config_path The Path to save in
    /// @return True if successfuly saved the file
    bool SaveConfig(const std::filesystem::path& config_path = DEFAULT_CONFIG_LOADER_PATH);

    // * Getters
    
    /// @brief 
    /// @return 
    std::filesystem::path GetThemePath();
    
    /// @brief 
    /// @return 
    std::filesystem::path GetAssetsPath();
    
    /// @brief 
    /// @return 
    std::string GetEmulatorFlags();
    
    /// @brief 
    /// @return 
    std::string GetEmulatorName();
    
    /// @brief 
    /// @return 
    std::filesystem::path GetGamesDirectory();

    /// @brief 
    /// @return 
    std::string GetGamesExtension();

    // * Setters

    /// @brief 
    /// @param value 
    void SetThemePath(std::filesystem::path value);
    
    /// @brief 
    /// @param value 
    void SetAssetsPath(std::filesystem::path value);
    
    /// @brief 
    /// @param value 
    void SetEmulatorFlags(std::string value);
    
    /// @brief 
    /// @param value 
    void SetEmulatorName(std::string value);
    
    /// @brief 
    /// @param value 
    void SetGamesDirectory(std::filesystem::path value);

    /// @brief 
    /// @param value 
    void SetGamesExtension(std::string value);
};

#endif

