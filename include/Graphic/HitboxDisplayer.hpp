/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** HitboxDisplayer
*/

#include "ECS/Core/Entities.hpp"
#include "raylib.h"

#include <unordered_map>

namespace graphic {

/*
 * Hitboxes displayer
 */
class HitboxDisplayer {
   public:
    HitboxDisplayer() noexcept = delete;
    HitboxDisplayer(HitboxDisplayer const& other) noexcept = delete;
    HitboxDisplayer(HitboxDisplayer&& other) noexcept = delete;
    ~HitboxDisplayer() noexcept = delete;

    HitboxDisplayer& operator=(HitboxDisplayer const& other) noexcept = delete;
    HitboxDisplayer& operator=(HitboxDisplayer&& other) noexcept = delete;

    /*
     * Clear the hitboxes list
     *
     * No return value
     */
    static void clear() noexcept;
    /*
     * Add a hitbox to the hitbox list
     *
     * No return value
     *
     * entity -> The entity to add hitbox for
     *
     * hitbox -> The hitbox to add
     */
    static void addHitbox(ecs::Entity entity, BoundingBox hitbox) noexcept;
    /*
     * Add a preview hitbox to the hitbox list
     *
     * No return value
     *
     * entity -> The entity to add hitbox for
     *
     * hitbox -> The hitbox to add
     */
    static void addPrevisualization(ecs::Entity entity, BoundingBox hitbox) noexcept;
    /*
     * Set a hitbox as in collision
     *
     * No return value
     *
     * entity -> The entity to set in collision
     */
    static void setHitBoxInCollision(ecs::Entity entity) noexcept;
    /*
     * Set a hitbox as in collision and not moving
     *
     * No return value
     *
     * entity -> The entity to set in collision
     */
    static void setHitBoxInCollisionNotMoving(ecs::Entity entity) noexcept;
    /*
     * Display the stored hitboxes
     *
     * No return value
     */
    static void display() noexcept;
    /*
     * Enable or not the Hitboxes
     *
     * No return value
     *
     * enabled -> true if the hitboxes should be enabled, false otherwise
     */
    static void enable(bool enabled = true) noexcept;

   private:
    struct Hitbox {
        BoundingBox hitbox{};
        Color color = GREEN;
        bool prev = false;
        BoundingBox prevHitbox{};
    };
    static bool enabled;
    static std::unordered_map<ecs::Entity, Hitbox> hitboxes;
};

} // namespace graphic
