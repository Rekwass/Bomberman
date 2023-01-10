/*
** EPITECH PROJECT, 2022
** Indie Studio
** File description:
** Transform Tests
*/

#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/Bounds3d.hpp"
#include "ECS/Components/Transform.hpp"
#include "ECS/Core/Coordinator.hpp"
#include "ECS/Systems/CollisionSystem.hpp"
#include "Utils.hpp"
#include "raylib.h"

#include <gtest/gtest.h>

// NOLINTNEXTLINE
TEST(ECS, CheckCollision)
{
    ecs::Coordinator coordinator = utils::initCoordinator();
    auto& collisionSystem = coordinator.registerSystem<ecs::system::CollisionSystem, ecs::component::Transform, ecs::component::Bounds3d>();
    ecs::Entity tEntity = coordinator.createEntity();
    coordinator.setComponent(tEntity, ecs::component::Attributes{});
    coordinator.setComponent(tEntity, ecs::component::Transform{});
    coordinator.setComponent(tEntity, ecs::component::Bounds3d{});

    utils::Vector min;
    min.x = coordinator.getComponent<ecs::component::Bounds3d>(tEntity).min.x;
    min.y = coordinator.getComponent<ecs::component::Bounds3d>(tEntity).min.y;
    min.z = coordinator.getComponent<ecs::component::Bounds3d>(tEntity).min.z;
    utils::Vector max;
    max.x = coordinator.getComponent<ecs::component::Bounds3d>(tEntity).max.x;
    max.y = coordinator.getComponent<ecs::component::Bounds3d>(tEntity).max.y;
    max.z = coordinator.getComponent<ecs::component::Bounds3d>(tEntity).max.z;
    EXPECT_EQ(min.x, 0);
    EXPECT_EQ(min.y, 0);
    EXPECT_EQ(min.z, 0);
    EXPECT_EQ(max.x, 0);
    EXPECT_EQ(max.y, 0);
    EXPECT_EQ(max.z, 0);

    coordinator.getComponent<ecs::component::Bounds3d>(tEntity).min = {100, 200, 300};
    coordinator.getComponent<ecs::component::Bounds3d>(tEntity).max = {1, 2, 3};
    collisionSystem.update(coordinator, 0);

    utils::Vector newMin;
    newMin.x = coordinator.getComponent<ecs::component::Bounds3d>(tEntity).min.x;
    newMin.y = coordinator.getComponent<ecs::component::Bounds3d>(tEntity).min.y;
    newMin.z = coordinator.getComponent<ecs::component::Bounds3d>(tEntity).min.z;
    utils::Vector newMax;
    newMax.x = coordinator.getComponent<ecs::component::Bounds3d>(tEntity).max.x;
    newMax.y = coordinator.getComponent<ecs::component::Bounds3d>(tEntity).max.y;
    newMax.z = coordinator.getComponent<ecs::component::Bounds3d>(tEntity).max.z;
    EXPECT_EQ(newMin.x, 100);
    EXPECT_EQ(newMin.y, 200);
    EXPECT_EQ(newMin.z, 300);
    EXPECT_EQ(newMax.x, 1);
    EXPECT_EQ(newMax.y, 2);
    EXPECT_EQ(newMax.z, 3);
}
