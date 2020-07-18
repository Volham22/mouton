#ifndef TRANSFORM_COMPONENTS_H
#define TRANSFORM_COMPONENTS_H

#include "Ecs/Components.h"

namespace Mouton
{

    struct TransformComponent : public Component
    {
        TransformComponent(const std::string& name = "TransformComponent");

        glm::vec3 Transform = { 0.0f, 0.0f, 0.0f };
        glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 Scale = { 0.0f, 0.0f, 0.0f };
    };

} // namespace Mouton


#endif