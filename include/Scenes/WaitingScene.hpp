/*
** EPITECH PROJECT, 2022
** include
** File description:
** WaitingScene
*/

#pragma once

#include "ECS/Core/Coordinator.hpp"
#include "Game/Map/MapReader.hpp"
#include "Game/PlayersManager.hpp"
#include "Game/Room.hpp"
#include "Scenes/IScene.hpp"

namespace scene {

class WaitingScene final : public IScene {
   public:
    WaitingScene() noexcept = delete;
    WaitingScene(game::Room& room, ecs::Coordinator& coordinator);
    WaitingScene(WaitingScene const& other) noexcept = delete;
    WaitingScene(WaitingScene&& other) noexcept = delete;
    ~WaitingScene() noexcept final;

    WaitingScene& operator=(WaitingScene const& other) noexcept = delete;
    WaitingScene& operator=(WaitingScene&& other) noexcept = delete;

    void update(ScenesManager& scenesManager, float dt) final;
    utils::Vector getCameraPosition() const noexcept final;
    utils::Vector getCameraLooking() const noexcept final;
    /*
     * Change the texture of the given player
     *
     * No return value
     *
     * id -> The id of the player to change the texture for
     *
     * filePath -> The path of the texture
     */
    void changeTexture(game::PlayerId id, const std::string& filePath) noexcept;
    /*
     * Set the player ready
     *
     * No return value
     *
     * id -> The id of the player to set ready
     */
    void setReady(game::PlayerId id) noexcept;
    /*
     * Set the player unready
     *
     * No return value
     *
     * id -> The id of the player to set unready
     */
    void setUnready(game::PlayerId id) noexcept;
    /*
     * Set the player present
     *
     * No return value
     *
     * id -> The id of the player to set present
     */
    void setPresent(game::PlayerId id) noexcept;
    /*
     * Set the player not present
     *
     * No return value
     *
     * id -> The id of the player to set not present
     */
    void setNotPresent(game::PlayerId id) noexcept;
    /*
     * Watch if the other players changed something, and change it on the visual too
     *
     * No return value
     */
    void watchChangesOnline() noexcept;

   private:
    ecs::Coordinator& coordinator;
    ecs::Entity title;
    ecs::Entity player1;
    ecs::Entity player2;
    ecs::Entity player3;
    ecs::Entity player4;
    ecs::Entity online1Ready;
    ecs::Entity online2Ready;
    ecs::Entity online3Ready;
    ecs::Entity online4Ready;
    ecs::Entity player;
    ecs::Entity ready;
    ecs::Entity beReadyText;
    game::MapReader mapReader;
    game::PlayerId playerId;
    std::vector<std::string> textures;
    std::array<ecs::Entity, 4> players{};
    std::array<ecs::Entity, 4> readies{};
    std::array<bool, 4> playersPresences{false};
    std::array<bool, 4> playersReadies{false};
    std::array<std::string, 4> playersTextures;
    int selectedTexture = 0;
    bool isReady = false;
};

} // namespace scene
