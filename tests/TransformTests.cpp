/*
** EPITECH PROJECT, 2022
** Indie Studio
** File description:
** Transform Tests
*/

#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/RenderableImage2d.hpp"
#include "ECS/Components/Transform.hpp"
#include "ECS/Core/Coordinator.hpp"
#include "ECS/Systems/TransformSystem.hpp"
#include "Utils.hpp"
#include "raylib.h"

#include <gtest/gtest.h>

// NOLINTNEXTLINE
TEST(ECS, CheckTransformMovement)
{
    ecs::Coordinator coordinator = utils::initCoordinator();
    auto& transformSystem = coordinator.registerSystem<ecs::system::TransformSystem, ecs::component::Attributes, ecs::component::Transform>();
    ecs::Entity tEntity = coordinator.createEntity();
    coordinator.setComponent(tEntity, ecs::component::Attributes{});
    coordinator.setComponent(tEntity, ecs::component::Transform{});
    coordinator.setComponent(tEntity, ecs::component::RenderableImage2d("assets/Textures/Lose/Lose.png"));

    utils::Vector pos = coordinator.getComponent<ecs::component::Attributes>(tEntity).position;
    EXPECT_EQ(pos.x, 0);
    EXPECT_EQ(pos.y, 0);
    EXPECT_EQ(pos.z, 0);

    coordinator.getComponent<ecs::component::Attributes>(tEntity).position = {100, 200, 300};
    transformSystem.update(coordinator, 0);

    utils::Vector newPos = coordinator.getComponent<ecs::component::Attributes>(tEntity).position;
    EXPECT_EQ(newPos.x, 100);
    EXPECT_EQ(newPos.y, 200);
    EXPECT_EQ(newPos.z, 300);
}

// NOLINTNEXTLINE
TEST(ECS, CheckTransformScale)
{
    ecs::Coordinator coordinator = utils::initCoordinator();
    auto& transformSystem = coordinator.registerSystem<ecs::system::TransformSystem, ecs::component::Attributes, ecs::component::Transform>();
    ecs::Entity tEntity = coordinator.createEntity();
    coordinator.setComponent(tEntity, ecs::component::Attributes{});
    coordinator.setComponent(tEntity, ecs::component::Transform{});
    coordinator.setComponent(tEntity, ecs::component::RenderableImage2d("assets/Textures/Lose/Lose.png"));

    int scale = coordinator.getComponent<ecs::component::Attributes>(tEntity).scale;
    EXPECT_EQ(scale, 1);

    coordinator.getComponent<ecs::component::Attributes>(tEntity).scale = 2;
    transformSystem.update(coordinator, 0);

    int newScale = coordinator.getComponent<ecs::component::Attributes>(tEntity).scale;
    EXPECT_EQ(newScale, 2);
}

// NOLINTNEXTLINE
TEST(ECS, CheckTransformRotationAxisAndAngle)
{
    ecs::Coordinator coordinator = utils::initCoordinator();
    auto& transformSystem = coordinator.registerSystem<ecs::system::TransformSystem, ecs::component::Attributes, ecs::component::Transform>();
    ecs::Entity tEntity = coordinator.createEntity();
    coordinator.setComponent(tEntity, ecs::component::Attributes{});
    coordinator.setComponent(tEntity, ecs::component::Transform{});
    coordinator.setComponent(tEntity, ecs::component::RenderableImage2d("assets/Textures/Lose/Lose.png"));

    utils::Vector axis = coordinator.getComponent<ecs::component::Attributes>(tEntity).rotationAxis;
    int angle = coordinator.getComponent<ecs::component::Attributes>(tEntity).rotationAngle;
    EXPECT_EQ(axis.x, 0);
    EXPECT_EQ(axis.y, 0);
    EXPECT_EQ(axis.z, 0);
    EXPECT_EQ(angle, 0);

    coordinator.getComponent<ecs::component::Attributes>(tEntity).rotationAxis = {28, 36, 42};
    coordinator.getComponent<ecs::component::Attributes>(tEntity).rotationAngle = 21;
    transformSystem.update(coordinator, 0);

    utils::Vector newAxis = coordinator.getComponent<ecs::component::Attributes>(tEntity).rotationAxis;
    int newAngle = coordinator.getComponent<ecs::component::Attributes>(tEntity).rotationAngle;
    EXPECT_EQ(newAxis.x, 28);
    EXPECT_EQ(newAxis.y, 36);
    EXPECT_EQ(newAxis.z, 42);
    EXPECT_EQ(newAngle, 21);
}
