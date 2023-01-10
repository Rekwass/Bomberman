/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Image2dRenderSystem
*/

#pragma once

#include "ECS/Core/Coordinator.hpp"
#include "ECS/Core/System.hpp"

namespace ecs::system {

/*
 * Renderer for 2d images
 */
class Image2dRenderSystem final : public System {
   public:
    Image2dRenderSystem() noexcept = default;
    Image2dRenderSystem(Image2dRenderSystem const& other) noexcept = default;
    Image2dRenderSystem(Image2dRenderSystem&& other) noexcept = default;
    ~Image2dRenderSystem() noexcept final = default;

    Image2dRenderSystem& operator=(Image2dRenderSystem const& other) noexcept = default;
    Image2dRenderSystem& operator=(Image2dRenderSystem&& other) noexcept = default;

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
