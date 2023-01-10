/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** PointDisplayer
*/

#include "Graphic/PointDisplayer.hpp"

#include "Vector.hpp"

// NOLINTNEXTLINE
std::unordered_map<utils::Vector, graphic::PointDisplayer::Point, utils::VectorHash> graphic::PointDisplayer::points = {};
bool graphic::PointDisplayer::enabled = false;

void graphic::PointDisplayer::clear() noexcept
{
    graphic::PointDisplayer::points.clear();
}

void graphic::PointDisplayer::addPoint(utils::Vector point, float range, Color color) noexcept
{
    if (graphic::PointDisplayer::enabled) {
        graphic::PointDisplayer::points.insert({point, {range, color}});
    }
}

void graphic::PointDisplayer::display() noexcept
{
    if (graphic::PointDisplayer::enabled) {
        for (const auto& point : graphic::PointDisplayer::points) {
            DrawSphere(point.first, 0.1, point.second.color);
            DrawLine3D({point.first.x + -1 * point.second.range, point.first.y, point.first.z}, {point.first.x + point.second.range, point.first.y, point.first.z}, RED);
            DrawLine3D({point.first.x, point.first.y + -1 * point.second.range, point.first.z}, {point.first.x, point.first.y + point.second.range, point.first.z}, GREEN);
            DrawLine3D({point.first.x, point.first.y, point.first.z + -1 * point.second.range}, {point.first.x, point.first.y, point.first.z + point.second.range}, BLUE);
        }
    }
}

void graphic::PointDisplayer::enable(bool enabled) noexcept
{
    graphic::PointDisplayer::enabled = enabled;
}
