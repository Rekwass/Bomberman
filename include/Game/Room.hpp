/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Room
*/

#pragma once

#include "ECS/Core/Coordinator.hpp"
#include "ECS/Core/Entities.hpp"
#include "Vector.hpp"

namespace game {

/*
 * Room 3d object
 */
class Room {
   public:
    Room() noexcept = delete;
    explicit Room(ecs::Coordinator& coordinator);
    Room(Room const& other) noexcept = default;
    Room(Room&& other) noexcept = default;
    ~Room() noexcept = default;

    Room& operator=(Room const& other) noexcept = delete;
    Room& operator=(Room&& other) noexcept = delete;

    /*
     * Get the position of the center of the map
     *
     * Return the map position
     */
    utils::Vector getMapPosition() const noexcept;
    /*
     * Get the map size
     *
     * Return the map size
     */
    utils::Vector getMapSize() const noexcept;
    void playMusic() noexcept;
    void stopMusic() noexcept;

   private:
    ecs::Coordinator& coordinator;
    ecs::Entity room{};
    ecs::Entity theme{};
    utils::Vector mapPosition{};
    utils::Vector mapSize{};
};

} // namespace game
