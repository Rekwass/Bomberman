/*
** EPITECH PROJECT, 2022
** Indie Studio
** File description:
** Main Menu
*/

#include "Scenes/IntroScene.hpp"

#include "AudioPlayer.hpp"
#include "ECS/Components/Music.hpp"
#include "ECS/Components/RenderableText2d.hpp"
#include "FilePaths.hpp"
#include "Scenes/MainMenuScene.hpp"

scene::IntroScene::IntroScene(ecs::Coordinator& coordinator) :
    coordinator(coordinator), title(this->coordinator.createEntity()), bomberman(this->coordinator.createEntity()), bomberman2(this->coordinator.createEntity()), space(this->coordinator.createEntity()), theme(this->coordinator.createEntity())
{
    coordinator.setComponent(this->title, ecs::component::Attributes{.position = {510, 0, 0}, .scale = 1});
    coordinator.setComponent(this->title, ecs::component::RenderableImage2d(fmt::format("{}Textures/Intro/BomberTek.png", ASSETS_PATH)));

    coordinator.setComponent(this->bomberman, ecs::component::Attributes{.position = {1300, 390, 0}});
    coordinator.setComponent(this->bomberman, ecs::component::RenderableImage2d(fmt::format("{}Textures/Intro/Player.png", ASSETS_PATH)));

    coordinator.setComponent(this->bomberman2, ecs::component::Attributes{.position = {-10, 210, 0}});
    coordinator.setComponent(this->bomberman2, ecs::component::RenderableImage2d(fmt::format("{}Textures/Intro/Player2.png", ASSETS_PATH)));

    coordinator.setComponent(this->space, ecs::component::Attributes{.position = {700, 950, 0}});
    coordinator.setComponent(this->space, ecs::component::RenderableText2d{.text = "Press SPACE to continue", .fontSize = 40});

    coordinator.setComponent(this->theme, ecs::component::MusicObject(fmt::format("{}audio/Musics/Intro.mp3", ASSETS_PATH)));
    this->coordinator.getComponent<ecs::component::MusicObject>(this->theme).play();
}

scene::IntroScene::~IntroScene() noexcept
{
    coordinator.destroyEntity(this->title);
    coordinator.destroyEntity(this->bomberman);
    coordinator.destroyEntity(this->bomberman2);
    coordinator.destroyEntity(this->space);
    coordinator.destroyEntity(this->theme);
}

void scene::IntroScene::update(scene::ScenesManager& scenesManager, float /*dt*/)
{
    if (IsKeyPressed(KEY_SPACE)) {
        this->coordinator.getComponent<ecs::component::MusicObject>(this->theme).pause();
        audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/Select.mp3", ASSETS_PATH));
        scenesManager.setScene<scene::MainMenuScene, true>(this->coordinator);
    }
}

utils::Vector scene::IntroScene::getCameraPosition() const noexcept
{
    return utils::Vector{-300, 150, 300};
}

utils::Vector scene::IntroScene::getCameraLooking() const noexcept
{
    return utils::Vector{101, 100, -100};
}
