#include "SpriteComponent.h"

namespace Mouton {

    SpriteComponent::SpriteComponent(const std::string& name,
                                     Component::ComponentType type)
        : Component(type, name, true)
    {}

    SpriteComponent::SpriteComponent(std::shared_ptr<Texture2D>& spriteTexture,
                                     const std::string& name,
                                     Component::ComponentType type)
        : Component(type, name, true), isTextured(true), texture(spriteTexture)
    {}

} // namespace Mouton
