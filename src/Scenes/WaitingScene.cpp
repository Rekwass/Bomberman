/*
** EPITECH PROJECT, 2022
** src
** File description:
** WaitingScene
*/

#include "Scenes/WaitingScene.hpp"

#include "AudioPlayer.hpp"
#include "ECS/Components/Animation.hpp"
#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/RenderableImage2d.hpp"
#include "ECS/Components/RenderableObject3d.hpp"
#include "ECS/Components/RenderableText2d.hpp"
#include "FilePaths.hpp"
#include "Network/Client.hpp"
#include "Scenes/GameScene.hpp"
#include "Scenes/ScenesManager.hpp"

#include <iostream>

scene::WaitingScene::WaitingScene(game::Room& room, ecs::Coordinator& coordinator) :
    coordinator(coordinator), title(coordinator.createEntity()), player1(coordinator.createEntity()), player2(coordinator.createEntity()), player3(coordinator.createEntity()), player4(coordinator.createEntity()), online1Ready(coordinator.createEntity()), online2Ready(coordinator.createEntity()), online3Ready(coordinator.createEntity()), online4Ready(coordinator.createEntity()), ready(coordinator.createEntity()), beReadyText(coordinator.createEntity()), mapReader(network::Client::getConfig(), room.getMapSize(), false)
{
    network::Client::setInLobby();

    std::string modelPath = this->mapReader.getPlayersInfos().model.modelPath;
    std::string animationPath = this->mapReader.getPlayersInfos().model.animationPath;
    int animationFps = this->mapReader.getPlayersInfos().model.animationFps;

    coordinator.setComponent(this->title, ecs::component::Attributes{.position = {350, 50, 0}});
    coordinator.setComponent(this->title, ecs::component::RenderableImage2d(fmt::format("{}Textures/Waiting/Title.png", ASSETS_PATH)));

    coordinator.setComponent(this->online1Ready, ecs::component::Attributes{.position = {490, 570, 0}, .scale = 0.6});
    coordinator.setComponent(this->player1, ecs::component::Attributes{.position = {65, 15, 0}, .scale = 3});
    coordinator.setComponent(this->player1, ecs::component::RenderableObject3d(modelPath, ""));
    coordinator.setComponent(this->player1, ecs::component::Animation(animationPath, 8, animationFps));

    coordinator.setComponent(this->online2Ready, ecs::component::Attributes{.position = {710, 620, 0}, .scale = 0.6});
    coordinator.setComponent(this->player2, ecs::component::Attributes{.position = {65, 15, 12.6}, .scale = 3});
    coordinator.setComponent(this->player2, ecs::component::RenderableObject3d(modelPath, ""));
    coordinator.setComponent(this->player2, ecs::component::Animation(animationPath, 8, animationFps));

    coordinator.setComponent(this->online3Ready, ecs::component::Attributes{.position = {980, 690, 0}, .scale = 0.6});
    coordinator.setComponent(this->player3, ecs::component::Attributes{.position = {65, 15, 25.3}, .scale = 3});
    coordinator.setComponent(this->player3, ecs::component::RenderableObject3d(modelPath, ""));
    coordinator.setComponent(this->player3, ecs::component::Animation(animationPath, 8, animationFps));

    coordinator.setComponent(this->online4Ready, ecs::component::Attributes{.position = {1320, 770, 0}, .scale = 0.6});
    coordinator.setComponent(this->player4, ecs::component::Attributes{.position = {65, 15, 38}, .scale = 3});
    coordinator.setComponent(this->player4, ecs::component::RenderableObject3d(modelPath, ""));
    coordinator.setComponent(this->player4, ecs::component::Animation(animationPath, 8, animationFps));

    coordinator.setComponent(this->ready, ecs::component::Attributes{.position = {700, 900, 0}});
    coordinator.setComponent(this->ready, ecs::component::RenderableImage2d(fmt::format("{}Textures/Waiting/UnReady.png", ASSETS_PATH)));

    coordinator.setComponent(this->beReadyText, ecs::component::Attributes{.position = {500, 850, 0}});
    coordinator.setComponent(this->beReadyText, ecs::component::RenderableText2d{.text = "Press space when ready", .fontSize = 60, .color = WHITE});

    this->textures = this->mapReader.getPlayersInfos().textures;

    this->players.at(0) = this->player1;
    this->players.at(1) = this->player2;
    this->players.at(2) = this->player3;
    this->players.at(3) = this->player4;
    this->readies.at(0) = this->online1Ready;
    this->readies.at(1) = this->online2Ready;
    this->readies.at(2) = this->online3Ready;
    this->readies.at(3) = this->online4Ready;

    this->player = players.at(network::Client::getId() - 1);
    this->playerId = network::Client::getId();

    this->setPresent(this->playerId);
    this->changeTexture(this->playerId, this->textures.at(this->selectedTexture));

    game::PlayersManager::setPlayerType(1, game::PlayerType::NETWORK);
    game::PlayersManager::setPlayerType(2, game::PlayerType::NETWORK);
    game::PlayersManager::setPlayerType(3, game::PlayerType::NETWORK);
    game::PlayersManager::setPlayerType(4, game::PlayerType::NETWORK);
    game::PlayersManager::setPlayerType(this->playerId, game::PlayerType::KEYBOARD);
    game::PlayersManager::setPlayerKeys(this->playerId, {.moveUp = KEY_W, .moveDown = KEY_S, .moveLeft = KEY_A, .moveRight = KEY_D, .putBomb = KEY_SPACE});
}

