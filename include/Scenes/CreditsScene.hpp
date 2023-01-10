/*
** EPITECH PROJECT, 2022
** Indie Studio
** File description:
** Main Menu Scene
*/

#pragma once

#include "Clock.hpp"
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

class CreditsScene : public IScene {
   public:
    CreditsScene() noexcept = delete;
    explicit CreditsScene(ecs::Coordinator& coordinator);
    CreditsScene(CreditsScene const& other) noexcept = delete;
    CreditsScene(CreditsScene&& other) noexcept = delete;
    ~CreditsScene() noexcept override;

    CreditsScene& operator=(CreditsScene const& other) noexcept = delete;
    CreditsScene& operator=(CreditsScene&& other) noexcept = delete;

    void update(ScenesManager& scenesManager, float dt) final;
    utils::Vector getCameraPosition() const noexcept final;
    utils::Vector getCameraLooking() const noexcept final;

   private:
    ecs::Coordinator& coordinator;
    ecs::Entity background{};
    ecs::Entity credits{};
    utils::Clock clock;
    bool end = false;
};

} // namespace scene
