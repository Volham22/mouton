#ifndef INTERNAL_TYPES_UTILITIES_H
#define INTERNAL_TYPES_UTILITIES_H

#include "MoutonPch.h"

#include <type_traits>
#include <typeinfo>
#include <sstream>

#include <pybind11/embed.h>

namespace Mouton
{

    namespace py = pybind11;
    class InternalTypeUtils
    {
    public:
        template<typename T, typename... Args>
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

        template<int32_t T, int32_t U, typename V>
        static std::string ToMatString(const glm::mat<T, U, V>& m)
        {
            static_assert(std::is_arithmetic_v<V>, "Matrix type must be arithmetic !");

            std::stringstream ss;

            ss << "Matrix of " << T << " x " << U << '\n';
            for(int32_t i = 0; i < T; i++)
            {
                for(int32_t j = 0; j < U; j++)
                    ss << m[i][j] << ' ';

                ss << '\n';
            }

            return ss.str();
        }

        template<typename T, typename U>
        static void AssignMatrixIndex(T& matrix, const py::tuple& args, const U& value)
        {
            if(args.size() > 2)
                throw std::out_of_range("Incorrect number of arguments passed to __setitem__");

            if constexpr(std::is_arithmetic_v<U>)
            {
                int32_t row = py::cast<float>(args[0]);
                int32_t column = py::cast<float>(args[1]);

                matrix[row][column] = value;
            }
            else
            {
                int32_t index = py::cast<int32_t>(args[0]);
                matrix[index] = value;
            }
        }

        template<typename T>
        static float GetMatrix2DIndex(const T& matrix, const py::tuple& args)
        {
            if(args.size() > 2)
                throw std::out_of_range("Incorrect number of arguments passed to __setitem__");

            int32_t row = py::cast<int32_t>(args[0]);
            int32_t column = py::cast<int32_t>(args[1]);

            return matrix[row][column];
        }

        template<typename T, typename Return>
        static Return GetMatrixIndex(const T& matrix, int32_t key)
        {
            return matrix[key];
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