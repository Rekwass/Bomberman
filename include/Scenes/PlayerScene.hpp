/*
** EPITECH PROJECT, 2022
** Indie Studio
** File description:
** Main Menu Scene
*/

#pragma once

#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/RenderableImage2d.hpp"
#include "ECS/Core/Coordinator.hpp"
#include "ECS/Core/Entities.hpp"
#include "Scenes/IScene.hpp"
#include "Scenes/ScenesManager.hpp"
#include "Vector.hpp"
#include "raylib.h"

namespace scene {

class PlayerScene final : public IScene {
   public:
    PlayerScene() noexcept = delete;
    explicit PlayerScene(ecs::Coordinator& coordinator);
    PlayerScene(PlayerScene const& other) noexcept = delete;
    PlayerScene(PlayerScene&& other) noexcept = delete;
    ~PlayerScene() noexcept override;

    PlayerScene& operator=(PlayerScene const& other) noexcept = delete;
    PlayerScene& operator=(PlayerScene&& other) noexcept = delete;

    void update(ScenesManager& scenesManager, float dt) final;
    utils::Vector getCameraPosition() const noexcept final;
    utils::Vector getCameraLooking() const noexcept final;

   private:
    ecs::Coordinator& coordinator;
    ecs::Entity waiting{};
};

} // namespace scene
