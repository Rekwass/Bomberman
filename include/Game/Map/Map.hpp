/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Map
*/

#pragma once

#include "ECS/Core/Coordinator.hpp"
#include "ECS/Systems/CollisionSystem.hpp"
#include "Game/HUD.hpp"
#include "Game/Map/Items/Bomb.hpp"
#include "Game/Map/Items/Ground.hpp"
#include "Game/Map/MapPart.hpp"
#include "Game/Map/MapReader.hpp"
#include "Game/Map/ObjectsInfos.hpp"
#include "Game/Map/Player/APlayer.hpp"
#include "Game/Map/Position.hpp"

#include <vector>

namespace game {

struct AroundMapPartStates {
    PartState up = PartState::UNFREE;
    PartState down = PartState::UNFREE;
    PartState left = PartState::UNFREE;
    PartState right = PartState::UNFREE;
    PartState middle = PartState::UNFREE;
};

struct AroundMapPartTypes {
    PartType up = PartType::WALL;
    PartType down = PartType::WALL;
    PartType left = PartType::WALL;
    PartType right = PartType::WALL;
    PartType middle = PartType::WALL;
};

struct Range {
    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;
    bool haveUp = false;
    bool haveDown = false;
    bool haveLeft = false;
    bool haveRight = false;
};

/*
 * A bomberman map
 */
class Map {
   public:
    Map() noexcept = delete;
    Map(ecs::Coordinator& coordinator, ecs::system::CollisionSystem& collisionSystem, const MapReader& mapReader, const utils::Vector& mapPosition);
    Map(Map const& other) noexcept = delete;
    Map(Map&& other) noexcept = default;
    ~Map() noexcept = default;

    Map& operator=(Map const& other) noexcept = delete;
    Map& operator=(Map&& other) noexcept = delete;

    /*
     * Update the map and its elements
     *
     * No return value
     */
    void update();
    /*
     * Put a bomb at the given coordinates
     *
     * Return false if the bomb could not be placed, true otherwise
     *
     * position -> The position of the bomb
     *
     * player -> The player that put the bomb
     */
    bool putBomb(utils::Vector position, APlayer& player) noexcept;
    /*
     * Get the around parts state
     *
     * No return value
     *
     * position -> The position of the entity to get around parts state
     */
    AroundMapPartStates getAroundParts(utils::Vector position) const noexcept;
    /*
     * Get the around parts type
     *
     * No return value
     *
     * position -> The position of the entity to get around parts state
     */
    AroundMapPartTypes getAroundPartsType(utils::Vector position) const noexcept;
    /*
     * Get the players stats
     *
     * Return the players stats
     */
    std::array<game::PlayerStat, 4> getPlayersStats() const noexcept;
    /*
     * Check if the given hitbox at the given position is all contained in a map portion
     *
     * Return true if the hitbox is contained in a map portion, false otherwise
     *
     * position -> The position of the hitbox
     *
     * hitbox -> The hitbox
     *
     * modifier -> The percentage to apply on the blockSize
     */
    bool isCompletelyInsidePart(utils::Vector position, BoundingBox hitbox, float modifier = 0.9) const noexcept;
    /*
     * Get the nearest part center
     *
     * Return the position of the center of the nearest
     *
     * position -> The position as a vector
     */
    utils::Vector getNearestPartCenter(utils::Vector& position) const noexcept;
    /*
     * Check if the game is ended
     *
     * Return true if the game is ended, false otherwise
     */
    bool isEnded() const noexcept;
    /*
     * Extract map players
     *
     * Return the players
     */
    std::vector<std::unique_ptr<APlayer>> extractPlayers() noexcept;

   private:
    /*
     * Convert a vector as a position in the map
     *
     * Return the position as indexes
     *
     * position -> The position as a vector
     */
    Position convertVectorAsPosition(utils::Vector position) const noexcept;
    /*
     * Get the range of non-unfree parts
     *
     * Return the range
     *
     * position -> The position of the map part to get range for
     *
     * range -> The maximum range
     */
    Range getRange(Position position, unsigned int maximumRange) noexcept;
    /*
     * Update the bombs
     *
     * No return value
     */
    void updateBombs() noexcept;

    bool valid = false;
    ecs::Coordinator& coordinator;
    ecs::system::CollisionSystem& collisionSystem;
    utils::Vector blockSize;
    utils::Vector mapStarting;
    ModelSoundInfos bombsInfos;
    ModelSoundInfos explosionsInfos;
    PowerUpsInfos powerUpsInfos;
    std::vector<std::vector<MapPart>> mapParts;
    std::vector<Ground> grounds;
    std::vector<std::unique_ptr<APlayer>> players;
    std::unordered_map<Position, Bomb, PositionHash> bombs;
};

} // namespace game
