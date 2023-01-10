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
#include "Game/Map/MapReader.hpp"
#include "Scenes/IScene.hpp"
#include "Scenes/ScenesManager.hpp"
#include "Vector.hpp"
#include "raylib.h"

namespace scene {

class MultiPlayerSelectionScene final : public IScene {
   public:
    MultiPlayerSelectionScene() noexcept = delete;
    MultiPlayerSelectionScene(game::Room& room, ecs::Coordinator& coordinator, std::string_view path);
    MultiPlayerSelectionScene(MultiPlayerSelectionScene const& other) noexcept = delete;
    MultiPlayerSelectionScene(MultiPlayerSelectionScene&& other) noexcept = delete;
    ~MultiPlayerSelectionScene() noexcept override;

    MultiPlayerSelectionScene& operator=(MultiPlayerSelectionScene const& other) noexcept = delete;
    MultiPlayerSelectionScene& operator=(MultiPlayerSelectionScene&& other) noexcept = delete;

    void update(ScenesManager& scenesManager, float dt) final;
    utils::Vector getCameraPosition() const noexcept final;
    utils::Vector getCameraLooking() const noexcept final;

   private:
    ecs::Coordinator& coordinator;
    ecs::Entity title{};
    ecs::Entity bomberman{};
    ecs::Entity bomberman2{};
    ecs::Entity left{};
    ecs::Entity right{};
    ecs::Entity left2{};
    ecs::Entity right2{};
    ecs::Entity choose{};
    game::MapReader mapReader;
    std::vector<std::string> textures;
    int selectedTexture1 = 0;
    int selectedTexture2 = 0;
};

} // namespace scene
