#include "AssetsCacheManager.hpp"

AssetsCacheManager::AssetsCacheManager()
{
    
}

AssetsCacheManager *AssetsCacheManager::GetIntance()
{
    static AssetsCacheManager INSTANCE;
    return &INSTANCE;
}