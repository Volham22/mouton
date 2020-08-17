#include "SpriteComponent.h"

namespace Mouton
{

    SpriteComponent::SpriteComponent(const std::string& name, Component::ComponentType type)
        : Component(type, name)
    {
    }

    SpriteComponent::SpriteComponent(std::shared_ptr<Texture2D>& spriteTexture,
        const std::string& name, Component::ComponentType type)
        : Component(type, name), isTextured(true), texture(spriteTexture)
    {
    }

} // namespace Mouton
