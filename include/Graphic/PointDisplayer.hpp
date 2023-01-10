/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** PoitDisplayer
*/

#pragma once

#include "Vector.hpp"
#include "raylib.h"

#include <unordered_map>

namespace graphic {

/*
 * Display points position
 */
class PointDisplayer {
   public:
    PointDisplayer() noexcept = delete;
    PointDisplayer(PointDisplayer const& other) noexcept = delete;
    PointDisplayer(PointDisplayer&& other) noexcept = delete;
    ~PointDisplayer() noexcept = delete;

    PointDisplayer& operator=(PointDisplayer const& other) noexcept = delete;
    PointDisplayer& operator=(PointDisplayer&& other) noexcept = delete;

    /*
     * Clear the points list
     *
     * No return value
     */
    static void clear() noexcept;
    /*
     * Add a point to the point list
     *
     * No return value
     *
     * point -> The point to add
     *
     * range -> The range of the line
     *
     * color -> The color of the point
     */
    static void addPoint(utils::Vector point, float range = 100, Color color = YELLOW) noexcept;
    /*
     * Display the stored points
     *
     * No return value
     */
    static void display() noexcept;
    /*
     * Enable or not the Points
     *
     * No return value
     *
     * enabled -> true if the points should be enabled, false otherwise
     */
    static void enable(bool enabled = true) noexcept;

   private:
    struct Point {
        float range = 100;
        Color color = YELLOW;
    };
    static bool enabled;
    static std::unordered_map<utils::Vector, Point, utils::VectorHash> points;
};

} // namespace graphic
