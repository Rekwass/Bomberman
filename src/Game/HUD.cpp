/*
** EPITECH PROJECT, 2022
** src
** File description:
** HUD
*/

#include "Game/HUD.hpp"

#include "FilePaths.hpp"
#include "Game/PlayersManager.hpp"

#include <string>

game::HUD::HUD(ecs::Coordinator& coordinator) :
    coordinator(coordinator), p1Name(coordinator.createEntity()), p1LifeIcon(coordinator.createEntity()), p1LifeNb(coordinator.createEntity()), p1BombIcon(coordinator.createEntity()), p1BombNb(coordinator.createEntity()), p2Name(coordinator.createEntity()), p2LifeIcon(coordinator.createEntity()), p2LifeNb(coordinator.createEntity()), p2BombIcon(coordinator.createEntity()), p2BombNb(coordinator.createEntity()), p3Name(coordinator.createEntity()), p3LifeIcon(coordinator.createEntity()), p3LifeNb(coordinator.createEntity()), p3BombIcon(coordinator.createEntity()), p3BombNb(coordinator.createEntity()), p4Name(coordinator.createEntity()), p4LifeIcon(coordinator.createEntity()), p4LifeNb(coordinator.createEntity()), p4BombIcon(coordinator.createEntity()), p4BombNb(coordinator.createEntity())
{
    // P1
    this->coordinator.setComponent(this->p1Name, ecs::component::Attributes{.position = {40, 50, 0}});
    this->coordinator.setComponent(this->p1Name, ecs::component::RenderableText2d{.text = this->getPlayerLabel(1), .fontSize = 55});
    this->coordinator.setComponent(this->p1LifeIcon, ecs::component::Attributes{.position = {35, 105, 0}});
    this->coordinator.setComponent(this->p1LifeIcon, ecs::component::RenderableImage2d(fmt::format("{}Textures/Game/Heart.png", ASSETS_PATH)));
    this->coordinator.setComponent(this->p1LifeNb, ecs::component::Attributes{.position = {115, 115, 0}});
    this->coordinator.setComponent(this->p1LifeNb, ecs::component::RenderableText2d{.text = "1", .fontSize = 48, .color = RED});
    this->coordinator.setComponent(this->p1BombIcon, ecs::component::Attributes{.position = {40, 170, 0}});
    this->coordinator.setComponent(this->p1BombIcon, ecs::component::RenderableImage2d(fmt::format("{}Textures/Game/Bomb.png", ASSETS_PATH)));
    this->coordinator.setComponent(this->p1BombNb, ecs::component::Attributes{.position = {115, 185, 0}});
    this->coordinator.setComponent(this->p1BombNb, ecs::component::RenderableText2d{.text = "1", .fontSize = 48, .color = BLACK});

    // P2
    this->coordinator.setComponent(this->p2Name, ecs::component::Attributes{.position = {1650, 50, 0}});
    this->coordinator.setComponent(this->p2Name, ecs::component::RenderableText2d{.text = this->getPlayerLabel(2), .fontSize = 55});
    this->coordinator.setComponent(this->p2LifeIcon, ecs::component::Attributes{.position = {1645, 105, 0}});
    this->coordinator.setComponent(this->p2LifeIcon, ecs::component::RenderableImage2d(fmt::format("{}Textures/Game/Heart.png", ASSETS_PATH)));
    this->coordinator.setComponent(this->p2LifeNb, ecs::component::Attributes{.position = {1725, 115, 0}});
    this->coordinator.setComponent(this->p2LifeNb, ecs::component::RenderableText2d{.text = "1", .fontSize = 48, .color = RED});
    this->coordinator.setComponent(this->p2BombIcon, ecs::component::Attributes{.position = {1650, 170, 0}});
    this->coordinator.setComponent(this->p2BombIcon, ecs::component::RenderableImage2d(fmt::format("{}Textures/Game/Bomb.png", ASSETS_PATH)));
    this->coordinator.setComponent(this->p2BombNb, ecs::component::Attributes{.position = {1725, 185, 0}});
    this->coordinator.setComponent(this->p2BombNb, ecs::component::RenderableText2d{.text = "1", .fontSize = 48, .color = BLACK});

    // P3
    this->coordinator.setComponent(this->p3Name, ecs::component::Attributes{.position = {40, 870, 0}});
    this->coordinator.setComponent(this->p3Name, ecs::component::RenderableText2d{.text = this->getPlayerLabel(3), .fontSize = 55});
    this->coordinator.setComponent(this->p3LifeIcon, ecs::component::Attributes{.position = {35, 925, 0}});
    this->coordinator.setComponent(this->p3LifeIcon, ecs::component::RenderableImage2d(fmt::format("{}Textures/Game/Heart.png", ASSETS_PATH)));
    this->coordinator.setComponent(this->p3LifeNb, ecs::component::Attributes{.position = {115, 935, 0}});
    this->coordinator.setComponent(this->p3LifeNb, ecs::component::RenderableText2d{.text = "1", .fontSize = 48, .color = RED});
    this->coordinator.setComponent(this->p3BombIcon, ecs::component::Attributes{.position = {40, 990, 0}});
    this->coordinator.setComponent(this->p3BombIcon, ecs::component::RenderableImage2d(fmt::format("{}Textures/Game/Bomb.png", ASSETS_PATH)));
    this->coordinator.setComponent(this->p3BombNb, ecs::component::Attributes{.position = {115, 1005, 0}});
    this->coordinator.setComponent(this->p3BombNb, ecs::component::RenderableText2d{.text = "1", .fontSize = 48, .color = BLACK});

    // P4
    this->coordinator.setComponent(this->p4Name, ecs::component::Attributes{.position = {1650, 870, 0}});
    this->coordinator.setComponent(this->p4Name, ecs::component::RenderableText2d{.text = this->getPlayerLabel(4), .fontSize = 55});
    this->coordinator.setComponent(this->p4LifeIcon, ecs::component::Attributes{.position = {1645, 925, 0}});
    this->coordinator.setComponent(this->p4LifeIcon, ecs::component::RenderableImage2d(fmt::format("{}Textures/Game/Heart.png", ASSETS_PATH)));
    this->coordinator.setComponent(this->p4LifeNb, ecs::component::Attributes{.position = {1725, 935, 0}});
    this->coordinator.setComponent(this->p4LifeNb, ecs::component::RenderableText2d{.text = "1", .fontSize = 48, .color = RED});
    this->coordinator.setComponent(this->p4BombIcon, ecs::component::Attributes{.position = {1650, 990, 0}});
    this->coordinator.setComponent(this->p4BombIcon, ecs::component::RenderableImage2d(fmt::format("{}Textures/Game/Bomb.png", ASSETS_PATH)));
    this->coordinator.setComponent(this->p4BombNb, ecs::component::Attributes{.position = {1725, 1005, 0}});
    this->coordinator.setComponent(this->p4BombNb, ecs::component::RenderableText2d{.text = "1", .fontSize = 48, .color = BLACK});
}

