/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** ScenesManager
*/

#pragma once

#include "ECS/Systems/CollisionSystem.hpp"
#include "Game/Room.hpp"
#include "Graphic/Renderer.hpp"
#include "IScene.hpp"
#include "Utils.hpp"

#include <memory>

namespace scene {

/*
 * Manage different IScenes
 */
class ScenesManager {
   public:
    ScenesManager() noexcept = delete;
    ScenesManager(graphic::Renderer& renderer, game::Room& room, ecs::system::CollisionSystem& collisionSystem, ecs::Coordinator& coordinator) noexcept;
    ScenesManager(ScenesManager const& other) noexcept = delete;
    ScenesManager(ScenesManager&& other) noexcept = default;
    ~ScenesManager() noexcept = default;

    ScenesManager& operator=(ScenesManager const& other) noexcept = delete;
    ScenesManager& operator=(ScenesManager&& other) noexcept = delete;

    template <typename T, bool needRoom = false, bool needCollisionSystem = false, bool displayLoading = false, typename... Args>
    void setScene(Args&&... args)
    {
        if (displayLoading) {
            this->drawWaitingScreen();
        }
        this->lastScene = std::move(this->actualScene);
        if constexpr (needRoom) {
            if constexpr (needCollisionSystem) {
                this->actualScene = std::make_unique<T>(this->room, this->collisionSystem, std::forward<Args>(args)...);
            } else {
                this->actualScene = std::make_unique<T>(this->room, std::forward<Args>(args)...);
            }
        } else {
            if constexpr (needCollisionSystem) {
                this->actualScene = std::make_unique<T>(this->collisionSystem, std::forward<Args>(args)...);
            } else {
                this->actualScene = std::make_unique<T>(std::forward<Args>(args)...);
            }
        }
    }
    /*
     * Update the current scene(s)
     *
     * No return value
     *
     * dt -> The time elapsed since the last update
     */
    void update(float dt);
    /*
     * Draw a waiting screen with tips
     *
     * No return value
     */
    void drawWaitingScreen();

   private:
    /**
     * Initialize the transition movement between 2 scenes
     *
     * @return No return value
     */
    void initTransition() noexcept;
    /**
     * Manage a new transition if needed
     *
     * @return No return value
     */
    void manageTransition() noexcept;
    /**
     * Check if the camera transition is ended
     *
     * @return True if the camera transition is ended, false otherwise
     */
    bool transitionIsEnded() const noexcept;
    /**
     * Stop the transition movement between 2 scenes
     *
     * @return No return value
     */
    void stopTransition() noexcept;

    graphic::Renderer& renderer;
    ecs::Coordinator& coordinator;
    ecs::system::CollisionSystem& collisionSystem;
    game::Room& room;
    bool isMoving = false;
    std::unique_ptr<IScene> actualScene = nullptr;
    std::unique_ptr<IScene> lastScene = nullptr;
};

} // namespace scene
