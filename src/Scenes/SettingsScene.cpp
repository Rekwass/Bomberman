/*
** EPITECH PROJECT, 2022
** Indie Studio
** File description:
** Main Settings
*/

#include "Scenes/SettingsScene.hpp"

#include "AudioPlayer.hpp"
#include "FilePaths.hpp"
#include "Game/SettingsManager.hpp"
#include "Scenes/MainMenuScene.hpp"

#include <string>

scene::SettingsScene::SettingsScene(ecs::Coordinator& coordinator) :
    coordinator(coordinator), title(coordinator.createEntity()), fpsValue(game::SettingsManager::getFps()), fps(coordinator.createEntity()), fpsLabel(coordinator.createEntity()), fpsLeftArrow(coordinator.createEntity()), fpsRightArrow(coordinator.createEntity()), monitorValue(game::SettingsManager::getMonitor()), monitor(coordinator.createEntity()), monitorLabel(coordinator.createEntity()), monitorLeftArrow(coordinator.createEntity()), monitorRightArrow(coordinator.createEntity()), audio(coordinator.createEntity()), audioLabel(coordinator.createEntity()), audioLeftArrow(coordinator.createEntity()), audioRightArrow(coordinator.createEntity()), fullscreen(coordinator.createEntity()), fullscreenLabel(coordinator.createEntity()), fullscreenLeftArrow(coordinator.createEntity()), fullscreenRightArrow(coordinator.createEntity()), returnButton(coordinator.createEntity()), applyButton(coordinator.createEntity()), defaultButton(coordinator.createEntity()), focus(0), maxFields(0)
{
    coordinator.setComponent(this->title, ecs::component::Attributes{.position = {1230, 0, 0}});
    coordinator.setComponent(this->title, ecs::component::RenderableImage2d(fmt::format("{}Textures/Settings/Settings.png", ASSETS_PATH)));

    coordinator.setComponent(this->fps, ecs::component::Attributes{.position = {260, 290, 0}});
    coordinator.setComponent(this->fps, ecs::component::RenderableImage2d(fmt::format("{}Textures/Settings/FPS.png", ASSETS_PATH)));
    this->maxFields += 1;
    coordinator.setComponent(this->fpsLabel, ecs::component::Attributes{.position = {850, 330, 0}});
    coordinator.setComponent(this->fpsLabel, ecs::component::RenderableText2d{.text = std::to_string(game::SettingsManager::getFps()), .fontSize = 90, .color = WHITE});
    coordinator.setComponent(this->fpsLeftArrow, ecs::component::Attributes{.position = {700, 300, 0}});
    coordinator.setComponent(this->fpsLeftArrow, ecs::component::RenderableImage2d(fmt::format("{}Textures/Settings/LeftArrow.png", ASSETS_PATH)));
    coordinator.setComponent(this->fpsRightArrow, ecs::component::Attributes{.position = {1050, 300, 0}});
    coordinator.setComponent(this->fpsRightArrow, ecs::component::RenderableImage2d(fmt::format("{}Textures/Settings/RightArrow.png", ASSETS_PATH)));

    coordinator.setComponent(this->monitor, ecs::component::Attributes{.position = {260, 450, 0}});
    coordinator.setComponent(this->monitor, ecs::component::RenderableImage2d(fmt::format("{}Textures/Settings/MonitorUnselect.png", ASSETS_PATH)));
    this->maxFields += 1;
    coordinator.setComponent(this->monitorLabel, ecs::component::Attributes{.position = {850, 490, 0}});
    coordinator.setComponent(this->monitorLabel, ecs::component::RenderableText2d{.text = std::to_string(game::SettingsManager::getMonitor() + 1), .fontSize = 90, .color = WHITE});
    coordinator.setComponent(this->monitorLeftArrow, ecs::component::Attributes{.position = {700, 460, 0}});
    coordinator.setComponent(this->monitorLeftArrow, ecs::component::RenderableImage2d(fmt::format("{}Textures/Settings/LeftArrow.png", ASSETS_PATH)));
    coordinator.setComponent(this->monitorRightArrow, ecs::component::Attributes{.position = {1050, 460, 0}});
    coordinator.setComponent(this->monitorRightArrow, ecs::component::RenderableImage2d(fmt::format("{}Textures/Settings/RightArrow.png", ASSETS_PATH)));

    coordinator.setComponent(this->audio, ecs::component::Attributes{.position = {260, 610, 0}});
    coordinator.setComponent(this->audio, ecs::component::RenderableImage2d(fmt::format("{}Textures/Settings/AudioUnselect.png", ASSETS_PATH)));
    this->maxFields += 1;
    coordinator.setComponent(this->audioLabel, ecs::component::Attributes{.position = {840, 650, 0}});
    coordinator.setComponent(this->audioLabel, ecs::component::RenderableText2d{.text = (game::SettingsManager::getAudioState() ? "ON" : "OFF"), .fontSize = 90, .color = WHITE});
    coordinator.setComponent(this->audioLeftArrow, ecs::component::Attributes{.position = {700, 620, 0}});
    coordinator.setComponent(this->audioLeftArrow, ecs::component::RenderableImage2d(fmt::format("{}Textures/Settings/LeftArrow.png", ASSETS_PATH)));
    coordinator.setComponent(this->audioRightArrow, ecs::component::Attributes{.position = {1050, 620, 0}});
    coordinator.setComponent(this->audioRightArrow, ecs::component::RenderableImage2d(fmt::format("{}Textures/Settings/RightArrow.png", ASSETS_PATH)));

    coordinator.setComponent(this->fullscreen, ecs::component::Attributes{.position = {260, 770, 0}});
    coordinator.setComponent(this->fullscreen, ecs::component::RenderableImage2d(fmt::format("{}Textures/Settings/FullUnselect.png", ASSETS_PATH)));
    this->maxFields += 1;
    coordinator.setComponent(this->fullscreenLabel, ecs::component::Attributes{.position = {840, 810, 0}});
    coordinator.setComponent(this->fullscreenLabel, ecs::component::RenderableText2d{.text = (game::SettingsManager::getFullscreenState() ? "ON" : "OFF"), .fontSize = 90, .color = WHITE});
    coordinator.setComponent(this->fullscreenLeftArrow, ecs::component::Attributes{.position = {700, 780, 0}});
    coordinator.setComponent(this->fullscreenLeftArrow, ecs::component::RenderableImage2d(fmt::format("{}Textures/Settings/LeftArrow.png", ASSETS_PATH)));
    coordinator.setComponent(this->fullscreenRightArrow, ecs::component::Attributes{.position = {1050, 780, 0}});
    coordinator.setComponent(this->fullscreenRightArrow, ecs::component::RenderableImage2d(fmt::format("{}Textures/Settings/RightArrow.png", ASSETS_PATH)));

    coordinator.setComponent(this->returnButton, ecs::component::Attributes{.position = {0, 0, 0}});
    coordinator.setComponent(this->returnButton, ecs::component::RenderableImage2d(fmt::format("{}Textures/Settings/ReturnUnselect.png", ASSETS_PATH)));
    this->maxFields += 1;

    coordinator.setComponent(this->applyButton, ecs::component::Attributes{.position = {1190, 340, 0}});
    coordinator.setComponent(this->applyButton, ecs::component::RenderableImage2d(fmt::format("{}Textures/Settings/ApplyUnselect.png", ASSETS_PATH)));
    this->maxFields += 1;

    coordinator.setComponent(this->defaultButton, ecs::component::Attributes{.position = {1150, 610, 0}});
    coordinator.setComponent(this->defaultButton, ecs::component::RenderableImage2d(fmt::format("{}Textures/Settings/DefaultValuesUnselect.png", ASSETS_PATH)));
    this->maxFields += 1;
}

