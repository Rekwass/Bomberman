/*
** EPITECH PROJECT, 2022
** include
** File description:
** Box
*/

#pragma once

#include "ECS/Core/Coordinator.hpp"
#include "ECS/Systems/CollisionSystem.hpp"
#include "Game/Map/IMapPart.hpp"
#include "Vector.hpp"

#include <string_view>

namespace game {

/*
 * The box 3d object
 */
class Box final : public IMapPart {
   public:
    Box() noexcept = delete;
    Box(ecs::Coordinator& coordinator, ecs::system::CollisionSystem& collisionSystem, std::string_view modelPath, std::string_view texturePath, const utils::Vector& position);
    Box(Box const& other) noexcept = delete;
    Box(Box&& other) noexcept;
    ~Box() final;

    Box& operator=(Box const& other) noexcept = delete;
    Box& operator=(Box&& other) noexcept = delete;

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
