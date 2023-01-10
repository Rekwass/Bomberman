/*
** EPITECH PROJECT, 2022
** include
** File description:
** Fire
*/

#pragma once

#include "ECS/Core/Coordinator.hpp"
#include "Game/Map/IMapPart.hpp"
#include "Game/Map/ObjectsInfos.hpp"
#include "Vector.hpp"

namespace game {

/*
 * Fire 3d object
 */
class Fire final : public IMapPart {
   public:
    Fire() noexcept = delete;
    Fire(ecs::Coordinator& coordinator, const ModelInfos& ModelInfos, const utils::Vector& position);
    Fire(Fire const& other) noexcept = delete;
    Fire(Fire&& other) noexcept;
    ~Fire() final;

    Fire& operator=(Fire const& other) noexcept = delete;
    Fire& operator=(Fire&& other) noexcept = delete;

    /*
     * Get the position of the map part
     *
     * Return the position as a vector
     */
    utils::Vector getPosition() const noexcept final;
    /*
     * Check is the fire stills here
     *
     * Return true is the fire is not burning and false otherwise
     */
    bool noMoreBurning() const noexcept;

   private:
    bool valid = true;
    ecs::Coordinator& coordinator;
    ecs::Entity entity;
};

} // namespace game
