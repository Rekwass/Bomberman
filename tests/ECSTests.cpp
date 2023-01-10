/*
** EPITECH PROJECT, 2022
** indie studio
** File description:
** ECS Tests
*/

#include "ECS/Core/Coordinator.hpp"
#include "Graphic/Renderer.hpp"
#include "Scenes/MainMenuScene.hpp"
#include "Scenes/ScenesManager.hpp"
#include "Utils.hpp"
#include "Graphic/Window.hpp"
#include "raylib.h"

#include <gtest/gtest.h>

// NOLINTNEXTLINE
TEST(Coordinator, Creation)
{
    // NOLINTNEXTLINE
    EXPECT_NO_THROW(
        ecs::Coordinator coordinator = utils::initCoordinator(););
}

// NOLINTNEXTLINE
TEST(Coordinator, CheckKeyboardInput)
{
    ecs::Coordinator coordinator = utils::initCoordinator();
    // NOLINTNEXTLINE
    EXPECT_NO_THROW(
        utils::checkKeyboardInputs(coordinator););
}

// TEST(System, TransformSystemCreation)
// {
// EXPECT_NO_THROW(
// auto& transformSystem = coordinator.registerSystem<ecs::system::TransformSystem, ecs::component::Attributes, ecs::component::Transform>();
// );
// }

// NOLINTNEXTLINE
// TEST(Coordinator, CreateRendererAndSceneManager)
//{
//    ecs::Coordinator coordinator = utils::initCoordinator();
//    // NOLINTNEXTLINE
//    EXPECT_NO_THROW(
//        graphic::Window window("Bomberman", 60);
//        window.setMaximized();
//
//        graphic::Renderer renderer(coordinator, CameraMode::CAMERA_CUSTOM);
//        scene::ScenesManager sceneManager(renderer);
//        sceneManager.setScene<graphic::MainMenuScene>(coordinator);
//        renderer.setBackgroundColor(RED););
//}
