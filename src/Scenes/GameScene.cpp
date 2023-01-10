/*
** EPITECH PROJECT, 2022
** Indie Studio
** File description:
** Main Menu
*/

#include "Scenes/GameScene.hpp"

#include "ECS/Components/Bounds3d.hpp"
#include "ECS/Systems/CollisionSystem.hpp"
#include "Game/Map/MapLoader.hpp"
#include "Network/Client.hpp"
#include "Scenes/EndScene.hpp"

// NOLINTNEXTLINE
scene::GameScene::GameScene(game::Room& room, ecs::system::CollisionSystem& collisionSystem, ecs::Coordinator& coordinator, game::MapReader mapReader) :
    coordinator(coordinator), map(game::MapLoader::loadMap(coordinator, collisionSystem, mapReader, room.getMapPosition())), mapPosition(room.getMapPosition()), hud(coordinator)
{
    network::Client::setInGame();
}

void scene::GameScene::update(scene::ScenesManager& scenesManager, float /*dt*/)
{
    if (this->map.isEnded()) {
        if (not this->gameEnded) {
            scenesManager.setScene<scene::EndScene, true>(this->coordinator, std::move(this->map.extractPlayers()));
            this->gameEnded = true;
        }
    } else {
        this->map.update();

        this->hud.update(this->map.getPlayersStats());
    }
}

utils::Vector scene::GameScene::getCameraPosition() const noexcept
{
    return (this->mapPosition + utils::Vector{-22, 43, 0});
}

utils::Vector scene::GameScene::getCameraLooking() const noexcept
{
    return this->mapPosition;
}
