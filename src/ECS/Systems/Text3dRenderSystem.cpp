/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Text3dRenderSystem
*/

#include "ECS/Systems/Text3dRenderSystem.hpp"

#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/RenderableText3d.hpp"
#include "raylib.h"

void DrawText3D(Font font, const char* text, utils::Vector position, float fontSize, float fontSpacing, float lineSpacing, bool backface, Color tint);

void ecs::system::Text3dRenderSystem::update(ecs::Coordinator& coordinator) const
{
    for (const auto& entity : this->entities) {
        auto& text = coordinator.getComponent<ecs::component::RenderableText3d>(entity);

        text.draw();
    }
}
