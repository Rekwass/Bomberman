/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Renderer
*/

#pragma once

#include "ECS/Components/Camera.hpp"
#include "ECS/Core/Coordinator.hpp"
#include "ECS/Core/Entities.hpp"
#include "ECS/Systems/CameraSystem.hpp"
#include "ECS/Systems/Image2dRenderSystem.hpp"
#include "ECS/Systems/Object3dRenderSystem.hpp"
#include "ECS/Systems/Text2dRenderSystem.hpp"
#include "Vector.hpp"

namespace graphic {

/*
 * Graphic raylib renderer
 */
class Renderer {
   public:
    Renderer() noexcept = delete;
    explicit Renderer(ecs::Coordinator& coordinator, CameraMode mode = CAMERA_CUSTOM, utils::Vector position = {10, 10, 10}, utils::Vector looking = {0, 0, 0});
    Renderer(Renderer const& other) noexcept = default;
    Renderer(Renderer&& other) noexcept = default;
    ~Renderer() noexcept = default;

    Renderer& operator=(Renderer const& other) noexcept = delete;
    Renderer& operator=(Renderer&& other) noexcept = delete;

    /*
     * Set if the fps should be drawn
     *
     * No return value
     *
     * should -> Set to true if the fps should be drawn and false otherwise
     */
    void displayFPS(bool should = true) noexcept;
    /*
     * Set if the grid should be displayed
     *
     * No return value
     *
     * size -> The size of the grid
     *
     * spacing -> The spacing between lines of the grid
     *
     * should -> Set to true if the grid should be displayed and false otherwise
     */
    void display3dGrid(int size, int spacing, bool should = true) noexcept;
    /*
     * Set the cleared background color
     *
     * No return value
     *
     * color -> The color to set
     */
    void setBackgroundColor(Color color) noexcept;
    /*
     * Set the camera position
     *
     * No return value
     *
     * position -> The new position of the camera
     */
    void setCameraPosition(utils::Vector position) noexcept;
    /*
     * Set where the camera should look
     *
     * No return value
     *
     * looking -> Where the camera should look
     */
    void setCameraLooking(utils::Vector looking) noexcept;
    /*
     * Set the camera mode
     *
     * No return value
     *
     * mode -> The mode of the camera
     */
    void setCameraMode(CameraMode mode) noexcept;
    /*
     * Get the actual camera position
     *
     * Return the camera position (not a reference)
     */
    utils::Vector getCameraPosition() const noexcept;
    /*
     * Get the actual camera movement
     *
     * Return a reference to the actual camera movement
     */
    utils::Vector& getCameraMovement() const noexcept;
    /*
     * Render the registered functions
     *
     * No return value
     */
    void render() const;

   private:
    ecs::Coordinator& coordinator;
    ecs::Entity camera;
    ecs::system::CameraSystem& cameraSystem;
    ecs::system::Object3dRenderSystem& object3dRenderSystem;
    ecs::system::Image2dRenderSystem& image2dRenderSystem;
    ecs::system::Text2dRenderSystem& text2dRenderSystem;
    Color backgroundColor = BLACK;
    CameraMode mode = CAMERA_CUSTOM;
    bool shouldDisplayFPS = false;
    bool shouldDisplayGrid = false;
    int gridSize = 10;
    int gridSpacing = 1;
};

} // namespace graphic
