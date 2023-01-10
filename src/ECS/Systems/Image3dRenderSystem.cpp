/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Image3dRenderSystem
*/

#include "ECS/Systems/Image3dRenderSystem.hpp"

#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/RenderableImage3d.hpp"

void ecs::system::Image3dRenderSystem::update(ecs::Coordinator& coordinator, const Camera3D& camera) const
{
    for (const auto& entity : this->entities) {
        auto& attributes = coordinator.getComponent<ecs::component::Attributes>(entity);
        auto& image = coordinator.getComponent<ecs::component::RenderableImage3d>(entity);
        const Texture2D& t = image.getTexture();

        DrawBillboard(camera, t, attributes.position, attributes.scale, WHITE);
    }
}
