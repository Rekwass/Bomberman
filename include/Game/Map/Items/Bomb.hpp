/*
** EPITECH PROJECT, 2022
** include
** File description:
** Bomb
*/

#pragma once

#include "ECS/Core/Coordinator.hpp"
#include "ECS/Systems/CollisionSystem.hpp"
#include "Game/Map/Player/APlayer.hpp"
#include "Vector.hpp"

namespace game {

using BombId = std::uint16_t;

/*
 * Bomb object
 */
class Bomb {
   public:
    Bomb() noexcept = delete;
    Bomb(ecs::Coordinator& coordinator, ecs::system::CollisionSystem& collisionSystem, const ModelSoundInfos& modelInfos, const utils::Vector& position, APlayer& player);
    Bomb(Bomb const& other) noexcept = delete;
    Bomb(Bomb&& other) noexcept;
    ~Bomb();

    Bomb& operator=(Bomb const& other) noexcept = delete;
    Bomb& operator=(Bomb&& other) noexcept = delete;

    /*
     * Update the bomb depending on the remaining time before explosion
     *
     * Return true if the bomb should explose and false otherwise
     */
    bool shouldExplose() const noexcept;
    /*
     * Get the range of the bomb
     *
     * Return the range of the bomb
     */
    unsigned int getRange() const noexcept;
    /*
     * Get the id identifying the bomb
     *
     * Return the id
     */
    BombId getId() const noexcept;
    /*
     * Set the bomb to explose
     *
     * No return value
     */
    void explose() noexcept;
    /*
     * Get the bomb real position
     *
     * Return the position as a vector
     */
    utils::Vector getPosition() const noexcept;

   private:
    bool valid = true;
    bool exploded = false;
    BombId id;
    unsigned int range;
    APlayer& player;
    std::string sound;
    ecs::Coordinator& coordinator;
    ecs::Entity entity;
};

} // namespace game
