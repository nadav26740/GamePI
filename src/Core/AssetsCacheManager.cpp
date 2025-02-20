#include "AssetsCacheManager.hpp"

AssetsCacheManager::AssetsCacheManager()
{
}

void AssetsCacheManager::Print_All_AssetsMap()
{

    std::cout << cpp_colors::foreground::bright_blue << std::endl << "=====================Textures=====================" << cpp_colors::style::reset << std::endl;
    for (auto itr = this->m_Texture_map.begin(); itr != this->m_Texture_map.end(); itr++)
    {
        std::cout << itr->first << ":" << &(itr->second) << std::endl;
    }
    std::cout << "=====================Textures=====================" << std::endl << std::endl;
    std::cout << "===================Textures_keys==================" << std::endl;
    for (auto itr = this->m_Texture_keys_map.begin(); itr != this->m_Texture_keys_map.end(); itr++)
    {
        std::cout << itr->first << ":" << itr->second << std::endl;
    }
    std::cout << "===================Textures_keys==================" << std::endl << std::endl;

    // TODO FONTS
    std::cout << cpp_colors::foreground::bright_blue << std::endl << "======================Fonts======================" << cpp_colors::style::reset << std::endl;
    for (auto itr = this->m_Fonts_map.begin(); itr != this->m_Fonts_map.end(); itr++)
    {
        std::cout << itr->first << ":" << &(itr->second) << std::endl;
    }
    std::cout << "=====================Fonts=====================" << std::endl << std::endl;
    std::cout << "===================Fonts_keys==================" << std::endl;
    for (auto itr = this->m_Fonts_keys_map.begin(); itr != this->m_Fonts_keys_map.end(); itr++)
    {
        std::cout << itr->first << ":" << itr->second << std::endl;
    }
    std::cout << "===================Fonts_keys==================" << std::endl << std::endl;

    std::cout << std::endl << cpp_colors::foreground::bright_red << "====================Failures===================" << cpp_colors::style::reset << std::endl;
    for (auto failed_str : this->Failed_To_Load)
    {
        std::cout << failed_str << std::endl;
    }
    std::cout << cpp_colors::foreground::bright_red << "====================Failures===================" << cpp_colors::style::reset << std::endl << std::endl;
    // TODO SOUNDS

    std::cout << cpp_colors::foreground::bright_blue << "===============Assets Cache Manager===============" << cpp_colors::style::reset << std::endl;
}

void AssetsCacheManager::HardResetAssets()
{
    this->m_Fonts_keys_map.clear();
    this->m_Fonts_map.clear();
    this->m_SoundBuffer_keys_map.clear();
    this->m_SoundBuffer_map.clear();
    this->m_Texture_keys_map.clear();
    this->m_Texture_map.clear();

    this->Default_Font = nullptr;
    this->Error_SoundBuffer = nullptr;
    this->Error_texture = nullptr;
}

AssetsCacheManager *AssetsCacheManager::GetIntance()
{
    static AssetsCacheManager INSTANCE;
    return &INSTANCE;
}

