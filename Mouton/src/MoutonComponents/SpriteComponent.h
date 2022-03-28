#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "Core/Utils/SerializationUtils.h"
#include "MoutonPch.h"

#include "Ecs/Components.h"
#include "Renderer/Texture.h"

namespace Mouton {

    struct SpriteComponent : public Component {
        glm::vec4 color { 1.0f, 0.0f, 0.0f, 1.0f };
        glm::vec3 position { 0.0f };
        float rotation = 0.0f;
        glm::vec2 scale { 1.0f };
        bool isTextured = false;
        std::shared_ptr<Texture2D> texture = nullptr;

        SpriteComponent(const std::string& name = "SpriteComponent",
                        Component::ComponentType type
                        = ComponentType::SpriteComponent);
        SpriteComponent(std::shared_ptr<Texture2D>& texture,
                        const std::string& name = "SpriteComponent",
                        Component::ComponentType type
                        = ComponentType::SpriteComponent);

        template<typename Writer>
        void Serialize(Writer& writer)
        {
            writer.String("Color");
            writer.StartArray();
            writer.Double(static_cast<double>(color.r));
            writer.Double(static_cast<double>(color.g));
            writer.Double(static_cast<double>(color.b));
            writer.Double(static_cast<double>(color.a));
            writer.EndArray();

            writer.String("Position");
            writer.StartArray();
            writer.Double(static_cast<double>(position.x));
            writer.Double(static_cast<double>(position.y));
            writer.Double(static_cast<double>(position.z));
            writer.EndArray();

            writer.String("Scale");
            writer.StartArray();
            writer.Double(static_cast<double>(scale.x));
            writer.Double(static_cast<double>(scale.y));
            writer.EndArray();

            writer.String("Rotation");
            writer.Double(static_cast<double>(rotation));

            writer.String("IsTextured");
            writer.Bool(isTextured);

            writer.String("Texture");
            if (isTextured)
                writer.String(texture->GetFilename().c_str());
            else
                writer.Null();
        }

        template<typename Value>
        static SpriteComponent* LoadJson(const Value& value)
        {
            auto color
                = Utils::SerializationUtils::Vec4FromJson(value["Color"]);
            auto position
                = Utils::SerializationUtils::Vec3FromJson(value["Position"]);
            auto scale
                = Utils::SerializationUtils::Vec2FromJson(value["Scale"]);
            float rotation = static_cast<float>(value["Rotation"].GetDouble());

            SpriteComponent* comp
                = new SpriteComponent(value["Name"].GetString());
            comp->color = color;
            comp->position = position;
            comp->scale = scale;
            comp->rotation = rotation;
            comp->isTextured = value["IsTextured"].GetBool();

            if (comp->isTextured)
                comp->texture
                    = Texture2D::CreateTexture(value["Texture"].GetString());

            return comp;
        }
    };

} // namespace Mouton

#endif