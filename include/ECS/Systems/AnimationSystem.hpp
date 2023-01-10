/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** AnimationSystem
*/

#pragma once

#include "ECS/Core/Coordinator.hpp"
#include "ECS/Core/System.hpp"

namespace ecs::system {

/*
 * Updator for 3d objects animations
 */
class AnimationSystem final : public System {
   public:
    AnimationSystem() noexcept = default;
    AnimationSystem(AnimationSystem const& other) noexcept = default;
    AnimationSystem(AnimationSystem&& other) noexcept = default;
    ~AnimationSystem() noexcept final = default;

    AnimationSystem& operator=(AnimationSystem const& other) noexcept = default;
    AnimationSystem& operator=(AnimationSystem&& other) noexcept = default;

    /*
     * Update the entities linked to the system
     *
     * No return value
     *
     * coordinator -> The coordinator to use to update the system
     *
     * elapsedTime -> The time elapsed since we want to update (in seconds)
     */
    void update(Coordinator& coordinator, float elapsedTime) const;
};

} // namespace ecs::system