bool AssetsCacheManager::LoadTheme(std::filesystem::path dir_path)
{
    std::cout << cpp_colors::foreground::bright_blue << "[Assets Cache Manager] Trying to load theme path [" << dir_path << "]" << cpp_colors::style::reset << std::endl;

    // Checking path
    if (!std::filesystem::exists(dir_path))
    {
        std::cerr << cpp_colors::foreground::bright_red << "[ERROR (Assets Cache Manager)] Failed to Load Theme - " << dir_path << " Isn't a exists!" << std::endl;
        return false;
    }

    if (!std::filesystem::is_directory(dir_path))
    {
        std::cerr << cpp_colors::foreground::bright_red << "[ERROR (Assets Cache Manager)] Failed to Load Theme - " << dir_path << " Isn't a directory" << std::endl;
        return false;
    }

    // looking for the Theme.json file (Config file)
    std::filesystem::path config_path = dir_path.string() + "/Theme.json";

#ifdef DEBUG
    cpp_colors::colorful_print( "[DEBUG (Assets Cache Manager)] Looking For Theme.json", cpp_colors::foreground::blue);
    cpp_colors::colorful_print( "[DEBUG (Assets Cache Manager)] path checking: " + config_path.string(), cpp_colors::foreground::blue);
#endif

    // Checking path
    if (!std::filesystem::exists(config_path))
    {
        std::cerr << cpp_colors::foreground::bright_red << "[ERROR (Assets Cache Manager)] Failed to Load Theme - " << config_path << " missing!" << std::endl;
        return false;
    }

    // Loading json
    std::ifstream json_file(config_path);
    nlohmann::json theme_config = nlohmann::json::parse(json_file);
    
    std::string asset_name;
    std::filesystem::path asset_path;
    std::vector<std::map<std::string, std::string>> objects_arrays;

    json_file.close();

    double version = theme_config.at("Metadata").at("Theme_Version");
    std::string theme_name = theme_config.at("Metadata").at("Theme_name");

    json_loaded.emplace_back(theme_name + ": " + config_path.string() + " | Ver: " + std::to_string(version));
    
#ifdef DEBUG
    cpp_colors::colorful_print("[DEBUG (Assets Cache Manager] Loaded config: name: " + theme_name + " Ver: " + std::to_string(version), cpp_colors::foreground::bright_blue);
#endif

    // Loading Textures
    for (auto &obj : theme_config.at("Textures").items())
    {
        asset_name = obj.value()["name"];
        asset_path = dir_path.string() + "/" + (std::string)obj.value()["path"];
        this->LoadTexture(asset_name, asset_path);
    }

    // Loading Fonts
    for (auto &obj : theme_config.at("Fonts").items())
    {
        asset_name = obj.value()["name"];
        asset_path = dir_path.string() + "/" + (std::string)obj.value()["path"];
        this->LoadFont(asset_name, asset_path);
    }
    
    // Sounds
    for (auto &obj : theme_config.at("Sounds").items())
    {
        asset_name = obj.value()["name"];
        asset_path = dir_path.string() + "/" + (std::string)obj.value()["path"];
        this->LoadSoundBuffer(asset_name, asset_path);
    }


    Print_All_AssetsMap();

    return true;
}

const sf::SoundBuffer *AssetsCacheManager::GetSoundBuffer(const std::string &name)
{
    std::cout << "AssetsCacheManager::GetSoundBuffer [WIP]" << std::endl;
    return nullptr;
}

const sf::Texture *AssetsCacheManager::GetTexture(const std::string &name)
{
#ifdef DEBUG
    std::cout << "[DEBUG (Assets Cache Manager)] Trying to get Texture: " << name << std::endl;
#endif

    auto key_itr = this->m_Texture_keys_map.find(name);
    if (key_itr == this->m_Texture_keys_map.end())
    {
        cpp_colors::colorful_print("[ERROR (Assets Cache Manager)] Failed to find Texture key:" + name, cpp_colors::foreground::bright_red, std::cerr);
        cpp_colors::colorful_print("[ERROR (Assets Cache Manager)] Loading Error Texture:" + name, cpp_colors::foreground::bright_red, std::cerr);
        return this->Error_texture;
    }

    auto Font_itr = this->m_Texture_map.find(key_itr->second);

#ifdef DEBUG
    std::cout << "[DEBUG (Assets Cache Manager)] Getting Texture (" << key_itr->first << ": " << key_itr->second << ")" << std::endl;
#endif

    if (Font_itr == this->m_Texture_map.end())
    {
        cpp_colors::colorful_print("[ERROR (Assets Cache Manager)] Failed to get Texture: " + name, cpp_colors::foreground::bright_red, std::cerr);
        cpp_colors::colorful_print("[ERROR (Assets Cache Manager)] Loading Error Texture:" + name, cpp_colors::foreground::bright_red, std::cerr);
        return this->Error_texture;
    }

    return &(Font_itr->second);
}

bool AssetsCacheManager::LoadTexture(const std::string &name, const std::filesystem::path &path)
{

    // Checking if texute in path hasn't been loaded before
    if (this->m_Texture_map.find(path) == this->m_Texture_map.end())
    {
        sf::Texture loaded_texture;
        if (!loaded_texture.loadFromFile(path))
        {
            cpp_colors::colorful_print("[ERROR (Assets Cache Manager)] Failed To Load Texture " + path.string(), cpp_colors::foreground::bright_red, std::cerr);
            this->Failed_To_Load.emplace_back("[Texture]" +  name + ": " + path.string());     
            return false;
        }
    
    
        this->m_Texture_map[path] = loaded_texture;        
    }
    
    this->m_Texture_keys_map[name] = path;
    std::cout << "[Assets Cache Manager] Loading: " << name << ": " << path << std::endl;

    // Checking if default error texture
    if (name == "Error_texture")
    {
        this->Error_texture = &this->m_Texture_map[path];
        cpp_colors::colorful_print("[AssetsCacheManager] Error Texture Loaded", cpp_colors::foreground::bright_green, std::cout);
    }

#ifdef DEBUG
    std::cout << "[Debug (Assets Cache Manager)] Loaded Texture: " << path << ": " << &this->m_Texture_map[path] << std::endl;
    //Print_All_AssetsMap();
#endif

    return true;
}

