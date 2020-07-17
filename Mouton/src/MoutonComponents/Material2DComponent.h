#ifndef MATERIAL2D_COMPONENT_H
#define MATERIAL2D_COMPONENT_H

#include "Ecs/Components.h"
#include "Renderer/Texture.h"

namespace Mouton
{

    struct Material2DComponent : public Component
    {
        Material2DComponent(const std::string& name = "Material2DComponent");

        bool IsTextured = false;
        glm::vec4 Color = { 1.0f, 0.0f, 0.0f, 0.0f };
        std::shared_ptr<Texture2D> MaterialTexture = nullptr;
    };

} // namespace Mouton


#endif
