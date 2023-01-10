/*
** EPITECH PROJECT, 2022
** src
** File description:
** AudioPlayer
*/

#include "AudioPlayer.hpp"

audio::AudioPlayer::AudioPlayer() noexcept
{
    InitAudioDevice();
}

audio::AudioPlayer::~AudioPlayer() noexcept
{
    StopSoundMulti();

    auto& instance = getInstance();
    for (const auto& sound : instance.sounds) {
        UnloadSound(sound.second);
    }

    CloseAudioDevice();
}

audio::AudioPlayer& audio::AudioPlayer::getInstance() noexcept
{
    static AudioPlayer audioPlayer;

    return audioPlayer;
}

void audio::AudioPlayer::Init() noexcept
{
    getInstance();
}

void audio::AudioPlayer::playSound(std::string_view soundPath) noexcept
{
    std::string path(soundPath);

    auto& instance = getInstance();

    if (not instance.sounds.contains(path)) {
        instance.sounds.insert({path, LoadSound(path.c_str())});
    }
    PlaySoundMulti(instance.sounds.at(path));
}

void audio::AudioPlayer::setSoundVolume(std::string_view soundPath, float volume) noexcept
{
    std::string path(soundPath);

    auto& instance = getInstance();

    if (instance.sounds.contains(path)) {
        SetSoundVolume(instance.sounds.at(path), volume);
    }
}

void audio::AudioPlayer::enable(bool state) noexcept
{
    SetMasterVolume((state ? 1 : 0));
}
