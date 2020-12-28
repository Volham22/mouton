#ifndef SERIALIZATION_UTILS_H
#define SERIALIZATION_UTILS_H

#include "MoutonPch.h"

namespace Mouton::Utils
{

    class SerializationUtils
    {
    public:
        template<typename Values>
        static glm::vec2 Vec2FromJson(const Values& values)
        {
            glm::vec2 v{0.0f};

            for(auto [it, i] = std::tuple{values.Begin(), 0};
                (it != values.End()) && (i < 2); it++, i++)
            {
                v[i] = (float)it->GetDouble();
            }

            return v;
        }

        template<typename Values>
        static glm::vec3 Vec3FromJson(const Values& values)
        {
            glm::vec3 v{0.0f};

            for(auto [it, i] = std::tuple{values.Begin(), 0};
                (it != values.End()) && (i < 3); it++, i++)
            {
                v[i] = (float)it->GetDouble();
            }

            return v;
        }

        template<typename Values>
        static glm::vec4 Vec4FromJson(const Values& values)
        {
            glm::vec4 v{0.0f};

            for(auto [it, i] = std::tuple{values.Begin(), 0};
                (it != values.End()) && (i < 4); it++, i++)
            {
                v[i] = (float)it->GetDouble();
            }

            return v;
        }

    };

} // namespace Mouton::Utils


#endif