/*
** EPITECH PROJECT, 2022
** Image Render System
** File description:
** Create Image Render System
*/

#pragma once

#include "ECS/Core/Coordinator.hpp"
#include "ECS/Core/System.hpp"

namespace ecs::system {

/*
 * Updator for the camera
 */
class CameraSystem final : public System {
   public:
    CameraSystem() noexcept = default;
    CameraSystem(CameraSystem const& other) noexcept = default;
    CameraSystem(CameraSystem&& other) noexcept = default;
    ~CameraSystem() noexcept final = default;

    CameraSystem& operator=(CameraSystem const& other) noexcept = default;
    CameraSystem& operator=(CameraSystem&& other) noexcept = default;

    /*
     * Update the entities linked to the system
     *
     * No return value
     *
     * coordinator -> The coordinator to use to update the system
     */
    void update(Coordinator& coordinator) const noexcept;
};

} // namespace ecs::system