/*
** EPITECH PROJECT, 2022
** include
** File description:
** ServerConnectionScene
*/

#pragma once

#include "Scenes/IScene.hpp"

namespace scene {

class ServerConnectionScene final : public IScene {
   public:
    ServerConnectionScene() noexcept = delete;
    explicit ServerConnectionScene(ecs::Coordinator& coordinator);
    ServerConnectionScene(ServerConnectionScene const& other) noexcept = delete;
    ServerConnectionScene(ServerConnectionScene&& other) noexcept = delete;
    ~ServerConnectionScene() noexcept final;

    ServerConnectionScene& operator=(ServerConnectionScene const& other) noexcept = delete;
    ServerConnectionScene& operator=(ServerConnectionScene&& other) noexcept = delete;

    void update(ScenesManager& scenesManager, float dt) final;
    utils::Vector getCameraPosition() const noexcept final;
    utils::Vector getCameraLooking() const noexcept final;
    /*
     * Listening to user inputs
     *
     * No return value
     */
    void listenInputs() noexcept;
    /*
     * Do stuff while client is connecting to server
     *
     * No return value
     *
     * ScenesManager -> The scenes manager
     */
    void doConnecting(ScenesManager& scenesManager);

   private:
    ecs::Coordinator& coordinator;
    ecs::Entity title;
    ecs::Entity ip;
    ecs::Entity extra;
    std::string ipText;
    bool suffix = true;
    bool connecting = false;
    float dtBuf = 0;
    int dotNumber = 0;
};

} // namespace scene
