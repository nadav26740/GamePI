#include "ConfigLoader.hpp"

void ConfigLoader::ResetToDefault()
{
    this->m_Default_assets_path = DEFAULT_DEFAULT_ASSETS_PATH;
    this->m_Emulator_Flags = DEFAULT_EMULATOR_FLAGS;
    this->m_Emulator_name = DEFAULT_EMULATOR_NAME;
    this->m_games_directory = DEFAULT_GAMES_DIRECTORY;
    this->m_Theme_path = DEFAULT_THEME_PATH;
 
    this->m_Config_Changed = false;
}


bool ConfigLoader::SaveConfig(const std::filesystem::path &config_path)
{
#ifdef DEBUG
    std::cout << "[ConfigLoader::SaveConfig] Saving config to " << config_path << std::endl;
#endif

     nlohmann::json js;
    js[KEY_CONFIG_VER] = CONFIG_LOADER_VER;
    js[KEY_DEFAULT_ASSETS_PATH] = m_Default_assets_path;
    js[KEY_EMULATOR_FLAGS] = m_Emulator_Flags;
    js[KEY_EMULATOR_NAME] = m_Emulator_name;
    js[KEY_THEME_PATH] = m_Theme_path;    
    js[KEY_GAMES_DIRECTORY] = m_games_directory;

    try
    {    
        std::ofstream output_file(config_path);
        if (!output_file.is_open())
        {
            cpp_colors::colorful_print("[ERROR (ConfigLoader::SaveConfig)] Failed To open Save file: " + config_path.string(), 
                                        cpp_colors::foreground::bright_red, std::cerr);
            return false;
        }

        output_file << js;
        output_file.close();
                
    }
    catch(const std::exception& e)
    {
        std::cerr << cpp_colors::foreground::bright_red << "[ERROR (ConfigLoader::SaveConfig)] Failed to Save: " << e.what() << cpp_colors::style::reset << std::endl;
        return false;
    }
    
    return true;
}

bool ConfigLoader::LoadConfig(const std::filesystem::path &config_path, bool Set_missings_to_default)
{
    std::cout << "[ConfigLoader::LoadConfig] Config Loader version: " << CONFIG_LOADER_VER << std::endl;
    std::cout << "[ConfigLoader::LoadConfig]Loading Config file: " << config_path << std::endl;

#ifdef DEBUG
    cpp_colors::colorful_print("[DEBUG (ConfigLoader::LoadConfig)] Loading config file: " + config_path.string(), cpp_colors::foreground::bright_blue);
#endif

    // checking file validation
    if (!std::filesystem::exists(config_path))
    {
        std::cerr << cpp_colors::foreground::bright_red << "[ERROR (ConfigLoader::LoadConfig)] " << config_path << " Not Exists!" << cpp_colors::style::reset << std::endl;
        return false;
    }

    // loading json
    nlohmann::json js;
    std::fstream config_file_handler;
    config_file_handler.open(config_path);

    // Checking if the file has been opened
    if (!config_file_handler.is_open())
    {
        cpp_colors::colorful_print("[ERROR (ConfigLoader::LoadConfig)] Failed To Open the Config File" + config_path.string(), 
                                        cpp_colors::foreground::bright_red, std::cerr);
        return false;
    }

    // Trying to parse the file into json format
    try
    {
        js = nlohmann::json::parse(config_file_handler);
    }
    catch(const std::exception& e)
    {
        cpp_colors::colorful_print("[ERROR (ConfigLoader::LoadConfig)] Failed To Read Config file: " + config_path.string() + ": " + e.what(), 
                                        cpp_colors::foreground::bright_red, std::cerr);
        return false;
    }


    config_file_handler.close();

    // reading data
    float version = 0.0;
    this->JsonIntoField(js, version, KEY_CONFIG_VER);
    std::cout << "[ConfigLoader::LoadConfig] Config Loaded Version: " 
        << (version ? std::to_string(version) : ((std::string)cpp_colors::foreground::bright_red + "Failed to load" + (std::string)cpp_colors::style::reset)) << std::endl;

    this->JsonIntoField(js, m_Default_assets_path, KEY_DEFAULT_ASSETS_PATH);
    this->JsonIntoField(js, m_games_directory, KEY_GAMES_DIRECTORY);
    this->JsonIntoField(js, m_Emulator_name, KEY_EMULATOR_NAME);
    this->JsonIntoField(js, m_Emulator_Flags, KEY_EMULATOR_FLAGS);
    this->JsonIntoField(js, m_Theme_path, KEY_THEME_PATH);

#ifdef DEBUG
    std::cout << "[DEBUG (ConfigLoader::LoadConfig)] Loaded Config" << js << std::endl;
#endif
    
return true;
}

// UNSAFE
template <typename T>
inline void ConfigLoader::JsonIntoField(nlohmann::json &js, T &field, std::string name)
{
    auto json_itr = js.find(name);
    if (json_itr == js.end())
    {
        cpp_colors::colorful_print("Failed To load " + name, cpp_colors::foreground::bright_red, std::cerr);
    }
    else
    {
        field = (T)json_itr.value();
    }
}

ConfigLoader::ConfigLoader()
{
    ResetToDefault();
}

ConfigLoader *ConfigLoader::GetIntance()
{
    static ConfigLoader intance;
    return &intance;
}
