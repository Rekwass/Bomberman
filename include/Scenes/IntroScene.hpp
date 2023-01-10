/*
** EPITECH PROJECT, 2022
** Indie Studio
** File description:
** Main Menu Scene
*/

#pragma once

#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/Music.hpp"
#include "ECS/Components/RenderableImage2d.hpp"
#include "ECS/Core/Coordinator.hpp"
#include "ECS/Core/Entities.hpp"
#include "Scenes/IScene.hpp"
#include "Scenes/ScenesManager.hpp"
#include "Vector.hpp"
#include "raylib.h"

namespace scene {

class IntroScene final : public IScene {
   public:
    IntroScene() noexcept = delete;
    explicit IntroScene(ecs::Coordinator& coordinator);
    IntroScene(IntroScene const& other) noexcept = delete;
    IntroScene(IntroScene&& other) noexcept = delete;
    ~IntroScene() noexcept override;

    IntroScene& operator=(IntroScene const& other) noexcept = delete;
    IntroScene& operator=(IntroScene&& other) noexcept = delete;

    void update(ScenesManager& scenesManager, float dt) final;
    utils::Vector getCameraPosition() const noexcept final;
    utils::Vector getCameraLooking() const noexcept final;

   private:
    ecs::Coordinator& coordinator;
    ecs::Entity title{};
    ecs::Entity bomberman{};
    ecs::Entity bomberman2{};
    ecs::Entity space{};
    ecs::Entity theme{};
};

} // namespace scene