scene::WaitingScene::~WaitingScene() noexcept
{
    this->coordinator.destroyEntity(this->title);
    this->coordinator.destroyEntity(this->player1);
    this->coordinator.destroyEntity(this->player2);
    this->coordinator.destroyEntity(this->player3);
    this->coordinator.destroyEntity(this->player4);
    this->coordinator.destroyEntity(this->online1Ready);
    this->coordinator.destroyEntity(this->online2Ready);
    this->coordinator.destroyEntity(this->online3Ready);
    this->coordinator.destroyEntity(this->online4Ready);
    this->coordinator.destroyEntity(this->ready);
    this->coordinator.destroyEntity(this->beReadyText);
}

utils::Vector scene::WaitingScene::getCameraPosition() const noexcept
{
    return {25, 35, 45};
}

utils::Vector scene::WaitingScene::getCameraLooking() const noexcept
{
    return {75, 15, 17};
}

void scene::WaitingScene::changeTexture(game::PlayerId id, const std::string& filePath) noexcept
{
    auto player = players.at(id - 1);

    if (id == this->playerId) {
        network::Client::setTexture(filePath);
    }
    this->coordinator.getComponent<ecs::component::RenderableObject3d>(player).setTexture(filePath);
    game::PlayersManager::setPlayerTexture(id, filePath);

    auto& animation = this->coordinator.getComponent<ecs::component::Animation>(player);
    animation.clear(false, false);
    animation.addAnimation(7, false);

    this->playersTextures.at(id - 1) = filePath;
}

void scene::WaitingScene::setReady(game::PlayerId id) noexcept
{
    if (id == this->playerId) {
        this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->ready).setTexture(fmt::format("{}Textures/Waiting/Ready.png", ASSETS_PATH));
    }
    auto& animation = this->coordinator.getComponent<ecs::component::Animation>(players.at(id - 1));
    animation.clear(false, false);
    animation.addAnimation(7, false);

    this->playersReadies.at(id - 1) = true;

    this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->readies.at(id - 1)).setTexture(fmt::format("{}Textures/Waiting/PlayerReady.png", ASSETS_PATH));
}

