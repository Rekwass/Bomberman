/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** HitboxDisplayer
*/

#include "Graphic/HitboxDisplayer.hpp"

// NOLINTNEXTLINE
std::unordered_map<ecs::Entity, graphic::HitboxDisplayer::Hitbox> graphic::HitboxDisplayer::hitboxes = {};
bool graphic::HitboxDisplayer::enabled = false;

void graphic::HitboxDisplayer::clear() noexcept
{
    graphic::HitboxDisplayer::hitboxes.clear();
}

void graphic::HitboxDisplayer::addHitbox(ecs::Entity entity, BoundingBox hitbox) noexcept
{
    if (graphic::HitboxDisplayer::enabled) {
        graphic::HitboxDisplayer::hitboxes.insert({entity, {.hitbox = hitbox}});
    }
}

void graphic::HitboxDisplayer::addPrevisualization(ecs::Entity entity, BoundingBox hitbox) noexcept
{
    if (graphic::HitboxDisplayer::enabled) {
        if (graphic::HitboxDisplayer::hitboxes.contains(entity)) {
            graphic::HitboxDisplayer::hitboxes.at(entity).prev = true;
            graphic::HitboxDisplayer::hitboxes.at(entity).prevHitbox = hitbox;
        }
    }
}

void graphic::HitboxDisplayer::setHitBoxInCollision(ecs::Entity entity) noexcept
{
    if (graphic::HitboxDisplayer::enabled) {
        if (graphic::HitboxDisplayer::hitboxes.contains(entity)) {
            graphic::HitboxDisplayer::hitboxes.at(entity).color = BLUE;
        }
    }
}

void graphic::HitboxDisplayer::setHitBoxInCollisionNotMoving(ecs::Entity entity) noexcept
{
    if (graphic::HitboxDisplayer::enabled) {
        if (graphic::HitboxDisplayer::hitboxes.contains(entity)) {
            graphic::HitboxDisplayer::hitboxes.at(entity).color = YELLOW;
        }
    }
}

void graphic::HitboxDisplayer::display() noexcept
{
    if (graphic::HitboxDisplayer::enabled) {
        for (const auto& hitbox : graphic::HitboxDisplayer::hitboxes) {
            DrawBoundingBox(hitbox.second.hitbox, hitbox.second.color);
            if (hitbox.second.prev) {
                DrawBoundingBox(hitbox.second.prevHitbox, RED);
            }
        }
    }
}

void graphic::HitboxDisplayer::enable(bool enabled) noexcept
{
    graphic::HitboxDisplayer::enabled = enabled;
}
