/*
** EPITECH PROJECT, 2022
** include
** File description:
** APowerUp
*/

#pragma once

#include "ECS/Core/Coordinator.hpp"
#include "Game/Map/IMapPart.hpp"
#include "Game/Map/Player/APlayer.hpp"

namespace game {

/*
 * Power ups abstraction
 */
class APowerUp : public IMapPart {
   public:
    APowerUp() noexcept = delete;
    APowerUp(ecs::Coordinator& coordinator, const ModelSoundInfos& powerUpInfos, const utils::Vector& position) noexcept;
    APowerUp(APowerUp const& other) noexcept = delete;
    APowerUp(APowerUp&& other) noexcept;
    ~APowerUp() override;

    APowerUp& operator=(APowerUp const& other) noexcept = delete;
    APowerUp& operator=(APowerUp&& other) noexcept = delete;

    /*
     * Get the position of the map part
     *
     * Return the position as a vector
     */
    utils::Vector getPosition() const noexcept final;
    /*
     * Change the given player according to the power up
     *
     * No return value
     *
     * player -> The player to do changes on
     */
    virtual void doChangesOnPlayer(APlayer& player) noexcept = 0;
    /*
     * Apply the power up effects on the given player
     *
     * No return value
     *
     * player -> The player to apply the power up on
     */
    void apply(APlayer& player) noexcept;
    /*
     * Play the power up associated sound
     *
     * No return value
     */
    void playSound() const noexcept;

   protected:
    bool valid = true;
    ecs::Entity entity;
    ecs::Coordinator& coordinator;
    std::string sound;
    bool used = false;
};

} // namespace game
