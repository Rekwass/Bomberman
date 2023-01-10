/*
** EPITECH PROJECT, 2022
** include
** File description:
** OnlinePlayer
*/

#pragma once

#include "Game/Map/Player/APlayer.hpp"
#include "Game/PlayersManager.hpp"

namespace game {

/*
 * Online player object
 */
class OnlinePlayer final : public APlayer {
   public:
    OnlinePlayer() noexcept = delete;
    OnlinePlayer(ecs::Coordinator& coordinator, const PlayersInfos& playersInfos, const utils::Vector& position, const PlayerId& id, Map& map) noexcept;
    OnlinePlayer(OnlinePlayer const& other) noexcept = delete;
    OnlinePlayer(OnlinePlayer&& other) noexcept = default;
    ~OnlinePlayer() noexcept final = default;

    OnlinePlayer& operator=(OnlinePlayer const& other) noexcept = delete;
    OnlinePlayer& operator=(OnlinePlayer&& other) noexcept = delete;

    /*
     * Update the AI player
     *
     * No return value
     */
    void update() final;

   private:
    Map& map;
    bool moving = false;
};

} // namespace game
