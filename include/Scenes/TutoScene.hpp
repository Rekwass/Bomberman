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

class TutoScene final : public IScene {
   public:
    TutoScene() noexcept = delete;
    explicit TutoScene(ecs::Coordinator& coordinator);
    TutoScene(TutoScene const& other) noexcept = delete;
    TutoScene(TutoScene&& other) noexcept = delete;
    ~TutoScene() noexcept override;

    TutoScene& operator=(TutoScene const& other) noexcept = delete;
    TutoScene& operator=(TutoScene&& other) noexcept = delete;

    void update(ScenesManager& scenesManager, float dt) final;
    utils::Vector getCameraPosition() const noexcept final;
    utils::Vector getCameraLooking() const noexcept final;

   private:
    ecs::Coordinator& coordinator;
    ecs::Entity returnButton{};
    ecs::Entity tuto{};
};

} // namespace scene
