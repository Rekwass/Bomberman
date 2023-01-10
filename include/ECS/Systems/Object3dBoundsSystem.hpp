/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Object3dBoundsSystem
*/

#pragma once

#include "ECS/Core/Coordinator.hpp"
#include "ECS/Core/System.hpp"

namespace ecs::system {

/*
 * Bounds updator for 3d objects
 */
class Object3dBoundsSystem final : public System {
   public:
    Object3dBoundsSystem() noexcept = default;
    Object3dBoundsSystem(Object3dBoundsSystem const& other) noexcept = default;
    Object3dBoundsSystem(Object3dBoundsSystem&& other) noexcept = default;
    ~Object3dBoundsSystem() noexcept final = default;

    Object3dBoundsSystem& operator=(Object3dBoundsSystem const& other) noexcept = default;
    Object3dBoundsSystem& operator=(Object3dBoundsSystem&& other) noexcept = default;

    /*
     * Update the entities linked to the system
     *
     * No return value
     *
     * coordinator -> The coordinator to use to update the system
     */
    void update(Coordinator& coordinator) const;
};

} // namespace ecs::system
