/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** CubicMap3dRenderSystem
*/

#pragma once

#include "ECS/Core/Coordinator.hpp"
#include "ECS/Core/System.hpp"

namespace ecs::system {

/*
 * Renderer for 3d cubic map
 */
class CubicMap3dRenderSystem final : public System {
   public:
    CubicMap3dRenderSystem() noexcept = default;
    CubicMap3dRenderSystem(CubicMap3dRenderSystem const& other) noexcept = default;
    CubicMap3dRenderSystem(CubicMap3dRenderSystem&& other) noexcept = default;
    ~CubicMap3dRenderSystem() noexcept final = default;

    CubicMap3dRenderSystem& operator=(CubicMap3dRenderSystem const& other) noexcept = default;
    CubicMap3dRenderSystem& operator=(CubicMap3dRenderSystem&& other) noexcept = default;

    /*
     * Update the entities linked to the system
     *
     * No return value
     *
     * coordinator -> The coordinator to use to update the system
     *
     * THIS FUNCTION SHOULD BE CALLED INSIDE A 'BeginMode3D' FUNCTION CALL
     */
    void update(Coordinator& coordinator) const;
};

} // namespace ecs::system
