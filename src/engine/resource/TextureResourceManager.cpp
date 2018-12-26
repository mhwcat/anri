#include <engine/resource/ResourceManager.h>
#include <engine/resource/TextureResourceManager.h>
#include <engine/DebugPrint.h>
#include <SDL_image.h>

TextureResourceManager::TextureResourceManager()
{

}

TextureResourceManager::~TextureResourceManager() 
{
    ANRI_DE debugPrint("TextureResourceManager destructor fired.");
    clear();
}

std::shared_ptr<TextureResourceManager> TextureResourceManager::getInstance() 
{
    static std::shared_ptr<TextureResourceManager> instance(new TextureResourceManager);

    return instance;
}

void TextureResourceManager::clear()
{
    for(auto& item : resources)
    {
        SDL_DestroyTexture(item.second);
    }

    resources.clear();
}

void TextureResourceManager::add(std::string _key, SDL_Texture* _val)
{
    if(resources.find(_key) != resources.end()) 
    {
        debugPrint("Cannot add resource of key %s, already exists!", _key.c_str());
        return;
    }

    ANRI_DE debugPrint("Loading texture resource %s.", _key.c_str());
    
    resources[_key] = _val;
}

void TextureResourceManager::add(std::string _key, std::string _path, SDL_Renderer* _renderer)
{
    if(resources.find(_key) != resources.end()) 
    {
        debugPrint("Cannot add resource of key %s, already exists!", _key.c_str());
        return;
    }

    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(_path.c_str());
    if(loadedSurface == NULL)
    {
        debugPrint("Unable to load image %s! SDL_image Error: %s\n", _path.c_str(), IMG_GetError());
        return;
    }

    newTexture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
    if(newTexture == NULL)
    {
        debugPrint("Unable to create texture from %s! SDL Error: %s\n", _path.c_str(), SDL_GetError());
        SDL_FreeSurface(loadedSurface);

        return;
    }

    SDL_FreeSurface(loadedSurface);

    ANRI_DE debugPrint("Loading texture resource %s.", _key.c_str());

    resources[_key] = newTexture;
}

void TextureResourceManager::remove(std::string _key) 
{
    if(resources.find(_key) == resources.end()) 
    {
        debugPrint("Cannot remove resource of key %s, not exists!", _key.c_str());
        return;
    }

    ANRI_DE debugPrint("Removing texture resource %s.", _key.c_str());

    SDL_DestroyTexture(resources[_key]);
    resources.erase(_key);
}

SDL_Texture* TextureResourceManager::get(std::string& _key) 
{
    if(resources.find(_key) != resources.end()) 
    {
        return resources[_key];
    } 

    return nullptr;
}


