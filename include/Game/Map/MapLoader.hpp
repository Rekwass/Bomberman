/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** MapLoader
*/

#pragma once

#include "Game/Map/Map.hpp"

#include <string_view>

namespace game {

/*
 * Load a bomberman map
 */
class MapLoader {
   public:
    MapLoader() noexcept = delete;
    MapLoader(MapLoader const& other) noexcept = delete;
    MapLoader(MapLoader&& other) noexcept = delete;
    ~MapLoader() noexcept = delete;

    MapLoader& operator=(MapLoader const& other) noexcept = delete;
    MapLoader& operator=(MapLoader&& other) noexcept = delete;

    /*
     * Load a new map and return it
     *
     * Returns the map itself
     *
     * coordinator -> ECS coordinator
     *
     * collisionSystem -> The ECS collisions system
     *
     * mapReader -> The map reader object
     *
     * mapPosition -> The position of the map center
     */
    static Map loadMap(ecs::Coordinator& coordinator, ecs::system::CollisionSystem& collisionSystem, const MapReader& mapReader, const utils::Vector& mapPosition);
};

} // namespace game
