/*
** EPITECH PROJECT, 2022
** Indie Studio
** File description:
** Main Menu
*/

#include "Scenes/PlayerSelectionScene.hpp"

#include "AudioPlayer.hpp"
#include "ECS/Components/Animation.hpp"
#include "ECS/Components/Music.hpp"
#include "ECS/Components/RenderableObject3d.hpp"
#include "FilePaths.hpp"
#include "Scenes/GameScene.hpp"
#include "raylib.h"

#include <utility>

scene::PlayerSelectionScene::PlayerSelectionScene(game::Room& room, ecs::Coordinator& coordinator, std::string_view path) :
    coordinator(coordinator), title(this->coordinator.createEntity()), bomberman(this->coordinator.createEntity()), left(this->coordinator.createEntity()), right(this->coordinator.createEntity()), choose(this->coordinator.createEntity()), mapReader(std::string{path}, room.getMapSize())
{
    this->textures = this->mapReader.getPlayersInfos().textures;

    coordinator.setComponent(this->title, ecs::component::Attributes{.position = {510, 0, 0}, .scale = 1});
    coordinator.setComponent(this->title, ecs::component::RenderableImage2d(fmt::format("{}Textures/PlayerSelection/PlayerSelection.png", ASSETS_PATH)));

    coordinator.setComponent(this->bomberman, ecs::component::Attributes{.position = {-15, 0.75, 23.5}, .scale = 3});
    coordinator.setComponent(this->bomberman, ecs::component::RenderableObject3d(this->mapReader.getPlayersInfos().model.modelPath, this->mapReader.getPlayersInfos().textures.at(this->selectedTexture)));
    coordinator.setComponent(this->bomberman, ecs::component::Animation(this->mapReader.getPlayersInfos().model.animationPath, 8, this->mapReader.getPlayersInfos().model.animationFps));
    auto& animation = this->coordinator.getComponent<ecs::component::Animation>(this->bomberman);
    animation.addAnimation(1);
    animation.loop(1);

    coordinator.setComponent(this->left, ecs::component::Attributes{.position = {500, 510, 0}});
    coordinator.setComponent(this->left, ecs::component::RenderableImage2d(fmt::format("{}Textures/PlayerSelection/LeftArrow.png", ASSETS_PATH)));

    coordinator.setComponent(this->right, ecs::component::Attributes{.position = {1300, 510, 0}});
    coordinator.setComponent(this->right, ecs::component::RenderableImage2d(fmt::format("{}Textures/PlayerSelection/RightArrow.png", ASSETS_PATH)));

    coordinator.setComponent(this->choose, ecs::component::Attributes{.position = {730, 810, 0}});
    coordinator.setComponent(this->choose, ecs::component::RenderableImage2d(fmt::format("{}Textures/PlayerSelection/Choose.png", ASSETS_PATH)));
}

scene::PlayerSelectionScene::~PlayerSelectionScene() noexcept
{
    coordinator.destroyEntity(this->title);
    coordinator.destroyEntity(this->bomberman);
    coordinator.destroyEntity(this->left);
    coordinator.destroyEntity(this->right);
    coordinator.destroyEntity(this->choose);
}

void scene::PlayerSelectionScene::update(scene::ScenesManager& scenesManager, float /*dt*/)
{
    if (IsKeyPressed(KEY_LEFT)) {
        if (this->selectedTexture > 0) {
            audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/MenuMove.mp3", ASSETS_PATH));
            this->selectedTexture--;
            game::PlayersManager::setPlayerTexture(1, this->textures.at(this->selectedTexture));
            this->coordinator.getComponent<ecs::component::RenderableObject3d>(this->bomberman).setTexture(this->textures.at(this->selectedTexture));
            auto& animation = this->coordinator.getComponent<ecs::component::Animation>(this->bomberman);
            animation.clear(false, false);
            animation.addAnimation(7, false);
        }
    }
    if (IsKeyPressed(KEY_RIGHT)) {
        if (this->selectedTexture < this->textures.size() - 1) {
            audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/MenuMove.mp3", ASSETS_PATH));
            this->selectedTexture++;
            game::PlayersManager::setPlayerTexture(1, this->textures.at(this->selectedTexture));
            this->coordinator.getComponent<ecs::component::RenderableObject3d>(this->bomberman).setTexture(this->textures.at(this->selectedTexture));
            auto& animation = this->coordinator.getComponent<ecs::component::Animation>(this->bomberman);
            animation.clear(false, false);
            animation.addAnimation(7, false);
        }
    }
    if (IsKeyPressed(KEY_ENTER)) {
        audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/Select.mp3", ASSETS_PATH));
        game::PlayersManager::setPlayerTexture(1, this->textures.at(this->selectedTexture));
        scenesManager.setScene<scene::GameScene, true, true, true>(this->coordinator, std::move(this->mapReader));
    }
}

utils::Vector scene::PlayerSelectionScene::getCameraPosition() const noexcept
{
    return utils::Vector{-30, 5, 30};
}

utils::Vector scene::PlayerSelectionScene::getCameraLooking() const noexcept
{
    return utils::Vector{40, 0, 0};
}
