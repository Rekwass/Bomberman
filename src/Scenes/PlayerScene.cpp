/*
** EPITECH PROJECT, 2022
** Indie Studio
** File description:
** Main Menu
*/

#include "Scenes/PlayerScene.hpp"

#include "FilePaths.hpp"
#include "Scenes/GameScene.hpp"

scene::PlayerScene::PlayerScene(ecs::Coordinator& coordinator) :
    coordinator(coordinator), waiting(this->coordinator.createEntity())
{
    coordinator.setComponent(this->waiting, ecs::component::Attributes{.position = {700, 50, 0}});
    coordinator.setComponent(this->waiting, ecs::component::RenderableImage2d(fmt::format("{}Textures/Waiting/Waiting.png", ASSETS_PATH)));
}

scene::PlayerScene::~PlayerScene() noexcept
{
    coordinator.destroyEntity(this->waiting);
}

void scene::PlayerScene::update(scene::ScenesManager& scenesManager, float /*dt*/)
{
    if (IsKeyPressed(KEY_ENTER)) {
        // scenesManager.setScene<scene::GameScene, true, true, true>(this->coordinator, "playerscenePath");
    }
}

utils::Vector scene::PlayerScene::getCameraPosition() const noexcept
{
    return utils::Vector{40, 28, 80};
}

utils::Vector scene::PlayerScene::getCameraLooking() const noexcept
{
    return utils::Vector{60, 10, 60};
}
