/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Relief3dRenderSystem
*/

#pragma once

#include "ECS/Core/Coordinator.hpp"
#include "ECS/Core/System.hpp"

namespace ecs::system {

/*
 * Renderer for 3d reliefs
 */
class Relief3dRenderSystem final : public System {
   public:
    Relief3dRenderSystem() noexcept = default;
    Relief3dRenderSystem(Relief3dRenderSystem const& other) noexcept = default;
    Relief3dRenderSystem(Relief3dRenderSystem&& other) noexcept = default;
    ~Relief3dRenderSystem() noexcept final = default;

    Relief3dRenderSystem& operator=(Relief3dRenderSystem const& other) noexcept = default;
    Relief3dRenderSystem& operator=(Relief3dRenderSystem&& other) noexcept = default;

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
