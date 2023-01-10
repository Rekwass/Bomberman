/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Ground
*/

#pragma once

#include "ECS/Core/Coordinator.hpp"
#include "ECS/Core/Entities.hpp"
#include "Vector.hpp"

#include <string_view>

namespace game {

/*
 * Ground 3d object
 */
class Ground {
   public:
    Ground() noexcept = delete;
    Ground(ecs::Coordinator& coordinator, std::string_view modelPath, std::string_view texturePath, const utils::Vector& position);
    Ground(Ground const& other) noexcept = default;
    Ground(Ground&& other) noexcept;
    ~Ground();

    Ground& operator=(Ground const& other) noexcept = delete;
    Ground& operator=(Ground&& other) noexcept = delete;

   private:
    bool valid = true;
    ecs::Coordinator& coordinator;
    ecs::Entity entity;
};

} // namespace game
