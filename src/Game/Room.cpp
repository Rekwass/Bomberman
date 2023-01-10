/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Room
*/

#include "Game/Room.hpp"

#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/Music.hpp"
#include "ECS/Components/RenderableObject3d.hpp"
#include "FilePaths.hpp"

game::Room::Room(ecs::Coordinator& coordinator) :
    coordinator(coordinator), room(coordinator.createEntity()), theme(coordinator.createEntity())
{
    this->coordinator.setComponent(this->room, ecs::component::Attributes{});
    this->coordinator.setComponent(this->room, ecs::component::RenderableObject3d(fmt::format("{}Objects/Room/Room.iqm", ASSETS_PATH), fmt::format("{}Textures/Room/Room.png", ASSETS_PATH)));

    this->coordinator.setComponent(this->theme, ecs::component::MusicObject(fmt::format("{}audio/Musics/MainTheme.mp3", ASSETS_PATH)));

    this->mapPosition = {-5, 1, 5};
    this->mapSize = {35, 2, 35};
}

utils::Vector game::Room::getMapPosition() const noexcept
{
    return this->mapPosition;
}

utils::Vector game::Room::getMapSize() const noexcept
{
    return this->mapSize;
}

void game::Room::playMusic() noexcept
{
    this->coordinator.getComponent<ecs::component::MusicObject>(this->theme).play();
}

void game::Room::stopMusic() noexcept
{
    this->coordinator.getComponent<ecs::component::MusicObject>(this->theme).pause();
}
