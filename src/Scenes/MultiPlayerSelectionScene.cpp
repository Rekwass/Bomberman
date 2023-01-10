/*
** EPITECH PROJECT, 2022
** Indie Studio
** File description:
** Main Menu
*/

#include "Scenes/MultiPlayerSelectionScene.hpp"

#include "AudioPlayer.hpp"
#include "ECS/Components/Music.hpp"
#include "ECS/Components/RenderableImage2d.hpp"
#include "ECS/Components/RenderableObject3d.hpp"
#include "FilePaths.hpp"
#include "Scenes/GameScene.hpp"
#include "raylib.h"

#include <utility>

scene::MultiPlayerSelectionScene::MultiPlayerSelectionScene(game::Room& room, ecs::Coordinator& coordinator, std::string_view path) :
    coordinator(coordinator), title(this->coordinator.createEntity()), bomberman(this->coordinator.createEntity()), bomberman2(this->coordinator.createEntity()), left(this->coordinator.createEntity()), right(this->coordinator.createEntity()), left2(this->coordinator.createEntity()), right2(this->coordinator.createEntity()), choose(this->coordinator.createEntity()), mapReader(std::string{path}, room.getMapSize())
{
    this->textures = this->mapReader.getPlayersInfos().textures;

    coordinator.setComponent(this->title, ecs::component::Attributes{.position = {510, 0, 0}, .scale = 1});
    coordinator.setComponent(this->title, ecs::component::RenderableImage2d(fmt::format("{}Textures/MultiPlayerSelection/PlayerSelection.png", ASSETS_PATH)));

    coordinator.setComponent(this->bomberman, ecs::component::Attributes{.position = {-18, 0.75, 17.5}, .rotationAxis = {0, 1, 0}, .rotationAngle = 65, .scale = 3});
    coordinator.setComponent(this->bomberman, ecs::component::RenderableObject3d(this->mapReader.getPlayersInfos().model.modelPath, this->mapReader.getPlayersInfos().textures.at(this->selectedTexture1)));
    coordinator.setComponent(this->bomberman, ecs::component::Animation(this->mapReader.getPlayersInfos().model.animationPath, 8, this->mapReader.getPlayersInfos().model.animationFps));
    auto& animation1 = this->coordinator.getComponent<ecs::component::Animation>(this->bomberman);
    animation1.addAnimation(1);
    animation1.loop(1);

    coordinator.setComponent(this->bomberman2, ecs::component::Attributes{.position = {-13, 0.75, 29.5}, .rotationAxis = {0, 1, 0}, .rotationAngle = -30, .scale = 3});
    coordinator.setComponent(this->bomberman2, ecs::component::RenderableObject3d(this->mapReader.getPlayersInfos().model.modelPath, this->mapReader.getPlayersInfos().textures.at(this->selectedTexture2)));
    coordinator.setComponent(this->bomberman2, ecs::component::Animation(this->mapReader.getPlayersInfos().model.animationPath, 8, this->mapReader.getPlayersInfos().model.animationFps));
    auto& animation2 = this->coordinator.getComponent<ecs::component::Animation>(this->bomberman2);
    animation2.addAnimation(1);
    animation2.loop(1);

    coordinator.setComponent(this->left, ecs::component::Attributes{.position = {20, 510, 0}});
    coordinator.setComponent(this->left, ecs::component::RenderableImage2d(fmt::format("{}Textures/MultiPlayerSelection/LeftArrow.png", ASSETS_PATH)));

    coordinator.setComponent(this->right, ecs::component::Attributes{.position = {700, 510, 0}});
    coordinator.setComponent(this->right, ecs::component::RenderableImage2d(fmt::format("{}Textures/MultiPlayerSelection/RightArrow.png", ASSETS_PATH)));

    coordinator.setComponent(this->left2, ecs::component::Attributes{.position = {1100, 510, 0}});
    coordinator.setComponent(this->left2, ecs::component::RenderableImage2d(fmt::format("{}Textures/MultiPlayerSelection/LeftArrow.png", ASSETS_PATH)));

    coordinator.setComponent(this->right2, ecs::component::Attributes{.position = {1800, 510, 0}});
    coordinator.setComponent(this->right2, ecs::component::RenderableImage2d(fmt::format("{}Textures/MultiPlayerSelection/RightArrow.png", ASSETS_PATH)));

    coordinator.setComponent(this->choose, ecs::component::Attributes{.position = {730, 810, 0}});
    coordinator.setComponent(this->choose, ecs::component::RenderableImage2d(fmt::format("{}Textures/MultiPlayerSelection/Choose.png", ASSETS_PATH)));
}

