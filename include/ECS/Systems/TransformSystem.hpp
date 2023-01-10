/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** TransformSystem
*/

#pragma once

#include "ECS/Core/Coordinator.hpp"
#include "ECS/Core/System.hpp"

namespace ecs::system {

/*
 * Transform on attributes
 */
class TransformSystem final : public System {
   public:
    TransformSystem() noexcept = default;
    TransformSystem(TransformSystem const& other) noexcept = default;
    TransformSystem(TransformSystem&& other) noexcept = default;
    ~TransformSystem() noexcept final = default;

    TransformSystem& operator=(TransformSystem const& other) noexcept = default;
    TransformSystem& operator=(TransformSystem&& other) noexcept = default;

    /*
     * Update the entities linked to the system
     *
     * No return value
     *
     * coordinator -> The coordinator to use to update the system
     *
     * elapsedTime -> The time elapsed since we want to update (in seconds)
     */
    void update(Coordinator& coordinator, float elapsedTime) const noexcept;
};

} // namespace ecs::system
