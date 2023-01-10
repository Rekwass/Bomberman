/*
** EPITECH PROJECT, 2022
** Indie Studio
** File description:
** Music System
*/

#pragma once

#include "ECS/Core/Coordinator.hpp"
#include "ECS/Core/System.hpp"

namespace ecs::system {

/*
 * Music system
 */
class MusicSystem final : public System {
   public:
    MusicSystem() noexcept;
    MusicSystem(MusicSystem const& other) noexcept = default;
    MusicSystem(MusicSystem&& other) noexcept = default;
    ~MusicSystem() noexcept final = default;

    MusicSystem& operator=(MusicSystem const& other) noexcept = default;
    MusicSystem& operator=(MusicSystem&& other) noexcept = default;

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
