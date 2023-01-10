/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Wall
*/

#pragma once

#include "ECS/Core/Coordinator.hpp"
#include "ECS/Core/Entities.hpp"
#include "ECS/Systems/CollisionSystem.hpp"
#include "Game/Map/IMapPart.hpp"
#include "Vector.hpp"

#include <string_view>

namespace game {

/*
 * Wall 3d object
 */
class Wall final : public IMapPart {
   public:
    Wall() noexcept = delete;
    Wall(ecs::Coordinator& coordinator, ecs::system::CollisionSystem& collisionSystem, std::string_view modelPath, std::string_view texturePath, const utils::Vector& position);
    Wall(Wall const& other) noexcept = delete;
    Wall(Wall&& other) noexcept;
    ~Wall() final;

    Wall& operator=(Wall const& other) noexcept = delete;
    Wall& operator=(Wall&& other) noexcept = delete;

    /*
     * Get the position of the map part
     *
     * Return the position as a vector
     */
    utils::Vector getPosition() const noexcept final;

   private:
    bool valid = true;
    ecs::Coordinator& coordinator;
    ecs::Entity entity;
};

} // namespace game
