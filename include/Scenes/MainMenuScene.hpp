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
#include "Game/Room.hpp"
#include "Scenes/IScene.hpp"
#include "Scenes/ScenesManager.hpp"
#include "Vector.hpp"
#include "raylib.h"

#include <vector>

namespace scene {

class MainMenuScene final : public IScene {
   public:
    MainMenuScene() noexcept = delete;
    explicit MainMenuScene(game::Room& room, ecs::Coordinator& coordinator);
    MainMenuScene(MainMenuScene const& other) noexcept = delete;
    MainMenuScene(MainMenuScene&& other) noexcept = delete;
    ~MainMenuScene() noexcept override;

    MainMenuScene& operator=(MainMenuScene const& other) noexcept = delete;
    MainMenuScene& operator=(MainMenuScene&& other) noexcept = delete;

    void update(ScenesManager& scenesManager, float dt) final;
    utils::Vector getCameraPosition() const noexcept final;
    utils::Vector getCameraLooking() const noexcept final;

   private:
    ecs::Coordinator& coordinator;
    ecs::Entity title{};
    ecs::Entity lSolo{};
    ecs::Entity lMulti{};
    ecs::Entity oMulti{};
    ecs::Entity settings{};
    ecs::Entity h2p{};
    ecs::Entity theme{};
    int focus;
    int maxFields;
};

} // namespace scene
