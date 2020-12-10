#ifndef INTERNAL_TYPES_UTILITIES_H
#define INTERNAL_TYPES_UTILITIES_H

#include "MoutonPch.h"

#include <type_traits>
#include <typeinfo>
#include <sstream>

namespace Mouton
{

    class InternalTypeUtils
    {
    public:
        template<typename T>
        static std::string ToString(const T& obj)
        {
            if constexpr(std::is_arithmetic_v<T>)
            {
                std::stringstream ss;
                ss << obj;
                return ss.str();
            }

            return typeid(obj).name();
        }
    };

    template<>
    std::string InternalTypeUtils::ToString<glm::vec2>(const glm::vec2& vector)
    {
        std::stringstream ss;

        ss << "<Vector2 " << "(x|r): " << vector.x;
        ss << " (y|g): " << vector.y;
        ss << '>';

        return ss.str();
    }

    template<>
    std::string InternalTypeUtils::ToString<glm::vec3>(const glm::vec3& vector)
    {
        std::stringstream ss;

        ss << "<Vector3 " << "(x|r): " << vector.x;
        ss << " (y|g): " << vector.y;
        ss << " (z|b) " << vector.z;
        ss << '>';

        return ss.str();
    }

    template<>
    std::string InternalTypeUtils::ToString<glm::vec4>(const glm::vec4& vector)
    {
        std::stringstream ss;

        ss << "<Vector4 " << "(x|r): " << vector.x;
        ss << " (y|g): " << vector.y;
        ss << " (z|b) " << vector.z;
        ss << " (w|a) " << vector.w;
        ss << '>';

        return ss.str();
    }

} // namespace Mouton


#endif