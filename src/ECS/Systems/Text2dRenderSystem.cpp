/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Text2dRenderSystem
*/

#include "ECS/Systems/Text2dRenderSystem.hpp"

#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/RenderableText2d.hpp"

void ecs::system::Text2dRenderSystem::update(ecs::Coordinator& coordinator) const
{
    for (const auto& entity : this->entities) {
        auto& attributes = coordinator.getComponent<ecs::component::Attributes>(entity);
        auto& text = coordinator.getComponent<ecs::component::RenderableText2d>(entity);

        DrawText(text.text.c_str(), attributes.position.x, attributes.position.y, text.fontSize, text.color);
    }
}
