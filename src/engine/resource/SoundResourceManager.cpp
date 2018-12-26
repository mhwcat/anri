#include <engine/resource/ResourceManager.h>
#include <engine/resource/SoundResourceManager.h>
#include <engine/DebugPrint.h>
#include <SDL_mixer.h>

SoundResourceManager::SoundResourceManager()
{

}

SoundResourceManager::~SoundResourceManager() 
{
    ANRI_DE debugPrint("SoundResourceManager destructor fired.");
    clear();
}

std::shared_ptr<SoundResourceManager> SoundResourceManager::getInstance() 
{
    static std::shared_ptr<SoundResourceManager> instance(new SoundResourceManager);

    return instance;
}

void SoundResourceManager::clear()
{
    for(auto& item : chunkResources)
    {
        Mix_FreeChunk(item.second);
    }

    for(auto& item : musicResources)
    {
        Mix_FreeMusic(item.second);
    }

    chunkResources.clear();
    musicResources.clear();
}

void SoundResourceManager::addChunk(std::string _key, Mix_Chunk* _val)
{
    if(chunkResources.find(_key) != chunkResources.end()) 
    {
        debugPrint("Cannot add resource of key %s, already exists!", _key.c_str());
        return;
    }

    ANRI_DE debugPrint("Loading sound resource %s.", _key.c_str());
    
    chunkResources[_key] = _val;
}

void SoundResourceManager::addChunk(std::string _key, std::string _path)
{
    if(chunkResources.find(_key) != chunkResources.end()) 
    {
        debugPrint("Cannot add resource of key %s, already exists!", _key.c_str());
        return;
    }

    Mix_Chunk* chunk = Mix_LoadWAV(_path.c_str());
    if(chunk == nullptr)
    {
        debugPrint("Failed to load sound %s! SDL_mixer error: %s", _path.c_str(), Mix_GetError());
        return;
    }

    ANRI_DE debugPrint("Loading sound resource %s.", _key.c_str());

    chunkResources[_key] = chunk;
}

void SoundResourceManager::addMusic(std::string _key, Mix_Music* _val)
{
    if(musicResources.find(_key) != musicResources.end()) 
    {
        debugPrint("Cannot add resource of key %s, already exists!", _key.c_str());
        return;
    }

    ANRI_DE debugPrint("Loading music resource %s.", _key.c_str());
    
    musicResources[_key] = _val;
}

void SoundResourceManager::addMusic(std::string _key, std::string _path)
{
    if(musicResources.find(_key) != musicResources.end()) 
    {
        debugPrint("Cannot add resource of key %s, already exists!", _key.c_str());
        return;
    }

    Mix_Music* music = Mix_LoadMUS(_path.c_str());
    if(music == nullptr)
    {
        debugPrint("Failed to load sound %s! SDL_mixer error: %s", _path.c_str(), Mix_GetError());
        return;
    }

    ANRI_DE debugPrint("Loading music resource %s.", _key.c_str());

    musicResources[_key] = music;
}

void SoundResourceManager::removeChunk(std::string _key) 
{
    if(chunkResources.find(_key) == chunkResources.end()) 
    {
        debugPrint("Cannot remove resource of key %s, not exists!", _key.c_str());
        return;
    }

    ANRI_DE debugPrint("Removing sound resource %s.", _key.c_str());

    Mix_FreeChunk(chunkResources[_key]);
    chunkResources.erase(_key);
}

void SoundResourceManager::removeMusic(std::string _key) 
{
    if(musicResources.find(_key) == musicResources.end()) 
    {
        debugPrint("Cannot remove resource of key %s, not exists!", _key.c_str());
        return;
    }

    ANRI_DE debugPrint("Removing music resource %s.", _key.c_str());

    Mix_FreeMusic(musicResources[_key]);
    musicResources.erase(_key);
}

Mix_Chunk* SoundResourceManager::getChunk(std::string& _key) 
{
    if(chunkResources.find(_key) != chunkResources.end()) 
    {
        return chunkResources[_key];
    } 

    return nullptr;
}

Mix_Music* SoundResourceManager::getMusic(std::string& _key) 
{
    if(musicResources.find(_key) != musicResources.end()) 
    {
        return musicResources[_key];
    } 

    return nullptr;
}


