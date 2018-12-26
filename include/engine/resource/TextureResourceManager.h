#ifndef ANRI_TEXTURE_RESOURCE_MANAGER_H
#define ANRI_TEXTURE_RESOURCE_MANAGER_H

#include <engine/resource/ResourceManager.h>
#include <SDL.h>
#include <memory>

class TextureResourceManager : public ResourceManager 
{
    private:
        TextureResourceManager();

    protected:
        std::map<std::string, SDL_Texture*> resources;
    
    public:
        TextureResourceManager(TextureResourceManager const&) = delete;
        TextureResourceManager(TextureResourceManager&&) = delete;
        virtual ~TextureResourceManager();
        static std::shared_ptr<TextureResourceManager> getInstance();

        void add(std::string _key, SDL_Texture* _val);
        void add(std::string _key, std::string _val, SDL_Renderer* _renderer);
        void remove(std::string _key);
        SDL_Texture* get(std::string& _key);
        void clear() override;
};


#endif
