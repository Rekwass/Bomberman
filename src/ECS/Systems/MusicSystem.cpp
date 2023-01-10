/*
** EPITECH PROJECT, 2022
** Indie Studio
** File description:
** Music System
*/

#include "ECS/Systems/MusicSystem.hpp"

#include "AudioPlayer.hpp"
#include "ECS/Components/Music.hpp"
#include "ECS/Core/Coordinator.hpp"
#include "raylib.h"

ecs::system::MusicSystem::MusicSystem() noexcept
{
    audio::AudioPlayer::Init();
}

void ecs::system::MusicSystem::update(ecs::Coordinator& coordinator) const
{
    for (const auto& entity : this->entities) {
        UpdateMusicStream(coordinator.getComponent<ecs::component::MusicObject>(entity).getMusic());
    }
}
