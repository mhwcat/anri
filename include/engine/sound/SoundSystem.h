#ifndef ANRI_SOUNDSYSTEM_H
#define ANRI_SOUNDSYSTEM_H


#include <map>
#include "SDL_mixer.h"

class SoundSystem
{
    public:
        SoundSystem();
        virtual ~SoundSystem();
        bool init();

        void playMusic(std::string id);
        void stopMusic(int fadeOutMs);
        void playSound(std::string id);

        void loadSound(std::string id, std::string path);
        void loadMusic(std::string id, std::string path);
        void unloadSound(std::string id);
        void unloadMusic(std::string id);
        void unloadAll();

        bool isMusicPlaying();

    private:
        std::map<std::string, Mix_Chunk*> sounds;
        std::map<std::string, Mix_Music*> musicTracks;

        std::string nowPlayingMusicTrackId;

        void clearNowPlaying();
};


#endif //ANRI_SOUNDSYSTEM_H
