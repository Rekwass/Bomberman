/*
** EPITECH PROJECT, 2022
** Object Render System
** File description:
** Create Object Render System
*/

#pragma once

#include "ECS/Core/Coordinator.hpp"
#include "ECS/Core/System.hpp"
#include "raylib.h"

namespace ecs::system {

/*
 * Renderer for 3d objects
 */
class Object3dRenderSystem final : public System {
   public:
    Object3dRenderSystem() noexcept = default;
    Object3dRenderSystem(Object3dRenderSystem const& other) noexcept = default;
    Object3dRenderSystem(Object3dRenderSystem&& other) noexcept = default;
    ~Object3dRenderSystem() noexcept final = default;

    Object3dRenderSystem& operator=(Object3dRenderSystem const& other) noexcept = default;
    Object3dRenderSystem& operator=(Object3dRenderSystem&& other) noexcept = default;

    /*
     * Update the entities linked to the system
     *
     * No return value
     *
     * coordinator -> The coordinator to use to update the system
     *
     * THIS FUNCTION SHOULD BE CALLED INSIDE A 'BeginMode3D' FUNCTION CALLED
     */
    void update(Coordinator& coordinator) const;
};

} // namespace ecs::system