scene::SettingsScene::~SettingsScene() noexcept
{
    coordinator.destroyEntity(this->title);
    coordinator.destroyEntity(this->fps);
    coordinator.destroyEntity(this->fpsLabel);
    coordinator.destroyEntity(this->fpsLeftArrow);
    coordinator.destroyEntity(this->fpsRightArrow);
    coordinator.destroyEntity(this->monitor);
    coordinator.destroyEntity(this->monitorLabel);
    coordinator.destroyEntity(this->monitorLeftArrow);
    coordinator.destroyEntity(this->monitorRightArrow);
    coordinator.destroyEntity(this->audio);
    coordinator.destroyEntity(this->audioLabel);
    coordinator.destroyEntity(this->audioLeftArrow);
    coordinator.destroyEntity(this->audioRightArrow);
    coordinator.destroyEntity(this->fullscreen);
    coordinator.destroyEntity(this->fullscreenLabel);
    coordinator.destroyEntity(this->fullscreenLeftArrow);
    coordinator.destroyEntity(this->fullscreenRightArrow);
    coordinator.destroyEntity(this->returnButton);
    coordinator.destroyEntity(this->applyButton);
    coordinator.destroyEntity(this->defaultButton);
}

bool scene::SettingsScene::changeFps(int fps) noexcept
{
    if (fps < 1) {
        return false;
    }
    this->fpsValue = fps;
    this->coordinator.getComponent<ecs::component::RenderableText2d>(this->fpsLabel).text = std::to_string(this->fpsValue);
    return true;
}

