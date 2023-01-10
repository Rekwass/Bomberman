/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** ScenesManager
*/

#include "Scenes/ScenesManager.hpp"

#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/RenderableImage2d.hpp"
#include "ECS/Components/RenderableText2d.hpp"
#include "FilePaths.hpp"
#include "Randomizer.hpp"

scene::ScenesManager::ScenesManager(graphic::Renderer& renderer, game::Room& room, ecs::system::CollisionSystem& collisionSystem, ecs::Coordinator& coordinator) noexcept :
    renderer(renderer), room(room), collisionSystem(collisionSystem), coordinator(coordinator)
{
}

void scene::ScenesManager::update(float dt)
{
    if (this->lastScene) {
        this->lastScene.reset(nullptr);
    }
    this->manageTransition();
    if (this->actualScene) {
        this->actualScene->update(*this, dt);
    }
}

void scene::ScenesManager::manageTransition() noexcept
{
    if (this->actualScene and not this->isMoving) {
        this->isMoving = true;
        this->initTransition();
    }
    if (this->isMoving and this->actualScene and this->transitionIsEnded()) {
        this->stopTransition();
    }
    this->renderer.setCameraLooking(this->actualScene->getCameraLooking());
}

void scene::ScenesManager::initTransition() noexcept
{
    if (not this->actualScene) {
        return;
    }
    auto& cameraMovement = this->renderer.getCameraMovement();
    cameraMovement = this->actualScene->getCameraPosition() - this->renderer.getCameraPosition();
}

void scene::ScenesManager::stopTransition() noexcept
{
    this->renderer.setCameraPosition(this->actualScene->getCameraPosition());
    this->renderer.setCameraLooking(this->actualScene->getCameraLooking());

    this->renderer.getCameraMovement() = {0, 0, 0};
    this->isMoving = false;
}

static bool checkCameraXPosition(utils::Vector cameraDestination, utils::Vector cameraMovement, utils::Vector cameraPosition)
{
    if (cameraMovement.x > 0 and (cameraPosition.x < cameraDestination.x)) {
        return false;
    }
    return (not(cameraMovement.x < 0 and (cameraPosition.x > cameraDestination.x)));
}

static bool checkCameraYPosition(utils::Vector cameraDestination, utils::Vector cameraMovement, utils::Vector cameraPosition)
{
    if (cameraMovement.y > 0 and (cameraPosition.y < cameraDestination.y)) {
        return false;
    }
    return (not(cameraMovement.y < 0 and (cameraPosition.y > cameraDestination.y)));
}

static bool checkCameraZPosition(utils::Vector cameraDestination, utils::Vector cameraMovement, utils::Vector cameraPosition)
{
    if (cameraMovement.z > 0 and (cameraPosition.z < cameraDestination.z)) {
        return false;
    }
    return (not(cameraMovement.z < 0 and (cameraPosition.z > cameraDestination.z)));
}

bool scene::ScenesManager::transitionIsEnded() const noexcept
{
    auto cameraDestination = this->actualScene->getCameraPosition();
    auto cameraMovement = this->renderer.getCameraMovement();
    auto cameraPosition = this->renderer.getCameraPosition();

    return (checkCameraXPosition(cameraDestination, cameraMovement, cameraPosition) and checkCameraYPosition(cameraDestination, cameraMovement, cameraPosition) and checkCameraZPosition(cameraDestination, cameraMovement, cameraPosition));
}

void scene::ScenesManager::drawWaitingScreen()
{
    static std::vector<std::string> tips = {"Throwing bombs at somebody have never been a good solution...", "Code on Windows is not that funny (ask Ben).", "Design is never a less important work.", "One day the AIs will not suicide themselves...", "In order to win, you must be at least good !", "Never trust an enemy player ! You might be taken by surprise...", "Try to sleep one day (or be a true g@m3rz).", "Soccer or coding, you must take a decision !", "Heard this goddamn song too much !! I can't play this game anymore...", "Pretty nice SFX, isn't it !?"};

    ecs::Entity title = this->coordinator.createEntity();
    ecs::Entity text = this->coordinator.createEntity();
    ecs::Entity image = this->coordinator.createEntity();

    this->coordinator.setComponent(image, ecs::component::RenderableImage2d(fmt::format("{}Textures/Loading.png", ASSETS_PATH)));
    auto& imageComponent = this->coordinator.getComponent<ecs::component::RenderableImage2d>(image);
    auto imageSize = imageComponent.getSize();
    this->coordinator.setComponent(image, ecs::component::Attributes{.position = {30, 910 - imageSize.y}});

    this->coordinator.setComponent(title, ecs::component::RenderableText2d{.text = "Tips", .fontSize = 50, .color = ORANGE});
    this->coordinator.setComponent(title, ecs::component::Attributes{.position = {30, 920}});

    this->coordinator.setComponent(text, ecs::component::RenderableText2d{.text = tips.at(utils::Randomizer::getRandomNumber<int>(0, tips.size() - 1)), .fontSize = 30, .color = DARKPURPLE});
    this->coordinator.setComponent(text, ecs::component::Attributes{.position = {50, 980}});

    this->renderer.render();

    this->coordinator.destroyEntity(title);
    this->coordinator.destroyEntity(text);
    this->coordinator.destroyEntity(image);
}