scene::MultiPlayerSelectionScene::~MultiPlayerSelectionScene() noexcept
{
    coordinator.destroyEntity(this->title);
    coordinator.destroyEntity(this->bomberman);
    coordinator.destroyEntity(this->bomberman2);
    coordinator.destroyEntity(this->left);
    coordinator.destroyEntity(this->right);
    coordinator.destroyEntity(this->left2);
    coordinator.destroyEntity(this->right2);
    coordinator.destroyEntity(this->choose);
}

void scene::MultiPlayerSelectionScene::update(scene::ScenesManager& scenesManager, float /*dt*/)
{
    if (IsKeyPressed(KEY_A)) {
        if (this->selectedTexture1 > 0) {
            audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/MenuMove.mp3", ASSETS_PATH));
            this->selectedTexture1--;
            game::PlayersManager::setPlayerTexture(1, this->textures.at(this->selectedTexture1));
            this->coordinator.getComponent<ecs::component::RenderableObject3d>(this->bomberman).setTexture(this->textures.at(this->selectedTexture1));
            auto& animation = this->coordinator.getComponent<ecs::component::Animation>(this->bomberman);
            animation.clear(false, false);
            animation.addAnimation(7, false);
        }
    }
    if (IsKeyPressed(KEY_D)) {
        if (this->selectedTexture1 < this->textures.size() - 1) {
            audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/MenuMove.mp3", ASSETS_PATH));
            this->selectedTexture1++;
            game::PlayersManager::setPlayerTexture(1, this->textures.at(this->selectedTexture1));
            this->coordinator.getComponent<ecs::component::RenderableObject3d>(this->bomberman).setTexture(this->textures.at(this->selectedTexture1));
            auto& animation = this->coordinator.getComponent<ecs::component::Animation>(this->bomberman);
            animation.clear(false, false);
            animation.addAnimation(7, false);
        }
    }
    if (IsKeyPressed(KEY_LEFT)) {
        if (this->selectedTexture2 > 0) {
            audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/MenuMove.mp3", ASSETS_PATH));
            this->selectedTexture2--;
            game::PlayersManager::setPlayerTexture(2, this->textures.at(this->selectedTexture2));
            this->coordinator.getComponent<ecs::component::RenderableObject3d>(this->bomberman2).setTexture(this->textures.at(this->selectedTexture2));
            auto& animation = this->coordinator.getComponent<ecs::component::Animation>(this->bomberman2);
            animation.clear(false, false);
            animation.addAnimation(7, false);
        }
    }
    if (IsKeyPressed(KEY_RIGHT)) {
        if (this->selectedTexture2 < this->textures.size() - 1) {
            audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/MenuMove.mp3", ASSETS_PATH));
            this->selectedTexture2++;
            game::PlayersManager::setPlayerTexture(2, this->textures.at(this->selectedTexture2));
            this->coordinator.getComponent<ecs::component::RenderableObject3d>(this->bomberman2).setTexture(this->textures.at(this->selectedTexture2));
            auto& animation = this->coordinator.getComponent<ecs::component::Animation>(this->bomberman2);
            animation.clear(false, false);
            animation.addAnimation(7, false);
        }
    }
    if (IsKeyPressed(KEY_ENTER)) {
        audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/Select.mp3", ASSETS_PATH));
        game::PlayersManager::setPlayerTexture(1, this->textures.at(this->selectedTexture1));
        game::PlayersManager::setPlayerTexture(2, this->textures.at(this->selectedTexture2));
        scenesManager.setScene<scene::GameScene, true, true, true>(this->coordinator, this->mapReader);
    }
}

utils::Vector scene::MultiPlayerSelectionScene::getCameraPosition() const noexcept
{
    return utils::Vector{-30, 5, 30};
}

utils::Vector scene::MultiPlayerSelectionScene::getCameraLooking() const noexcept
{
    return utils::Vector{40, 0, 0};
}
