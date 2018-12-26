#include <engine/DebugPrint.h>
#include <engine/sound/SoundSystem.h>
#include <engine/resource/SoundResourceManager.h>

#include "SDL.h"

SoundSystem::SoundSystem()
{
    ANRI_DE debugPrint("Initializing SoundSystem!");

    clearNowPlaying();
}

SoundSystem::~SoundSystem()
{
    ANRI_DE debugPrint("SoundSystem destructor fired!");

    if(isMusicPlaying())
    {
        Mix_HaltMusic();
    }

    Mix_CloseAudio();
}

bool SoundSystem::init()
{
    ANRI_DE debugPrint("Initializing SDL Audio subsystem...");
    if(SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
    {
        debugPrint("SDL Audio could not initialize! SDL error: %s", SDL_GetError());
        return false;
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        debugPrint("SDL_mixer could not initialize! SDL_mixer error: %s", Mix_GetError());
        return false;
    }

    Mix_AllocateChannels(16);

    return true;
}

void SoundSystem::playSound(std::string _resourceName, int volume, int loops)
{
    Mix_Chunk* sound = SoundResourceManager::getInstance()->getChunk(_resourceName);

    if(sound == nullptr)
    {
        debugPrint("Sound %s not loaded!", _resourceName.c_str());
        return;
    }

    Mix_VolumeChunk(sound, volume);
    Mix_PlayChannel(-1, sound, loops);
}

void SoundSystem::playMusic(std::string _resourceName, int volume, int loops)
{
    Mix_Music* music = SoundResourceManager::getInstance()->getMusic(_resourceName);

    if(music == nullptr)
    {
        debugPrint("Music track %s not loaded!", _resourceName.c_str());
        return;
    }

    Mix_VolumeMusic(volume);
    Mix_PlayMusic(music, loops);
    nowPlayingMusicTrackId = _resourceName;
}

void SoundSystem::stopMusic(int fadeOutMs)
{
    if(!isMusicPlaying())
        return;

    if(fadeOutMs != 0)
        Mix_FadeOutMusic(fadeOutMs);
    else
        Mix_HaltMusic();

    clearNowPlaying();
}

bool SoundSystem::isMusicPlaying()
{
    return !nowPlayingMusicTrackId.empty();
}

void SoundSystem::clearNowPlaying()
{
    nowPlayingMusicTrackId.clear();
}