game::HUD::~HUD() noexcept
{
    this->coordinator.destroyEntity(p1Name);
    this->coordinator.destroyEntity(p1LifeIcon);
    this->coordinator.destroyEntity(p1LifeNb);
    this->coordinator.destroyEntity(p1BombIcon);
    this->coordinator.destroyEntity(p1BombNb);
    this->coordinator.destroyEntity(p2Name);
    this->coordinator.destroyEntity(p2LifeIcon);
    this->coordinator.destroyEntity(p2LifeNb);
    this->coordinator.destroyEntity(p2BombIcon);
    this->coordinator.destroyEntity(p2BombNb);
    this->coordinator.destroyEntity(p3Name);
    this->coordinator.destroyEntity(p3LifeIcon);
    this->coordinator.destroyEntity(p3LifeNb);
    this->coordinator.destroyEntity(p3BombIcon);
    this->coordinator.destroyEntity(p3BombNb);
    this->coordinator.destroyEntity(p4Name);
    this->coordinator.destroyEntity(p4LifeIcon);
    this->coordinator.destroyEntity(p4LifeNb);
    this->coordinator.destroyEntity(p4BombIcon);
    this->coordinator.destroyEntity(p4BombNb);
}

void game::HUD::update(std::array<PlayerStat, 4> stats) noexcept
{
    this->coordinator.getComponent<ecs::component::RenderableText2d>(this->p1LifeNb).text = std::to_string(stats.at(0).lifes);
    this->coordinator.getComponent<ecs::component::RenderableText2d>(this->p1BombNb).text = std::to_string(stats.at(0).bombs);

    this->coordinator.getComponent<ecs::component::RenderableText2d>(this->p2LifeNb).text = std::to_string(stats.at(1).lifes);
    this->coordinator.getComponent<ecs::component::RenderableText2d>(this->p2BombNb).text = std::to_string(stats.at(1).bombs);

    this->coordinator.getComponent<ecs::component::RenderableText2d>(this->p3LifeNb).text = std::to_string(stats.at(2).lifes);
    this->coordinator.getComponent<ecs::component::RenderableText2d>(this->p3BombNb).text = std::to_string(stats.at(2).bombs);

    this->coordinator.getComponent<ecs::component::RenderableText2d>(this->p4LifeNb).text = std::to_string(stats.at(3).lifes);
    this->coordinator.getComponent<ecs::component::RenderableText2d>(this->p4BombNb).text = std::to_string(stats.at(3).bombs);
}

std::string game::HUD::getPlayerLabel(game::PlayerId id) noexcept
{
    switch (game::PlayersManager::getPlayerType(id)) {
    case game::PlayerType::KEYBOARD:
        return fmt::format("Player {}", this->playerCount++ + 1);
    case game::PlayerType::AI:
        return fmt::format("AI {}", this->aiCount++ + 1);
    case game::PlayerType::NETWORK:
        return fmt::format("ONLINE {}", this->onlineCount++ + 1);
    }
}
