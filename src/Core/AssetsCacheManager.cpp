#include "AssetsCacheManager.hpp"

AssetsCacheManager::AssetsCacheManager()
{
    
}

void AssetsCacheManager::print_all_texturemap()
{

    std::cout << "=====================Textures=====================" << std::endl;
    for (auto itr = this->m_Texture_map.begin(); itr != this->m_Texture_map.end(); itr++)
    {
        std::cout << itr->first << ":" << &(itr->second) << std::endl;
    }
    std::cout << "=====================Textures=====================" << std::endl;
    std::cout << "===================Textures_keys==================" << std::endl;
    for (auto itr = this->m_Texture_keys_map.begin(); itr != this->m_Texture_keys_map.end(); itr++)
    {
        std::cout << itr->first << ":" << itr->second << std::endl;
    }
    std::cout << "==================================================" << std::endl;

}

AssetsCacheManager *AssetsCacheManager::GetIntance()
{
    static AssetsCacheManager INSTANCE;
    return &INSTANCE;
}

void AssetsCacheManager::LoadFromJson(const std::string &path)
{
    std::cout << "AssetsCacheManager::LoadFromJson [WIP]" << std::endl;
}

const sf::SoundBuffer *AssetsCacheManager::GetSoundBuffer(const std::string &name)
{
    std::cout << "AssetsCacheManager::GetSoundBuffer [WIP]" << std::endl;
    return nullptr;
}

const sf::Texture *AssetsCacheManager::GetTexture(const std::string &name)
{
    auto key_itr = this->m_Texture_keys_map.find(name);
    if (key_itr == this->m_Fonts_keys_map.end())
    {
        std::cerr << "[ERROR (Assets Cache Manager)] Failed to find Texture key: " << name << std::endl;
        return this->Error_texture.get();
    }

    auto texture_itr = this->m_Texture_map.find(key_itr->second);

#ifdef DEBUG
    std::cout << "Getting Texture (" << key_itr->first << ": " << key_itr->second << ")" << std::endl;
#endif

    if (texture_itr == this->m_Texture_map.end())
    {
        std::cerr << "[ERROR (Assets Cache Manager)] Failed to get Texture: " << name << std::endl;
        return this->Error_texture.get();
    }  

    return &(texture_itr->second);
}

bool AssetsCacheManager::LoadTexture(const std::string &name, const std::filesystem::path &path)
{
    sf::Texture loaded_texture;
    if (!loaded_texture.loadFromFile(path))
    {
        std::cerr << "[ERROR (Assets Cache Manager)] Failed To Load Texture " << path << std::endl;
        this->Failed_To_Load.emplace_back(name + ": " + path.string());
        return false;
    }

    this->m_Texture_map[path] = loaded_texture;
    this->m_Texture_keys_map[name] = path;
    
#ifdef DEBUG
     std::cout << "Loaded Texture: " << path << ": " << &this->m_Texture_map[path] << std::endl;
     print_all_texturemap();
#endif

    return true;
}

void AssetsCacheManager::LoadSoundBuffer(const std::string &name, const std::filesystem::path &path)
{
    // TODO
}

AssetsCacheStatus AssetsCacheManager::GetStatus()
{
    std::cout << "AssetsCacheManager::GetStatus [WIP]" << std::endl;
    AssetsCacheStatus status;
    return status;
}
