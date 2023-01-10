/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Renderer
*/

#include "Graphic/Renderer.hpp"

#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/RenderableImage2d.hpp"
#include "ECS/Components/RenderableObject3d.hpp"
#include "ECS/Components/RenderableText2d.hpp"
#include "ECS/Components/Transform.hpp"
#include "Graphic/HitboxDisplayer.hpp"
#include "Graphic/PointDisplayer.hpp"

graphic::Renderer::Renderer(ecs::Coordinator& coordinator, CameraMode mode, utils::Vector cameraPosition, utils::Vector cameraLooking) :
    coordinator(coordinator), cameraSystem(coordinator.registerSystem<ecs::system::CameraSystem, ecs::component::Camera>()), object3dRenderSystem(coordinator.registerSystem<ecs::system::Object3dRenderSystem, ecs::component::Attributes, ecs::component::RenderableObject3d>()), image2dRenderSystem(coordinator.registerSystem<ecs::system::Image2dRenderSystem, ecs::component::Attributes, ecs::component::RenderableImage2d>()), text2dRenderSystem(coordinator.registerSystem<ecs::system::Text2dRenderSystem, ecs::component::Attributes, ecs::component::RenderableText2d>()), mode(mode)
{
    this->camera = coordinator.createEntity();
    coordinator.setComponent(camera, ecs::component::Attributes{.position = cameraPosition});
    coordinator.setComponent(camera, ecs::component::Transform{});
    coordinator.setComponent(camera, ecs::component::Camera{{.position = cameraPosition, .target = cameraLooking, .up = {0, 1, 0}, .fovy = 45, .projection = CAMERA_PERSPECTIVE}});

    auto& camera = coordinator.getComponent<ecs::component::Camera>(this->camera);
    SetCameraMode(camera.camera, mode);
    if (this->mode != CAMERA_CUSTOM) {
        camera.usingSpecialMode = true;
    }
}

void graphic::Renderer::displayFPS(bool should) noexcept
{
    this->shouldDisplayFPS = should;
}

void graphic::Renderer::display3dGrid(int size, int spacing, bool should) noexcept
{
    this->shouldDisplayGrid = should;
    this->gridSize = size;
    this->gridSpacing = spacing;
}

void graphic::Renderer::setBackgroundColor(Color color) noexcept
{
    this->backgroundColor = color;
}

void graphic::Renderer::render() const
{
    cameraSystem.update(this->coordinator);

    auto& camera = this->coordinator.getComponent<ecs::component::Camera>(this->camera);

    graphic::PointDisplayer::addPoint({camera.camera.target.x, camera.camera.target.y, camera.camera.target.z});

    BeginDrawing();
    {
        ClearBackground(this->backgroundColor);

        BeginMode3D(camera.camera);
        {
            if (shouldDisplayGrid) {
                DrawGrid(this->gridSize, this->gridSpacing);
            }

            this->object3dRenderSystem.update(this->coordinator);

            graphic::HitboxDisplayer::display();
            graphic::PointDisplayer::display();
        }
        EndMode3D();

        this->image2dRenderSystem.update(coordinator);
        this->text2dRenderSystem.update(coordinator);
        if (this->shouldDisplayFPS) {
            DrawFPS(10, 10);
        }
    }
    EndDrawing();
}

void graphic::Renderer::setCameraPosition(utils::Vector position) noexcept
{
    this->coordinator.getComponent<ecs::component::Attributes>(this->camera).position = position;

    auto& camera = coordinator.getComponent<ecs::component::Camera>(this->camera);

    camera.camera.position = position;
    if (this->mode != CAMERA_CUSTOM) {
        SetCameraMode(camera.camera, this->mode);
    }
}

void graphic::Renderer::setCameraLooking(utils::Vector looking) noexcept
{
    auto& camera = coordinator.getComponent<ecs::component::Camera>(this->camera);

    camera.camera.target = looking;
    if (this->mode != CAMERA_CUSTOM) {
        SetCameraMode(camera.camera, this->mode);
    }
}

void graphic::Renderer::setCameraMode(CameraMode mode) noexcept
{
    this->mode = mode;
    auto& camera = coordinator.getComponent<ecs::component::Camera>(this->camera);

    camera.camera = {.up = {0, 1, 0}, .fovy = 45, .projection = CAMERA_PERSPECTIVE};
    camera.usingSpecialMode = (mode != CAMERA_CUSTOM);
    SetCameraMode(camera.camera, this->mode);
}

utils::Vector graphic::Renderer::getCameraPosition() const noexcept
{
    auto& pos = coordinator.getComponent<ecs::component::Camera>(this->camera).camera.position;

    return {pos.x, pos.y, pos.z};
}

utils::Vector& graphic::Renderer::getCameraMovement() const noexcept
{
    return this->coordinator.getComponent<ecs::component::Transform>(this->camera).movement;
}
