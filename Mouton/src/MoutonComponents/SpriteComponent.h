#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "MoutonPch.h"

#include "Ecs/Components.h"
#include "Renderer/Texture.h"

namespace Mouton
{

    struct SpriteComponent : public Component {
        glm::vec4 color{1.0f, 0.0f, 0.0f, 1.0f};
        glm::vec3 position{0.0f};
        float rotation = 0.0f;
        glm::vec2 scale{1.0f};
        bool isTextured = false;
        std::shared_ptr<Texture2D> texture = nullptr;


        SpriteComponent(const std::string& name = "SpriteComponent",
            Component::ComponentType type = ComponentType::SpriteComponent);
        SpriteComponent(std::shared_ptr<Texture2D>& texture,
            const std::string& name = "SpriteComponent",
            Component::ComponentType type = ComponentType::SpriteComponent);
    };

} // namespace Mouton


#endif