/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** IMapPart
*/

#pragma once

#include "Vector.hpp"

namespace game {

/*
 * Map part interface
 */
class IMapPart {
   public:
    IMapPart() noexcept = default;
    IMapPart(IMapPart const& other) noexcept = default;
    IMapPart(IMapPart&& other) noexcept = default;
    virtual ~IMapPart() noexcept = default;

    IMapPart& operator=(IMapPart const& other) noexcept = default;
    IMapPart& operator=(IMapPart&& other) noexcept = default;

    /*
     * Get the position of the map part
     *
     * Return the position as a vector
     */
    virtual utils::Vector getPosition() const noexcept = 0;
};

} // namespace game
