/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** APlayer
*/

#pragma once

#include "ECS/Components/Animation.hpp"
#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/Transform.hpp"
#include "ECS/Core/Coordinator.hpp"
#include "Game/Map/ObjectsInfos.hpp"
#include "Game/PlayersManager.hpp"

namespace game {

class Map;

struct Movement {
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
};

/*
 * The player interface
 */
class APlayer {
   public:
    APlayer() noexcept = delete;
    APlayer(ecs::Coordinator& coordinator, const PlayersInfos& playersInfos, std::string_view texturePath, const utils::Vector& position, const PlayerId& id, const PlayerType& type) noexcept;
    APlayer(APlayer const& other) noexcept = delete;
    APlayer(APlayer&& other) noexcept;
    virtual ~APlayer();

    APlayer& operator=(APlayer const& other) noexcept = delete;
    APlayer& operator=(APlayer&& other) noexcept = delete;

    /*
     * Update the Player
     *
     * No return value
     */
    virtual void update() = 0;
    /*
     * Get the player type
     *
     * Return the player type
     */
    const PlayerType& getType() const noexcept;
    /*
     * Get the player id
     *
     * Return the player id
     */
    const PlayerId& getId() const noexcept;
    /*
     * Get the player range of the bomb he place
     *
     * Return the player range
     */
    unsigned int getBombRange() const noexcept;
    /*
     * Get the player lifes
     *
     * Return the player left lifes
     */
    unsigned int getLifes() const noexcept;
    /*
     * Get the player left bombs
     *
     * Return the number of bombs the player has in stock
     */
    unsigned int getLeftBombs() const noexcept;
    /*
     * Get the player object position
     *
     * Return the position as a vector
     */
    utils::Vector getPosition() const noexcept;
    /*
     * Check if a player is taking damage
     *
     * Return true if the player is actually taking damage
     */
    bool isTakingDamage() const noexcept;
    /*
     * Check if the player is alive
     *
     * Return true if the player is alive and false otherwise
     */
    bool isAlive() const noexcept;
    /*
     * Give back a bomb to the player
     *
     * No return value
     */
    void restoreBomb() noexcept;
    /*
     * Try to put a bomb on the map
     *
     * Return false if it was not possible to put the bomb, true otherwise
     *
     * map -> The map to put the bomb on
     *
     * position -> The position where to put the bomb
     */
    bool tryPutBomb(Map& map, utils::Vector position) noexcept;
    /*
     * Use a bomb of the player
     *
     * No return value
     */
    void useBomb() noexcept;
    /*
     * Take damage
     *
     * No return value
     */
    void takeDamage();
    /*
     * Make the player die
     *
     * No return value
     */
    void die();
    /*
     * Add a life to the player
     *
     * No return value
     */
    void addLife() noexcept;
    /*
     * Add a bomb range to the player
     *
     * No return value
     */
    void addBombRange() noexcept;
    /*
     * Add a bomb to the player stock
     *
     * No return value
     */
    void addBomb() noexcept;
    /*
     * Upgrade the speed of the player
     *
     * No return value
     */
    void upgradeSpeed() noexcept;
    /*
     * Set the position of the player
     *
     * No return value
     *
     * position -> The new position of the player
     */
    void setPosition(const utils::Vector& position) noexcept;
    /*
     * Set the rotation of the player
     *
     * No return value
     *
     * rotation -> The new rotation of the player
     */
    void setRotation(float rotation) noexcept;
    /*
     * Play the player celebration
     *
     * No return value
     */
    void playCelebration();

   protected:
    /*
     * Move the player up
     *
     * No return value
     *
     * moving -> Set to true if the player should move up
     */
    void moveUp(bool moving = true);
    /*
     * Move the player down
     *
     * No return value
     *
     * moving -> Set to true if the player should move down
     */
    void moveDown(bool moving = true);
    /*
     * Move the player left
     *
     * No return value
     *
     * moving -> Set to true if the player should move left
     */
    void moveLeft(bool moving = true);
    /*
     * Move the player right
     *
     * No return value
     *
     * moving -> Set to true if the player should move right
     */
    void moveRight(bool moving = true);
    /*
     * Stop the player and all his movements
     *
     * No return value
     */
    void stop() noexcept;
    /*
     * Set the new rotation of the player
     *
     * No return value
     */
    void setNewRotation() noexcept;
    /*
     * Start the walking animation on the player
     *
     * No return value
     *
     * animation -> The player animation component
     */
    static void startWalkingAnimation(ecs::component::Animation& animation);
    /*
     * Stop the walking animation on the player
     *
     * No return value
     *
     * animation -> The player animation component
     */
    static void stopWalkingAnimation(ecs::component::Animation& animation);

    bool valid = true;
    ecs::Entity entity;
    ecs::Coordinator& coordinator;
    Movement movements;
    PlayerId id;
    PlayerType type;
    int movementNumber = 0;
    float speed = 4;
    bool speedBoosted = false;
    bool alive = true;
    unsigned int lifes = 1;
    unsigned int bombsNumber = 1;
    unsigned int bombRange = 1;
    PlayerSounds sounds;
};

} // namespace game
