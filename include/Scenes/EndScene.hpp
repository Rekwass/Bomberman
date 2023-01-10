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
#include "ECS/Components/RenderableObject3d.hpp"
#include "ECS/Components/RenderableText2d.hpp"
#include "ECS/Core/Coordinator.hpp"
#include "ECS/Core/Entities.hpp"
#include "Game/Map/Player/APlayer.hpp"
#include "Game/Room.hpp"
#include "Scenes/IScene.hpp"
#include "Scenes/ScenesManager.hpp"
#include "Vector.hpp"
#include "raylib.h"

namespace scene {

class EndScene : public IScene {
   public:
    EndScene() noexcept = delete;
    EndScene(game::Room& room, ecs::Coordinator& coordinator, std::vector<std::unique_ptr<game::APlayer>> players);
    EndScene(EndScene const& other) noexcept = delete;
    EndScene(EndScene&& other) noexcept = delete;
    ~EndScene() noexcept override;

    EndScene& operator=(EndScene const& other) noexcept = delete;
    EndScene& operator=(EndScene&& other) noexcept = delete;

    void update(ScenesManager& scenesManager, float dt) final;
    utils::Vector getCameraPosition() const noexcept final;
    utils::Vector getCameraLooking() const noexcept final;

   private:
    ecs::Coordinator& coordinator;
    ecs::Entity title{};
    ecs::Entity text{};
    std::vector<std::unique_ptr<game::APlayer>> players;
    ecs::Entity menu{};
    ecs::Entity credits{};
    ecs::Entity theme{};
};

} // namespace scene
