/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** CubicMap3dBoundsSystem
*/

#pragma once

#include "ECS/Core/Coordinator.hpp"
#include "ECS/Core/System.hpp"

namespace ecs::system {

/*
 * Bounds updator for 3d cubic map
 */
class CubicMap3dBoundsSystem final : public System {
   public:
    CubicMap3dBoundsSystem() noexcept = default;
    CubicMap3dBoundsSystem(CubicMap3dBoundsSystem const& other) noexcept = default;
    CubicMap3dBoundsSystem(CubicMap3dBoundsSystem&& other) noexcept = default;
    ~CubicMap3dBoundsSystem() noexcept final = default;

    CubicMap3dBoundsSystem& operator=(CubicMap3dBoundsSystem const& other) noexcept = default;
    CubicMap3dBoundsSystem& operator=(CubicMap3dBoundsSystem&& other) noexcept = default;

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