void scene::SettingsScene::applyFps() noexcept
{
    game::SettingsManager::setFps(this->fpsValue);
    this->changeFps(game::SettingsManager::getFps());
}

bool scene::SettingsScene::changeMonitor(int monitorId) noexcept
{
    if (monitorId < 0) {
        return false;
    }
    this->monitorValue = monitorId;
    auto monitorCount = GetMonitorCount();
    if (this->monitorValue >= monitorCount) {
        this->monitorValue = monitorCount - 1;
    }
    this->coordinator.getComponent<ecs::component::RenderableText2d>(this->monitorLabel).text = std::to_string(this->monitorValue + 1);
    return true;
}

void scene::SettingsScene::applyMonitor() noexcept
{
    game::SettingsManager::setMonitor(this->monitorValue);
    this->changeMonitor(game::SettingsManager::getMonitor());
}

void scene::SettingsScene::changeAudio(bool state) noexcept
{
    this->audioValue = state;
    this->coordinator.getComponent<ecs::component::RenderableText2d>(this->audioLabel).text = (this->audioValue ? "ON" : "OFF");
}

void scene::SettingsScene::applyAudio() noexcept
{
    game::SettingsManager::setAudioState(this->audioValue);
    this->changeAudio(game::SettingsManager::getAudioState());
}

void scene::SettingsScene::changeFullscreen(bool state) noexcept
{
    this->fullscreenValue = state;
    this->coordinator.getComponent<ecs::component::RenderableText2d>(this->fullscreenLabel).text = (this->fullscreenValue ? "ON" : "OFF");
}

void scene::SettingsScene::applyFullscreen() noexcept
{
    game::SettingsManager::setFullscreenState(this->fullscreenValue);
    this->changeFullscreen(game::SettingsManager::getFullscreenState());
}

