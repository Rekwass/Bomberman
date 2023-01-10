/*
** EPITECH PROJECT, 2022
** include
** File description:
** LifePowerUp
*/

#pragma once

#include "Game/Map/PowerUp/APowerUp.hpp"

namespace game {

/*
 * Life power up
 */
class LifePowerUp final : public APowerUp {
   public:
    LifePowerUp() noexcept = delete;
    LifePowerUp(ecs::Coordinator& coordinator, const ModelSoundInfos& modelInfos, const utils::Vector& position) noexcept;
    LifePowerUp(LifePowerUp const& other) noexcept = delete;
    LifePowerUp(LifePowerUp&& other) noexcept = default;
    ~LifePowerUp() noexcept final = default;

    LifePowerUp& operator=(LifePowerUp const& other) noexcept = delete;
    LifePowerUp& operator=(LifePowerUp&& other) noexcept = delete;

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
