/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** RendererTests
*/

#include "ECS/Core/Coordinator.hpp"
#include "Graphic/Renderer.hpp"
#include "Utils.hpp"

#include <gtest/gtest.h>

TEST(Renderer, CameraPosition)
{
    ecs::Coordinator coordinator = utils::initCoordinator();
    utils::Vector cameraPosition = {100, 200, 300};
    utils::Vector cameraPosition2 = {400, 500, 600};
    utils::Vector cameraTarget = {25, 50, 75};
    graphic::Renderer renderer(coordinator, CameraMode::CAMERA_CUSTOM, cameraPosition, cameraTarget);

    auto res = renderer.getCameraPosition();
    EXPECT_EQ(res.x, cameraPosition.x);
    EXPECT_EQ(res.y, cameraPosition.y);
    EXPECT_EQ(res.z, cameraPosition.z);

    renderer.setCameraPosition(cameraPosition2);

    auto res2 = renderer.getCameraPosition();
    EXPECT_EQ(res2.x, cameraPosition2.x);
    EXPECT_EQ(res2.y, cameraPosition2.y);
    EXPECT_EQ(res2.z, cameraPosition2.z);
}

TEST(Renderer, CameraMovement)
{
    ecs::Coordinator coordinator = utils::initCoordinator();
    utils::Vector cameraPosition = {100, 200, 300};
    utils::Vector cameraTarget = {25, 50, 75};
    utils::Vector cameraMovement = {21, 42, 84};
    graphic::Renderer renderer(coordinator, CameraMode::CAMERA_CUSTOM, cameraPosition, cameraTarget);
    renderer.getCameraMovement() = cameraMovement;
    auto& res = renderer.getCameraMovement();

    EXPECT_EQ(res.x, cameraMovement.x);
    EXPECT_EQ(res.y, cameraMovement.y);
    EXPECT_EQ(res.z, cameraMovement.z);
}
