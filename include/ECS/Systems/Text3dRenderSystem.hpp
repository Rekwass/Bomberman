/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Text3dRenderSystem
*/

#pragma once

#include "ECS/Core/Coordinator.hpp"
#include "ECS/Core/System.hpp"

namespace ecs::system {

/*
 * Renderer for 3d texts
 */
class Text3dRenderSystem final : public System {
   public:
    Text3dRenderSystem() noexcept = default;
    Text3dRenderSystem(Text3dRenderSystem const& other) noexcept = default;
    Text3dRenderSystem(Text3dRenderSystem&& other) noexcept = default;
    ~Text3dRenderSystem() noexcept final = default;

    Text3dRenderSystem& operator=(Text3dRenderSystem const& other) noexcept = default;
    Text3dRenderSystem& operator=(Text3dRenderSystem&& other) noexcept = default;

    /*
     * Update the entities linked to the system
     *
     * No return value
     *
     * coordinator -> The coordinator to use to update the system
     *
     * THIS FUNCTION SHOULD BE CALLED INSIDE A 'BeginDrawing' FUNCTION CALL
     */
    void update(Coordinator& coordinator) const;
};

} // namespace ecs::system
