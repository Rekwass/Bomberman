/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** MapLoader
*/

#include "Game/Map/MapLoader.hpp"

game::Map game::MapLoader::loadMap(ecs::Coordinator& coordinator, ecs::system::CollisionSystem& collisionSystem, const MapReader& mapReader, const utils::Vector& mapPosition)
{
    return {coordinator, collisionSystem, mapReader, mapPosition};
}