void scene::WaitingScene::setUnready(game::PlayerId id) noexcept
{
    if (id == this->playerId) {
        this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->ready).setTexture(fmt::format("{}Textures/Waiting/UnReady.png", ASSETS_PATH));
    }
    auto& animation = this->coordinator.getComponent<ecs::component::Animation>(players.at(id - 1));
    animation.clear(false, false);
    animation.addAnimation(8, false);

    this->playersReadies.at(id - 1) = false;

    this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->readies.at(id - 1)).setTexture(fmt::format("{}Textures/Waiting/PlayerUnready.png", ASSETS_PATH));
}

void scene::WaitingScene::setPresent(game::PlayerId id) noexcept
{
    auto& animation = this->coordinator.getComponent<ecs::component::Animation>(players.at(id - 1));
    animation.addAnimation(1);
    animation.loop(1);

    this->playersPresences.at(id - 1) = true;

    if (id != this->playerId) {
        this->coordinator.setComponent(this->readies.at(id - 1), ecs::component::RenderableImage2d(fmt::format("{}Textures/Waiting/PlayerUnready.png", ASSETS_PATH)));
    }
}

void scene::WaitingScene::setNotPresent(game::PlayerId id) noexcept
{
    auto player = players.at(id - 1);

    auto& animation = this->coordinator.getComponent<ecs::component::Animation>(player);
    animation.clear(false, false);
    animation.clear();

    this->coordinator.getComponent<ecs::component::RenderableObject3d>(player).setTexture("");

    this->playersPresences.at(id - 1) = false;

    if (id != this->playerId) {
        this->coordinator.removeComponent<ecs::component::RenderableImage2d>(this->readies.at(id - 1));
    }
}

void scene::WaitingScene::watchChangesOnline() noexcept
{
    for (game::PlayerId id = 1; id < 5; id++) {
        if (id != this->playerId) {
            auto present = network::Client::isPlayerPresent(id);
            if (present and not this->playersPresences.at(id - 1)) {
                std::cout << "One of the online just connect" << std::endl;
                this->setPresent(id);
            } else if (not present and this->playersPresences.at(id - 1)) {
                std::cout << "One of the online disconnect" << std::endl;
                this->setNotPresent(id);
            }

            if (this->playersPresences.at(id - 1)) {
                auto texture = network::Client::getPlayerTexture(id);
                if (texture != this->playersTextures.at(id - 1)) {
                    std::cout << "One of the online texture changed to " << texture << std::endl;
                    this->changeTexture(id, texture);
                }

                auto ready = network::Client::isPlayerReady(id);
                if (ready and not this->playersReadies.at(id - 1)) {
                    std::cout << "One of the online get ready" << std::endl;
                    this->setReady(id);
                } else if (not ready and this->playersReadies.at(id - 1)) {
                    std::cout << "One of the online get unready" << std::endl;
                    this->setUnready(id);
                }
            }
        }
    }
}

void scene::WaitingScene::update(ScenesManager& scenesManager, float /*dt*/)
{
    this->watchChangesOnline();
    if (IsKeyPressed(KEY_SPACE)) {
        audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/Select.mp3", ASSETS_PATH));
        if (this->isReady) {
            this->setUnready(this->playerId);
        } else {
            this->setReady(this->playerId);
        }
        this->isReady = not this->isReady;
        network::Client::setReady(this->isReady);
    }
    if (not this->isReady and IsKeyPressed(KEY_LEFT)) {
        if (this->selectedTexture > 0) {
            audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/MenuMove.mp3", ASSETS_PATH));
            this->selectedTexture--;
            this->changeTexture(network::Client::getId(), this->textures.at(this->selectedTexture));
        }
    }
    if (not this->isReady and IsKeyPressed(KEY_RIGHT)) {
        if (this->selectedTexture < this->textures.size() - 1) {
            audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/MenuMove.mp3", ASSETS_PATH));
            this->selectedTexture++;
            this->changeTexture(network::Client::getId(), this->textures.at(this->selectedTexture));
        }
    }
    if (this->isReady and std::all_of(this->playersReadies.begin(), this->playersReadies.end(), [](bool ready) { return ready; })) {
        scenesManager.setScene<scene::GameScene, true, true, true>(this->coordinator, this->mapReader);
    }
}
