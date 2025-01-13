#include "AssetsCache.hpp"

AssetsCache::AssetsCache()
{
    
}

AssetsCache *AssetsCache::GetIntance()
{
    static AssetsCache INSTANCE;
    return &INSTANCE;
}