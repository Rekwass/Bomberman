/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Image2dRenderSystem
*/

#include "ECS/Systems/Image2dRenderSystem.hpp"

#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/RenderableImage2d.hpp"

void ecs::system::Image2dRenderSystem::update(ecs::Coordinator& coordinator) const
{
    for (const auto& entity : this->entities) {
        auto& attributes = coordinator.getComponent<ecs::component::Attributes>(entity);
        auto& image = coordinator.getComponent<ecs::component::RenderableImage2d>(entity);
        const Texture2D& t = image.getTexture();

        DrawTextureEx(t, {attributes.position.x, attributes.position.y}, attributes.rotationAngle, attributes.scale, WHITE);
    }
}
