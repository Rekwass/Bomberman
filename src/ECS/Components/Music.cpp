/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** MusicObject
*/

#include "ECS/Components/Music.hpp"

#include "ECS/ECSErrors.hpp"

ecs::component::MusicObject::MusicObject(std::string_view musicPath) noexcept :
    music(LoadMusicStream(musicPath.data()))
{
    this->valid = true;
}

ecs::component::MusicObject::MusicObject(MusicObject&& other) noexcept :
    music(other.music), isPause(other.isPause), isStarted(other.isStarted), loop(other.loop), pitch(other.pitch), valid(other.valid)
{
    other.valid = false;
}

ecs::component::MusicObject& ecs::component::MusicObject::operator=(MusicObject&& other) noexcept
{
    this->music = other.music;
    this->isPause = other.isPause;
    this->isStarted = other.isStarted;
    this->loop = other.loop;
    this->pitch = other.pitch;
    this->valid = other.valid;
    other.valid = false;
    return *this;
}

ecs::component::MusicObject::~MusicObject() noexcept
{
    if (this->valid) {
        StopMusicStream(this->music);
        UnloadMusicStream(this->music);
    }
}

const Music& ecs::component::MusicObject::getMusic() noexcept
{
    return this->music;
}

void ecs::component::MusicObject::play() noexcept
{
    if (this->valid) {
        if (not this->isStarted) {
            PlayMusicStream(this->music);
            this->isStarted = true;
        } else {
            ResumeMusicStream(this->music);
        }
    }
}

void ecs::component::MusicObject::pause() noexcept
{
    if (this->valid) {
        this->isPause = not isPause;
        if (this->isPause) {
            PauseMusicStream(this->music);
        } else {
            ResumeMusicStream(this->music);
        }
    }
}

void ecs::component::MusicObject::restart() noexcept
{
    if (this->valid) {
        StopMusicStream(this->music);
        if (not this->isPause) {
            PlayMusicStream(this->music);
        }
    }
}

void ecs::component::MusicObject::setVolume(float volume) noexcept
{
    if (this->valid) {
        SetMusicVolume(this->music, volume);
    }
}

void ecs::component::MusicObject::setPitch(float pitch) noexcept
{
    if (this->valid) {
        SetMusicPitch(this->music, pitch);
    }
}

void ecs::component::MusicObject::setPause(bool value) noexcept
{
    if (this->valid) {
        this->isPause = value;
    }
}