void scene::SettingsScene::update(scene::ScenesManager& scenesManager, float /*dt*/)
{
    if (IsKeyPressed(KEY_ENTER)) {
        switch (this->focus) {
        case 4:
            audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/Select.mp3", ASSETS_PATH));
            this->applyFps();
            this->applyAudio();
            this->applyMonitor();
            this->applyFullscreen();
            break;
        case 5:
            audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/Select.mp3", ASSETS_PATH));
            this->changeFps(60);
            this->changeMonitor(0);
            this->changeAudio(true);
            this->changeFullscreen(true);
            this->applyFps();
            this->applyAudio();
            this->applyMonitor();
            this->applyFullscreen();
            break;
        case 6:
            audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/Select.mp3", ASSETS_PATH));
            scenesManager.setScene<scene::MainMenuScene, true>(this->coordinator);
            return;
        }
    } else if (IsKeyPressed(KEY_UP)) {
        audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/MenuMove.mp3", ASSETS_PATH));
        switch (this->focus) {
        case 0:
            this->focus = maxFields - 1;
            this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->fps).setTexture(fmt::format("{}Textures/Settings/FPSUnselect.png", ASSETS_PATH));
            this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->returnButton).setTexture(fmt::format("{}Textures/Settings/Return.png", ASSETS_PATH));
            break;
        case 1:
            this->focus--;
            this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->monitor).setTexture(fmt::format("{}Textures/Settings/MonitorUnselect.png", ASSETS_PATH));
            this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->fps).setTexture(fmt::format("{}Textures/Settings/FPS.png", ASSETS_PATH));
            break;
        case 2:
            this->focus--;
            this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->audio).setTexture(fmt::format("{}Textures/Settings/AudioUnselect.png", ASSETS_PATH));
            this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->monitor).setTexture(fmt::format("{}Textures/Settings/Monitor.png", ASSETS_PATH));
            break;
        case 3:
            this->focus--;
            this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->fullscreen).setTexture(fmt::format("{}Textures/Settings/FullUnselect.png", ASSETS_PATH));
            this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->audio).setTexture(fmt::format("{}Textures/Settings/Audio.png", ASSETS_PATH));
            break;
        case 4:
            this->focus--;
            this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->applyButton).setTexture(fmt::format("{}Textures/Settings/ApplyUnselect.png", ASSETS_PATH));
            this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->fullscreen).setTexture(fmt::format("{}Textures/Settings/Full.png", ASSETS_PATH));
            break;
        case 5:
            this->focus--;
            this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->defaultButton).setTexture(fmt::format("{}Textures/Settings/DefaultValuesUnselect.png", ASSETS_PATH));
            this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->applyButton).setTexture(fmt::format("{}Textures/Settings/Apply.png", ASSETS_PATH));
            break;
        case 6:
            this->focus--;
            this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->returnButton).setTexture(fmt::format("{}Textures/Settings/ReturnUnselect.png", ASSETS_PATH));
            this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->defaultButton).setTexture(fmt::format("{}Textures/Settings/DefaultValues.png", ASSETS_PATH));
            break;
        }
    } else if (IsKeyPressed(KEY_DOWN)) {
        audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/MenuMove.mp3", ASSETS_PATH));
        switch (this->focus) {
        case 0:
            this->focus++;
            this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->fps).setTexture(fmt::format("{}Textures/Settings/FPSUnselect.png", ASSETS_PATH));
            this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->monitor).setTexture(fmt::format("{}Textures/Settings/Monitor.png", ASSETS_PATH));
            break;
        case 1:
            this->focus++;
            this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->monitor).setTexture(fmt::format("{}Textures/Settings/MonitorUnselect.png", ASSETS_PATH));
            this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->audio).setTexture(fmt::format("{}Textures/Settings/Audio.png", ASSETS_PATH));
            break;
        case 2:
            this->focus++;
            this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->audio).setTexture(fmt::format("{}Textures/Settings/AudioUnselect.png", ASSETS_PATH));
            this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->fullscreen).setTexture(fmt::format("{}Textures/Settings/Full.png", ASSETS_PATH));
            break;
        case 3:
            this->focus++;
            this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->fullscreen).setTexture(fmt::format("{}Textures/Settings/FullUnselect.png", ASSETS_PATH));
            this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->applyButton).setTexture(fmt::format("{}Textures/Settings/Apply.png", ASSETS_PATH));
            break;
        case 4:
            this->focus++;
            this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->applyButton).setTexture(fmt::format("{}Textures/Settings/ApplyUnselect.png", ASSETS_PATH));
            this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->defaultButton).setTexture(fmt::format("{}Textures/Settings/DefaultValues.png", ASSETS_PATH));
            break;
        case 5:
            this->focus++;
            this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->defaultButton).setTexture(fmt::format("{}Textures/Settings/DefaultValuesUnselect.png", ASSETS_PATH));
            this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->returnButton).setTexture(fmt::format("{}Textures/Settings/Return.png", ASSETS_PATH));
            break;
        case 6:
            this->focus = 0;
            this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->returnButton).setTexture(fmt::format("{}Textures/Settings/ReturnUnselect.png", ASSETS_PATH));
            this->coordinator.getComponent<ecs::component::RenderableImage2d>(this->fps).setTexture(fmt::format("{}Textures/Settings/FPS.png", ASSETS_PATH));
            break;
        }
    } else if (IsKeyPressed(KEY_LEFT)) {
        switch (this->focus) {
        case 0:
            if (this->changeFps(this->fpsValue - 1)) {
                audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/MenuMove.mp3", ASSETS_PATH));
            }
            break;
        case 1:
            if (this->changeMonitor(this->monitorValue - 1)) {
                audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/MenuMove.mp3", ASSETS_PATH));
            }
            break;
        case 2:
            if (this->audioValue) {
                this->changeAudio(false);
                audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/MenuMove.mp3", ASSETS_PATH));
            }
            break;
        case 3:
            if (this->fullscreenValue) {
                this->changeFullscreen(false);
                audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/MenuMove.mp3", ASSETS_PATH));
            }
            break;
        }
    } else if (IsKeyPressed(KEY_RIGHT)) {
        switch (this->focus) {
        case 0:
            this->changeFps(this->fpsValue + 1);
            audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/MenuMove.mp3", ASSETS_PATH));
            break;
        case 1:
            if (this->changeMonitor(this->monitorValue + 1)) {
                audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/MenuMove.mp3", ASSETS_PATH));
            }
            break;
        case 2:
            if (not this->audioValue) {
                this->changeAudio(true);
                audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/MenuMove.mp3", ASSETS_PATH));
            }
            break;
        case 3:
            if (not this->fullscreenValue) {
                this->changeFullscreen(true);
                audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/MenuMove.mp3", ASSETS_PATH));
            }
            break;
        }
    }
}

utils::Vector scene::SettingsScene::getCameraPosition() const noexcept
{
    return utils::Vector{-15, 20, 10};
}

utils::Vector scene::SettingsScene::getCameraLooking() const noexcept
{
    return utils::Vector{-40, 20, 11};
}