bool AssetsCacheManager::LoadSoundBuffer(const std::string &name, const std::filesystem::path &path)
{
    // TODO
    return false;
}

bool AssetsCacheManager::LoadFont(const std::string &name, const std::filesystem::path &path)
{

    // Checking if path hasn't been loaded before
    if (this->m_Fonts_map.find(path) == this->m_Fonts_map.end())
    {
        sf::Font _font;
        if (!_font.loadFromFile(path))
        {
            cpp_colors::colorful_print("[ERROR (Assets Cache Manager)] Failed To Load Font " + path.string(), cpp_colors::foreground::bright_red, std::cerr);
            this->Failed_To_Load.emplace_back("[Font]" + name + ": " + path.string());     
            return false;
        }
    
        this->m_Fonts_map[path] = _font;
    }
    
    this->m_Fonts_keys_map[name] = path;

    // Checking if default error texture
    if (name == "Default_Font")
    {
        this->Default_Font = &this->m_Fonts_map[path];
        cpp_colors::colorful_print("[AssetsCacheManager] Default Font Loaded", cpp_colors::foreground::bright_green, std::cout);
    }

#ifdef DEBUG
    std::cout << "[Debug (Assets Cache Manager)] Loaded Font: " << path << ": " << &this->m_Fonts_map[path] << std::endl;
#endif

    return true;
}

const sf::Font *AssetsCacheManager::GetFont(const std::string &name)
{
    #ifdef DEBUG
    std::cout << "[DEBUG (Assets Cache Manager)] Trying to get Font: " << name << std::endl;
#endif

    auto key_itr = this->m_Fonts_keys_map.find(name);
    if (key_itr == this->m_Fonts_keys_map.end())
    {
        cpp_colors::colorful_print("[ERROR (Assets Cache Manager)] Failed to find Font key:" + name, cpp_colors::foreground::bright_red, std::cerr);
        cpp_colors::colorful_print("[ERROR (Assets Cache Manager)] Loading Error Font:" + name, cpp_colors::foreground::bright_red, std::cerr);
        return this->Default_Font;
    }

    auto Font_itr = this->m_Fonts_map.find(key_itr->second);

#ifdef DEBUG
    std::cout << "[DEBUG (Assets Cache Manager)] Getting Font (" << key_itr->first << ": " << key_itr->second << ")" << std::endl;
#endif

    if (Font_itr == this->m_Fonts_map.end())
    {
        cpp_colors::colorful_print("[ERROR (Assets Cache Manager)] Failed to get Font: " + name, cpp_colors::foreground::bright_red, std::cerr);
        cpp_colors::colorful_print("[ERROR (Assets Cache Manager)] Loading Error Font:" + name, cpp_colors::foreground::bright_red, std::cerr);
        return this->Default_Font;
    }

    return &(Font_itr->second);
}

AssetsCacheStatus AssetsCacheManager::GetStatus()
{
    std::cout << "AssetsCacheManager::GetStatus [WIP]" << std::endl;
    AssetsCacheStatus status;
    status.Failed_To_Load = this->Failed_To_Load;

    status.fonts_loaded = m_Fonts_map.size();
    status.Sounds_loaded = m_SoundBuffer_map.size();
    status.textures_loaded = m_Texture_map.size();
    
    for (auto itr = this->m_Texture_keys_map.begin(); itr != this->m_Texture_keys_map.end(); itr++)
    {
        status.Loaded_assets.emplace_back("[Texture]" + itr->first + ":" + itr->second.string() );
    }
    
    for (auto itr = this->m_SoundBuffer_keys_map.begin(); itr != this->m_SoundBuffer_keys_map.end(); itr++)
    {
        status.Loaded_assets.emplace_back("[Soundbuffer]" + itr->first + ":" + itr->second.string() );
    }
    
    for (auto itr = this->m_Fonts_keys_map.begin(); itr != this->m_Fonts_keys_map.end(); itr++)
    {
        status.Loaded_assets.emplace_back("[Font]" + itr->first + ":" + itr->second.string() );
    }

    status.json_loaded = this->json_loaded;

    return status;
}
