/*
** EPITECH PROJECT, 2022
** Indie Studio
** File description:
** Main Menu
*/

#include "Scenes/EndScene.hpp"

#include "AudioPlayer.hpp"
#include "FilePaths.hpp"
#include "Game/PlayersManager.hpp"
#include "Scenes/MainMenuScene.hpp"

#include <optional>

// NOLINTNEXTLINE
scene::EndScene::EndScene(game::Room& room, ecs::Coordinator& coordinator, std::vector<std::unique_ptr<game::APlayer>> players) :
    coordinator(coordinator), title(this->coordinator.createEntity()), text(this->coordinator.createEntity()), menu(this->coordinator.createEntity()), credits(this->coordinator.createEntity()), theme(this->coordinator.createEntity()), players(std::move(players))
{
    room.stopMusic();

    coordinator.setComponent(this->title, ecs::component::Attributes{.position = {760, 0, 0}});
    coordinator.setComponent(this->title, ecs::component::RenderableImage2d(fmt::format("{}Textures/End/Result.png", ASSETS_PATH)));

    float buf = 0;
    std::optional<std::reference_wrapper<game::APlayer>> winPlayer = std::nullopt;
    for (auto& player : this->players) {
        player->setPosition({44 + buf, 28, -50});
        player->setRotation(90);
        player->playCelebration();
        buf += 4;
        if (player->isAlive()) {
            winPlayer.emplace(*player);
        }
    }

    if (winPlayer.has_value()) {
        coordinator.setComponent(this->text, ecs::component::RenderableText2d{.text = "Music by Bensound.com", .fontSize = 20});
        std::string res = "Player ";
        res.append(std::to_string(winPlayer.value().get().getId()));
        if (winPlayer.value().get().getType() == game::PlayerType::AI) {
            res.append(" (AI)");
        }
        res.append(" won!");

        coordinator.setComponent(this->text, ecs::component::Attributes{.position = {550, 250, 0}});
        coordinator.setComponent(this->text, ecs::component::RenderableText2d{.text = res, .fontSize = 90});
    } else {
        coordinator.setComponent(this->text, ecs::component::Attributes{.position = {850, 250, 0}});
        coordinator.setComponent(this->text, ecs::component::RenderableText2d{.text = "Draw!", .fontSize = 90});
    }

    coordinator.setComponent(this->menu, ecs::component::Attributes{.position = {780, 800, 0}});
    coordinator.setComponent(this->menu, ecs::component::RenderableImage2d(fmt::format("{}Textures/End/Menu.png", ASSETS_PATH)));

    coordinator.setComponent(this->credits, ecs::component::Attributes{.position = {850, 1050, 0}});
    coordinator.setComponent(this->credits, ecs::component::RenderableText2d{.text = "Music by Bensound.com", .fontSize = 20});

    coordinator.setComponent(this->theme, ecs::component::MusicObject(fmt::format("{}audio/Musics/End.mp3", ASSETS_PATH)));
    this->coordinator.getComponent<ecs::component::MusicObject>(this->theme).play();

    audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/Applause.mp3", ASSETS_PATH));
}

scene::EndScene::~EndScene() noexcept
{
    coordinator.destroyEntity(this->title);
    coordinator.destroyEntity(this->text);
    coordinator.destroyEntity(this->menu);
    coordinator.destroyEntity(this->credits);
    coordinator.destroyEntity(this->theme);
}

void scene::EndScene::update(scene::ScenesManager& scenesManager, float /*dt*/)
{
    if (IsKeyPressed(KEY_ENTER)) {
        this->coordinator.getComponent<ecs::component::MusicObject>(this->theme).pause();
        audio::AudioPlayer::playSound(fmt::format("{}audio/Sounds/Select.mp3", ASSETS_PATH));
        scenesManager.setScene<scene::MainMenuScene, true>(this->coordinator);
    }
}

utils::Vector scene::EndScene::getCameraPosition() const noexcept
{
    return utils::Vector{50, 30, -30};
}

utils::Vector scene::EndScene::getCameraLooking() const noexcept
{
    return utils::Vector{51, 29, -100};
}
