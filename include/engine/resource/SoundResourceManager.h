#ifndef ANRI_SOUND_RESOURCE_MANAGER_H
#define ANRI_SOUND_RESOURCE_MANAGER_H

#include <engine/resource/ResourceManager.h>
#include <SDL_mixer.h>
#include <memory>

class SoundResourceManager : public ResourceManager 
{
    private:
        SoundResourceManager();

    protected:
        std::map<std::string, Mix_Chunk*> chunkResources;
        std::map<std::string, Mix_Music*> musicResources;

    public:
        SoundResourceManager(SoundResourceManager const&) = delete;
        SoundResourceManager(SoundResourceManager&&) = delete;
        virtual ~SoundResourceManager();
        static std::shared_ptr<SoundResourceManager> getInstance();

        void addChunk(std::string _key, Mix_Chunk* _val);
        void addChunk(std::string _key, std::string _path);
        void addMusic(std::string _key, Mix_Music* _val);
        void addMusic(std::string _key, std::string _path);
        void removeChunk(std::string _key);
        void removeMusic(std::string _key);
        Mix_Chunk* getChunk(std::string& _key);
        Mix_Music* getMusic(std::string& _key);
        void clear() override;
};


#endif
