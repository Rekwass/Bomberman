/*
** EPITECH PROJECT, 2022
** src
** File description:
** ServerConnectionScene
*/

#include "Scenes/ServerConnectionScene.hpp"

#include "AudioPlayer.hpp"
#include "Clock.hpp"
#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/RenderableImage2d.hpp"
#include "ECS/Components/RenderableText2d.hpp"
#include "FilePaths.hpp"
#include "Network/Client.hpp"
#include "Scenes/ScenesManager.hpp"
#include "Scenes/WaitingScene.hpp"

#include <cctype>
#include <iostream>

scene::ServerConnectionScene::ServerConnectionScene(ecs::Coordinator& coordinator) :
    coordinator(coordinator), title(coordinator.createEntity()), ip(coordinator.createEntity())
{
    coordinator.setComponent(this->title, ecs::component::Attributes{.position = {200, 50, 0}});
    coordinator.setComponent(this->title, ecs::component::RenderableImage2d(fmt::format("{}Textures/ServerConnection/Title.png", ASSETS_PATH)));

    coordinator.setComponent(this->ip, ecs::component::Attributes{.position = {700, 300, 0}});
    coordinator.setComponent(this->ip, ecs::component::RenderableText2d{.text = "> ", .fontSize = 80, .color = WHITE});

    this->extra = this->coordinator.createEntity();
    this->coordinator.setComponent(this->extra, ecs::component::Attributes{.position = {1200, 530, 0}});
    this->coordinator.setComponent(this->extra, ecs::component::RenderableText2d{.fontSize = 65});
}

scene::ServerConnectionScene::~ServerConnectionScene() noexcept
{
    this->coordinator.destroyEntity(this->title);
    this->coordinator.destroyEntity(this->ip);
    this->coordinator.destroyEntity(this->extra);
}

void scene::ServerConnectionScene::listenInputs() noexcept
{
    static constexpr float suffixDelay = 0.4;

    if (this->dtBuf >= suffixDelay) {
        while (this->dtBuf >= suffixDelay) {
            this->dtBuf -= suffixDelay;
        }
        this->suffix = not this->suffix;
    }

    if (IsKeyPressed(KEY_ZERO) or IsKeyPressed(KEY_KP_0)) {
        this->ipText.push_back('0');
    }
    if (IsKeyPressed(KEY_ONE) or IsKeyPressed(KEY_KP_1)) {
        this->ipText.push_back('1');
    }
    if (IsKeyPressed(KEY_TWO) or IsKeyPressed(KEY_KP_2)) {
        this->ipText.push_back('2');
    }
    if (IsKeyPressed(KEY_THREE) or IsKeyPressed(KEY_KP_3)) {
        this->ipText.push_back('3');
    }
    if (IsKeyPressed(KEY_FOUR) or IsKeyPressed(KEY_KP_4)) {
        this->ipText.push_back('4');
    }
    if (IsKeyPressed(KEY_FIVE) or IsKeyPressed(KEY_KP_5)) {
        this->ipText.push_back('5');
    }
    if (IsKeyPressed(KEY_SIX) or IsKeyPressed(KEY_KP_6)) {
        this->ipText.push_back('6');
    }
    if (IsKeyPressed(KEY_SEVEN) or IsKeyPressed(KEY_KP_7)) {
        this->ipText.push_back('7');
    }
    if (IsKeyPressed(KEY_EIGHT) or IsKeyPressed(KEY_KP_8)) {
        this->ipText.push_back('8');
    }
    if (IsKeyPressed(KEY_NINE) or IsKeyPressed(KEY_KP_9)) {
        this->ipText.push_back('9');
    }
    if (IsKeyPressed(KEY_PERIOD) or IsKeyPressed(KEY_KP_DECIMAL)) {
        this->ipText.push_back('.');
    }
    if (IsKeyPressed(KEY_BACKSPACE)) {
        if (not this->ipText.empty()) {
            this->ipText.pop_back();
        }
    }
    if ((IsKeyPressed(KEY_ENTER) or IsKeyPressed(KEY_KP_ENTER)) and (not this->ipText.empty() and (std::isdigit(this->ipText.back()) != 0 and std::isdigit(this->ipText.front()) != 0))) {
        audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/Select.mp3", ASSETS_PATH));
        auto& text = this->coordinator.getComponent<ecs::component::RenderableText2d>(this->extra);
        text.text = fmt::format("Connecting to\n'{}'", this->ipText);
        text.color = BLUE;
        this->dotNumber = 0;
        this->connecting = true;
        network::Client::tryConnecting(this->ipText);
    }
    this->coordinator.getComponent<ecs::component::RenderableText2d>(this->ip).text = fmt::format("> {}{}", this->ipText, (this->suffix ? "_" : ""));
}

void scene::ServerConnectionScene::doConnecting(ScenesManager& scenesManager)
{
    static constexpr float dotDelay = 0.2;

    if (network::Client::isConnected()) {
        scenesManager.setScene<scene::WaitingScene, true>(this->coordinator);
        this->connecting = false;
    }
    if (network::Client::failedToConnect()) {
        auto& text = this->coordinator.getComponent<ecs::component::RenderableText2d>(this->extra);
        text.text = fmt::format("Failed to connect to\n'{}'", this->ipText);
        text.color = RED;
        this->connecting = false;
    }

    if (this->dtBuf >= dotDelay) {
        while (this->dtBuf >= dotDelay) {
            this->dtBuf -= dotDelay;
        }
        this->dotNumber++;
        if (this->dotNumber > 3) {
            this->dotNumber = 0;
        }
        this->coordinator.getComponent<ecs::component::RenderableText2d>(this->extra).text = fmt::format("Connecting to\n'{}'{:.>{}}", this->ipText, "", this->dotNumber);
    }
}

void scene::ServerConnectionScene::update(ScenesManager& scenesManager, float dt)
{
    this->dtBuf += dt;

    if (not this->connecting) {
        this->listenInputs();
    } else {
        this->doConnecting(scenesManager);
    }
}

utils::Vector scene::ServerConnectionScene::getCameraPosition() const noexcept
{
    return {40, 28, 80};
}

utils::Vector scene::ServerConnectionScene::getCameraLooking() const noexcept
{
    return {60, 10, 60};
}
