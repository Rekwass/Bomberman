/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Main
*/

#include "Clock.hpp"
#include "ECS/Components/Animation.hpp"
#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/Bounds3d.hpp"
#include "ECS/Components/RenderableObject3d.hpp"
#include "ECS/Components/Transform.hpp"
#include "ECS/Core/Coordinator.hpp"
#include "ECS/ECSErrors.hpp"
#include "ECS/Systems/AnimationSystem.hpp"
#include "ECS/Systems/MusicSystem.hpp"
#include "ECS/Systems/Object3dBoundsSystem.hpp"
#include "ECS/Systems/TransformSystem.hpp"
#include "FilePaths.hpp"
#include "Game/Map/Error.hpp"
#include "Game/PlayersManager.hpp"
#include "Game/Room.hpp"
#include "Game/SettingsManager.hpp"
#include "Graphic/HitboxDisplayer.hpp"
#include "Graphic/PointDisplayer.hpp"
#include "Graphic/Renderer.hpp"
#include "Graphic/Window.hpp"
#include "IndieError.hpp"
#include "Scenes/CreditsScene.hpp"
#include "Utils.hpp"
#include "raylib.h"

#include <chrono>
#include <cstdlib>
#include <iostream>

int main(int ac, const char* av[])
{
    if (utils::checkUsage(ac, av)) {
        return 0;
    }
    utils::setRaylibLogLevel();

    try {
#if defined linux
        // NOLINTNEXTLINE
        if (std::getenv("DISPLAY") == nullptr) {
            throw error::IndieError("DISPLAY environment variable not found");
        }
#endif
        ecs::Coordinator coordinator = utils::initCoordinator();

        auto& animationSystem = coordinator.registerSystem<ecs::system::AnimationSystem, ecs::component::Animation, ecs::component::RenderableObject3d>();
        auto& transformSystem = coordinator.registerSystem<ecs::system::TransformSystem, ecs::component::Attributes, ecs::component::Transform>();
        auto& object3dBoundsSystem = coordinator.registerSystem<ecs::system::Object3dBoundsSystem, ecs::component::Attributes, ecs::component::RenderableObject3d, ecs::component::Bounds3d>();
        auto& collisionSystem = coordinator.registerSystem<ecs::system::CollisionSystem, ecs::component::Transform, ecs::component::Bounds3d>();
        auto& musicSystem = coordinator.registerSystem<ecs::system::MusicSystem>();

        graphic::Window window("Bomberman", 60);
        window.setWindowLogo(fmt::format("{}Textures/Logo.png", ASSETS_PATH));
        graphic::Renderer renderer(coordinator, CAMERA_CUSTOM, {0, 100, 0});

        game::Room room(coordinator);
        scene::ScenesManager sceneManager(renderer, room, collisionSystem, coordinator);
        sceneManager.setScene<scene::CreditsScene>(coordinator);
        utils::initEventsListeners(coordinator, renderer, window);
        game::SettingsManager::init(coordinator);
        utils::Clock clock;

        float dt = 0;

        while (not window.shouldClose()) {
            clock.saveTimePoint();

            utils::checkKeyboardInputs(coordinator);

            graphic::HitboxDisplayer::clear();
            graphic::PointDisplayer::clear();

            animationSystem.update(coordinator, dt); // ICI MARCHE PO
            object3dBoundsSystem.update(coordinator);
            collisionSystem.update(coordinator, dt);
            transformSystem.update(coordinator, dt);
            sceneManager.update(dt);
            renderer.render();
            musicSystem.update(coordinator);

            dt = clock.getElapsedTime() / 1000;
        }
#if defined linux
    } catch (const error::IndieError& e) {
        std::cerr << e.what() << std::endl;
        return 84;
#endif
    } catch (const ecs::error::ComponentError& e) {
        std::cerr << "The component '" << e.which() << "' failed because '" << e.what() << "'" << std::endl;
        return 84;
    } catch (const ecs::error::ECSError& e) {
        std::cerr << "An error occurred in the ECS: " << e.what() << std::endl;
        return 84;
    } catch (const error::MapLoaderError& e) {
        std::cerr << "The map with config file is invalid:" << std::endl
                  << e.what() << "'" << std::endl;
        return 84;
    }
    return 0;
}
