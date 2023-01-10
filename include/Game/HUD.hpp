/*
** EPITECH PROJECT, 2022
** include
** File description:
** HUD
*/

#pragma once

#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/RenderableImage2d.hpp"
#include "ECS/Components/RenderableText2d.hpp"
#include "ECS/Core/Coordinator.hpp"
#include "ECS/Core/Entities.hpp"
#include "Game/PlayersManager.hpp"

namespace game {

struct PlayerStat {
    unsigned int lifes;
    unsigned int bombs;
};

class HUD {
   public:
    HUD()
    noexcept = delete;
    explicit HUD(ecs::Coordinator& coordinator);
    HUD(HUD const& other)
    noexcept = delete;
    HUD(HUD&& other)
    noexcept = delete;
    ~HUD() noexcept;

    HUD& operator=(HUD const& other) noexcept = delete;
    HUD& operator=(HUD&& other) noexcept = delete;

    /*
     * Update the HUD
     *
     * No return value
     *
     * stats -> The players stats
     */
    void update(std::array<PlayerStat, 4> stats) noexcept;

   private:
    /*
     * Get the player label according to it id
     *
     * Return the player label as a string
     *
     * id -> Player id
     */
    std::string getPlayerLabel(game::PlayerId id) noexcept;

    ecs::Coordinator& coordinator;
    ecs::Entity p1Name{};
    ecs::Entity p1LifeIcon{};
    ecs::Entity p1LifeNb{};
    ecs::Entity p1BombIcon{};
    ecs::Entity p1BombNb{};
    ecs::Entity p2Name{};
    ecs::Entity p2LifeIcon{};
    ecs::Entity p2LifeNb{};
    ecs::Entity p2BombIcon{};
    ecs::Entity p2BombNb{};
    ecs::Entity p3Name{};
    ecs::Entity p3LifeIcon{};
    ecs::Entity p3LifeNb{};
    ecs::Entity p3BombIcon{};
    ecs::Entity p3BombNb{};
    ecs::Entity p4Name{};
    ecs::Entity p4LifeIcon{};
    ecs::Entity p4LifeNb{};
    ecs::Entity p4BombIcon{};
    ecs::Entity p4BombNb{};
    int playerCount = 0;
    int aiCount = 0;
    int onlineCount = 0;
};

} // namespace game
