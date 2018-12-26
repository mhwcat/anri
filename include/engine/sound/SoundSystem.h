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

        void playMusic(std::string id, int volume, int loops);
        void stopMusic(int fadeOutMs);
        void playSound(std::string id, int volume, int loops);

        bool isMusicPlaying();

    private:
        std::string nowPlayingMusicTrackId;

        void clearNowPlaying();
};


#endif //ANRI_SOUNDSYSTEM_H
