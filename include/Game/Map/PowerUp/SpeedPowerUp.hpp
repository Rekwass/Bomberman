/*
** EPITECH PROJECT, 2022
** include
** File description:
** SpeedPowerUp
*/

#pragma once

#include "Game/Map/PowerUp/APowerUp.hpp"

namespace game {

/*
 * Speed increase power up
 */
class SpeedPowerUp final : public APowerUp {
   public:
    SpeedPowerUp() noexcept = delete;
    SpeedPowerUp(ecs::Coordinator& coordinator, const ModelSoundInfos& modelInfos, const utils::Vector& position) noexcept;
    SpeedPowerUp(SpeedPowerUp const& other) noexcept = delete;
    SpeedPowerUp(SpeedPowerUp&& other) noexcept = default;
    ~SpeedPowerUp() noexcept final = default;

    SpeedPowerUp& operator=(SpeedPowerUp const& other) noexcept = delete;
    SpeedPowerUp& operator=(SpeedPowerUp&& other) noexcept = delete;

    /*
     * Change the given player according to the power up
     *
     * No return value
     *
     * player -> The player to do changes on
     */
    void doChangesOnPlayer(APlayer& player) noexcept final;
};

} // namespace game
