/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Relief3dBoundsSystem
*/

#pragma once

#include "ECS/Core/Coordinator.hpp"
#include "ECS/Core/System.hpp"

namespace ecs::system {

/*
 * Bounds updator for 3d reliefs
 */
class Relief3dBoundsSystem final : public System {
   public:
    Relief3dBoundsSystem() noexcept = default;
    Relief3dBoundsSystem(Relief3dBoundsSystem const& other) noexcept = default;
    Relief3dBoundsSystem(Relief3dBoundsSystem&& other) noexcept = default;
    ~Relief3dBoundsSystem() noexcept final = default;

    Relief3dBoundsSystem& operator=(Relief3dBoundsSystem const& other) noexcept = default;
    Relief3dBoundsSystem& operator=(Relief3dBoundsSystem&& other) noexcept = default;

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
