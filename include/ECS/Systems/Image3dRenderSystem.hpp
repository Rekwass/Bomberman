/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Image3dRenderSystem
*/

#pragma once

#include "ECS/Core/Coordinator.hpp"
#include "ECS/Core/System.hpp"
#include "raylib.h"

namespace ecs::system {

/*
 * Renderer for 3d images
 */
class Image3dRenderSystem final : public System {
   public:
    Image3dRenderSystem() noexcept = default;
    Image3dRenderSystem(Image3dRenderSystem const& other) noexcept = default;
    Image3dRenderSystem(Image3dRenderSystem&& other) noexcept = default;
    ~Image3dRenderSystem() noexcept final = default;

    Image3dRenderSystem& operator=(Image3dRenderSystem const& other) noexcept = default;
    Image3dRenderSystem& operator=(Image3dRenderSystem&& other) noexcept = default;

    /*
     * Update the entities linked to the system
     *
     * No return value
     *
     * coordinator -> The coordinator to use to update the system
     *
     * camera -> The camera to use to set the angle of the image
     *
     * THIS FUNCTION SHOULD BE CALLED INSIDE A 'BeginMode3D' FUNCTION CALL
     */
    void update(Coordinator& coordinator, const Camera3D& camera) const;
};

} // namespace ecs::system
