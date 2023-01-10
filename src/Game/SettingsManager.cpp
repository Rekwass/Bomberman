/*
** EPITECH PROJECT, 2022
** src
** File description:
** SettingsManager
*/

#include "Game/SettingsManager.hpp"

#include "AudioPlayer.hpp"
#include "FilePaths.hpp"
#include "IndieError.hpp"
#include "Game/Map/MapReader.hpp"
#include "nlohmann/json.hpp"
#include "raylib.h"

#include <fstream>

std::unique_ptr<game::SettingsManager> game::SettingsManager::instance = nullptr;

game::SettingsManager::SettingsManager(ecs::Coordinator& coordinator) :
    coordinator(coordinator)
{
    if (game::MapReader::doesExist(SETTINGS_PATH)) {
        std::ifstream reader(SETTINGS_PATH.data());
        nlohmann::json json;
        reader >> json;
        if (json.contains("FPS")) {
            this->fps = json.at("FPS").get<int>();
        }
        if (json.contains("Screen")) {
            this->monitor = json.at("Screen").get<int>();
        }
        if (json.contains("Audio")) {
            this->audio = json.at("Audio").get<bool>();
        }
        if (json.contains("FullScreen")) {
            this->fullscreen = json.at("FullScreen").get<bool>();
        }
    }

    this->applyFps();
    this->applyAudio();
    this->applyFullscreen();
    this->applyMonitor();
}

game::SettingsManager::~SettingsManager() noexcept
{
    std::ofstream writer(SETTINGS_PATH.data());
    nlohmann::json json = {
        {"FPS", this->fps},
        {"Screen", this->monitor},
        {"Audio", this->audio},
        {"FullScreen", this->fullscreen}};
    writer << std::setw(4) << json << std::endl;
}

void game::SettingsManager::init(ecs::Coordinator& coordinator) noexcept
{
    instance.reset(new SettingsManager(coordinator));
}

int game::SettingsManager::getFps() noexcept
{
    if (instance == nullptr) {
        return 60;
    }
    return instance->fps;
}

int game::SettingsManager::getMonitor() noexcept
{
    if (instance == nullptr) {
        return 0;
    }
    return instance->monitor;
}

bool game::SettingsManager::getAudioState() noexcept
{
    if (instance == nullptr) {
        return true;
    }
    return instance->audio;
}

bool game::SettingsManager::getFullscreenState() noexcept
{
    if (instance == nullptr) {
        return true;
    }
    return instance->fullscreen;
}

void game::SettingsManager::setFps(int fps) noexcept
{
    if (instance != nullptr and fps > 0) {
        instance->fps = fps;
        instance->applyFps();
    }
}

void game::SettingsManager::setMonitor(int monitorId) noexcept
{
    if (instance != nullptr and monitorId < GetMonitorCount()) {
        instance->monitor = monitorId;
        instance->applyMonitor();
    }
}

void game::SettingsManager::setAudioState(bool state) noexcept
{
    if (instance != nullptr) {
        instance->audio = state;
        instance->applyAudio();
    }
}

void game::SettingsManager::setFullscreenState(bool state) noexcept
{
    if (instance != nullptr) {
        instance->fullscreen = state;
        instance->applyFullscreen();
    }
}

void game::SettingsManager::applyFps() const noexcept
{
    SetTargetFPS(this->fps);
}

void game::SettingsManager::applyMonitor() const noexcept
{
    SetWindowMonitor(this->monitor);
}

void game::SettingsManager::applyAudio() const noexcept
{
    this->coordinator.sendEvent((this->audio ? ecs::Events::AUDIO_ON : ecs::Events::AUDIO_OFF));
}

void game::SettingsManager::applyFullscreen() const noexcept
{
    this->coordinator.sendEvent((this->fullscreen ? ecs::Events::FULLSCREEN_ON : ecs::Events::FULLSCREEN_OFF));
}
