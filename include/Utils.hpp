/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Utils
*/

#pragma once

#include "ECS/Core/Coordinator.hpp"
#include "Graphic/Renderer.hpp"
#include "Graphic/Window.hpp"

namespace utils {

/*
 * Set the ray lib log level according to the RAYLIBDEBUG environment variable
 *
 * No return value
 */
void setRaylibLogLevel() noexcept;
/*
 * Init the ECS coordinator
 *
 * Return the inited coordinator
 */
ecs::Coordinator initCoordinator();
/*
 * Init the ECS events and listeners
 *
 * No return value
 *
 * coordinator -> The ECS coordinator
 *
 * renderer -> The renderer for objects
 *
 * window -> The graphic window
 */
void initEventsListeners(ecs::Coordinator& coordinator, graphic::Renderer& renderer, graphic::Window& window) noexcept;

/*
 * Check if program arguments contain the usage command
 *
 * Return true if the usage command is founded
 *
 * ac -> Program arguments number
 *
 * av[] -> Program arguments list
 */
bool checkUsage(int ac, const char* av[]) noexcept;
/*
 * Check for keyboard inputs and do according actions
 *
 * No return value
 *
 * coordinator -> ECS coordinator
 */
void checkKeyboardInputs(ecs::Coordinator& coordinator) noexcept;
/**
 * Convert an angle in degrees to fit into [0, 360]
 *
 * @param x The angle in degrees
 * @return The angle in degrees between 0 and 360
 */
float getInsideBorder(float x) noexcept;
/**
 * Get the minimum value of a vector
 *
 * @param vector The vector to get the minimum value
 * @return The minimum value of the vector
 */
float getVectorMin(utils::Vector& vector) noexcept;

enum class TypePart {
    GROUND = 0,
    WALL = 1
};

} // namespace utils
