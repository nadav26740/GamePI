#pragma once
#ifndef CONFIGLOADER_HPP
#define CONFIGLOADER_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

// third party libs
#include "libs/nlohmann/json.hpp"
#include "libs/cpp-colors/colors.hpp"

// Compile debug/release flag
#include "MacroFlags.hpp"

// Defines
#define DEFAULT_CONFIG_LOADER_PATH std::string(std::getenv("HOME")) + "/.GamePI.config"
#define CONFIG_LOADER_VER 0.1
#define CONFIG_LOADER_VER_0_1

#define DEFAULT_DEFAULT_ASSETS_PATH std::string(std::getenv("HOME")) + "/GAMEPI/Assets"
#define DEFAULT_THEME_PATH ""
#define DEFAULT_EMULATOR_NAME "mgba"
#define DEFAULT_EMULATOR_FLAGS "-f"
#define DEFAULT_GAMES_DIRECTORY std::string(std::getenv("HOME")) + "/EMULATOR_GAMES"

#define KEY_DEFAULT_ASSETS_PATH "Assets_Directory"
#define KEY_THEME_PATH "Theme"
#define KEY_EMULATOR_NAME "Emulator_Name"
#define KEY_EMULATOR_FLAGS "Emulator_Flags"
#define KEY_GAMES_DIRECTORY "Games_Directory"
#define KEY_CONFIG_VER "Config_version"

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

    bool m_Config_Changed;

public:
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

    // Add Gets
    // Add sets
};

#endif

