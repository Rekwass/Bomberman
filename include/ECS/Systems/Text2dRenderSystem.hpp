/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Text2dRenderSystem
*/

#pragma once

#include "ECS/Core/Coordinator.hpp"
#include "ECS/Core/System.hpp"

namespace ecs::system {

/*
 * Renderer for 2d texts
 */
class Text2dRenderSystem final : public System {
   public:
    Text2dRenderSystem() noexcept = default;
    Text2dRenderSystem(Text2dRenderSystem const& other) noexcept = default;
    Text2dRenderSystem(Text2dRenderSystem&& other) noexcept = default;
    ~Text2dRenderSystem() noexcept final = default;

    Text2dRenderSystem& operator=(Text2dRenderSystem const& other) noexcept = default;
    Text2dRenderSystem& operator=(Text2dRenderSystem&& other) noexcept = default;

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
