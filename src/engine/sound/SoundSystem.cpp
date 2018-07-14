#include <engine/DebugPrint.h>
#include <engine/sound/SoundSystem.h>

#include "SDL.h"

SoundSystem::SoundSystem()
{
    ANRI_DE debugPrint("Initializing SoundSystem!");

    clearNowPlaying();
}

SoundSystem::~SoundSystem()
{
    ANRI_DE debugPrint("SoundSystem destructor fired!");

    unloadAll();
    Mix_CloseAudio();
}

bool SoundSystem::init()
{
    ANRI_DE debugPrint("Initializing SDL Audio subsystem...");
    if(SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
    {
        ANRI_DE debugPrint("SDL Audio could not initialize! SDL error: %s", SDL_GetError());
        return false;
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        ANRI_DE debugPrint("SDL_mixer could not initialize! SDL_mixer error: %s", Mix_GetError());
        return false;
    }

    Mix_AllocateChannels(16);

    return true;
}

void SoundSystem::playSound(std::string id, int volume, int loops)
{
    if(sounds.count(id) == 0)
    {
        ANRI_DE debugPrint("Sound %s not loaded!", id.c_str());
        return;
    }

    Mix_Chunk *chunk = sounds[id];

    Mix_VolumeChunk(chunk, volume);
    Mix_PlayChannel(-1, chunk, loops);
}

void SoundSystem::playMusic(std::string id, int volume, int loops)
{
    if(musicTracks.count(id) == 0)
    {
        ANRI_DE debugPrint("Music track %s not loaded!", id.c_str());
        return;
    }

    Mix_Music *music = musicTracks[id];

    Mix_VolumeMusic(volume);
    Mix_PlayMusic(music, loops);
    nowPlayingMusicTrackId = id;
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

void SoundSystem::loadSound(std::string id, std::string path)
{
    Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
    if(chunk == nullptr)
    {
        ANRI_DE debugPrint("Failed to load sound %s! SDL_mixer error: %s", id.c_str(), Mix_GetError());
        return;
    }

    sounds[id] = chunk;

    ANRI_DE debugPrint("Loaded sound %s.", id.c_str());
}

void SoundSystem::unloadSound(std::string id)
{
    Mix_FreeChunk(sounds[id]);

    sounds.erase(id);

    ANRI_DE debugPrint("Unloaded sound %s.", id.c_str());
}

void SoundSystem::loadMusic(std::string id, std::string path)
{
    Mix_Music* music = Mix_LoadMUS(path.c_str());
    if(music == nullptr)
    {
        ANRI_DE debugPrint("Failed to load music track %s! SDL_mixer error: %s", id.c_str(), Mix_GetError());
        return;
    }

    musicTracks[id] = music;

    ANRI_DE debugPrint("Loaded music track %s.", id.c_str());
}

void SoundSystem::unloadMusic(std::string id)
{
    Mix_FreeMusic(musicTracks[id]);

    musicTracks.erase(id);

    ANRI_DE debugPrint("Unloaded music track %s.", id.c_str());
}

void SoundSystem::unloadAll()
{
    ANRI_DE debugPrint("Unloading all sounds & music...");

    if(isMusicPlaying())
    {
        Mix_HaltMusic();
    }

    for(auto const& sound : sounds)
    {
        Mix_FreeChunk(sound.second);
    }

    for(auto const& musicTrack : musicTracks)
    {
        Mix_FreeMusic(musicTrack.second);
    }

    sounds.clear();
    musicTracks.clear();
}

bool SoundSystem::isMusicPlaying()
{
    return !nowPlayingMusicTrackId.empty();
}

void SoundSystem::clearNowPlaying()
{
    nowPlayingMusicTrackId.clear();
}
