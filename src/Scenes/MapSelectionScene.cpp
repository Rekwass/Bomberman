/*
** EPITECH PROJECT, 2022
** Indie Studio
** File description:
** Main Menu
*/

#include "Scenes/MapSelectionScene.hpp"

#include "AudioPlayer.hpp"
#include "ECS/Components/RenderableText2d.hpp"
#include "FilePaths.hpp"
#include "Scenes/GameScene.hpp"
#include "Scenes/MainMenuScene.hpp"
#include "Scenes/MultiPlayerSelectionScene.hpp"
#include "Scenes/PlayerSelectionScene.hpp"

#include <ostream>

static bool stringEndWith(const std::string_view str, const std::string_view ext)
{
    size_t file = str.find(ext.data());

    if (str.length() <= ext.length() or file == std::string_view::npos) {
        return false;
    }
    return file == str.length() - ext.length();
}

std::vector<std::string> readFilesInDir(std::string_view path, std::string_view ext)
{
    std::vector<std::string> files = {};
    std::string fileName;

    try {
        std::filesystem::exists(path.data());
    } catch (const std::filesystem::filesystem_error&) {
        return files;
    }

    for (const std::filesystem::path& file :
        std::filesystem::directory_iterator(path.data())) {
        fileName = file.string();
        if (stringEndWith(fileName, ext.data())) {
            size_t start = fileName.find_last_of('/');
            size_t end = fileName.find_last_of('.');
            files.emplace_back(fileName.substr(start + 1, end - start - 1));
        }
    }
    if (files.empty()) {
        std::string error = "Missing libraries in '";
        error.append(path.data());
        error.append("'.");
    }
    return files;
}

scene::MapSelectionScene::MapSelectionScene(ecs::Coordinator& coordinator, int type) :
    coordinator(coordinator), title(this->coordinator.createEntity()), paths(readFilesInDir(MAPS_PATH, ".json")), current(this->coordinator.createEntity()), map(this->coordinator.createEntity()), type(type)
{
    coordinator.setComponent(this->title, ecs::component::Attributes{.position = {510, 0, 0}, .scale = 1});
    coordinator.setComponent(this->title, ecs::component::RenderableImage2d(fmt::format("{}Textures/MapSelection/BomberTek.png", ASSETS_PATH)));

    coordinator.setComponent(this->current, ecs::component::Attributes{.position = {910, 610, 0}});
    coordinator.setComponent(this->current, ecs::component::RenderableText2d{.text = paths[1], .fontSize = 120});

    coordinator.setComponent(this->map, ecs::component::Attributes{.position = {610, 600, 0}, .scale = 1});
    coordinator.setComponent(this->map, ecs::component::RenderableImage2d(fmt::format("{}Textures/MapSelection/Map.png", ASSETS_PATH)));
}

scene::MapSelectionScene::~MapSelectionScene() noexcept
{
    coordinator.destroyEntity(this->title);
    coordinator.destroyEntity(this->current);
    coordinator.destroyEntity(this->map);
}

void scene::MapSelectionScene::update(scene::ScenesManager& scenesManager, float /*dt*/)
{
    if (IsKeyPressed(KEY_ENTER)) {
        audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/Select.mp3", ASSETS_PATH));
        std::string path = fmt::format("{}/", MAPS_PATH);
        path.append(this->paths[this->focus]);
        path.append(".json");
        if (this->type == 0) {
            scenesManager.setScene<scene::PlayerSelectionScene, true>(this->coordinator, path);
        } else if (this->type == 1) {
            scenesManager.setScene<scene::MultiPlayerSelectionScene, true>(this->coordinator, path);
        }
    } else if (IsKeyPressed(KEY_LEFT)) {
        audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/MenuMove.mp3", ASSETS_PATH));
        if (this->focus < 1) {
            this->focus = paths.size() - 1;
        } else {
            this->focus--;
        }
        coordinator.getComponent<ecs::component::RenderableText2d>(this->current).text = paths[this->focus];
    } else if (IsKeyPressed(KEY_RIGHT)) {
        audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/MenuMove.mp3", ASSETS_PATH));
        if (this->focus >= paths.size() - 1) {
            this->focus = 0;
        } else {
            this->focus++;
        }
        coordinator.getComponent<ecs::component::RenderableText2d>(this->current).text = paths[this->focus];
    }
}

utils::Vector scene::MapSelectionScene::getCameraPosition() const noexcept
{
    return utils::Vector{-20, 83, 0};
}

utils::Vector scene::MapSelectionScene::getCameraLooking() const noexcept
{
    return utils::Vector{200, 83, 1};
}
