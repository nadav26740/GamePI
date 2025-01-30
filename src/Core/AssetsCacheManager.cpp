#include "AssetsCacheManager.hpp"

AssetsCacheManager::AssetsCacheManager()
{
    
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
    std::cout << "AssetsCacheManager::GetTexture [WIP]" << std::endl;
    return nullptr;
}

AssetsCacheStatus AssetsCacheManager::GetStatus()
{
    std::cout << "AssetsCacheManager::GetStatus [WIP]" << std::endl;
    return AssetsCacheStatus();
}
