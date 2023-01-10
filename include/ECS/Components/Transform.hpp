/*
** EPITECH PROJECT, 2022
** Indie Studio
** File description:
** Transform
*/

#pragma once

#include "Vector.hpp"

namespace ecs::component {

/*
 * Values in movement are the distance traveled in a second
 *
 * rotationSpeed is the degrees added to the rotation each second
 *
 * rotationAngleGoal must be between 0 and 360 degrees
 */
struct Transform {
    utils::Vector movement{0, 0, 0};
    bool movingX = true;
    bool movingY = true;
    bool movingZ = true;

    float rotationAngleGoal = 0;
    float rotationSpeed = 0;
};

} // namespace ecs::component
