#include "PythonScriptEngine.h"

#include "Core/Timestep.h"
#include "PythonBehaviourBinder.h"
#include "PythonCoreAPI.h"
#include "MoutonComponents/SpriteComponent.h"
#include "MoutonComponents/PythonBehaviourComponent.h"
#include "InternalTypesUtilities.h"
#include "PythonInternalTypesMathUtils.h"

#include <pybind11/embed.h>
#include <pybind11/operators.h>

namespace py = pybind11;

PYBIND11_EMBEDDED_MODULE(Mouton, m)
{
    using namespace Mouton;

    py::class_<glm::vec2>(m, "Vector2")
    .def(py::init<float>())
    .def(py::init<float, float>())
    .def("ToString", &InternalTypeUtils::ToString<glm::vec2>)
    .def("__str__", &InternalTypeUtils::ToString<glm::vec2>)
    .def("__getitem__", [](const glm::vec2& vec, int32_t key) { return vec[key]; })
    .def("__setitem__", [](glm::vec2& vec, int32_t key, float value) { vec[key] = value; })
    .def(py::self * py::self)
    .def(py::self *= py::self)
    .def(py::self + py::self)
    .def(py::self += py::self)
    .def(py::self + float())
    .def(py::self += float())
    .def(py::self * float())
    .def(py::self *= float())
    .def_readwrite("x", &glm::vec2::x)
    .def_readwrite("y", &glm::vec2::y);

    py::class_<glm::vec3>(m, "Vector3")
    .def(py::init<float>())
    .def(py::init<float, float, float>())
    .def("__getitem__", [](const glm::vec3& vec, int32_t key) { return vec[key]; })
    .def("__setitem__", [](glm::vec3& vec, int32_t key, float value) { vec[key] = value; })
    .def("ToString", &InternalTypeUtils::ToString<glm::vec3>)
    .def("__str__", &InternalTypeUtils::ToString<glm::vec3>)
    .def(py::self * py::self)
    .def(py::self *= py::self)
    .def(py::self + py::self)
    .def(py::self += py::self)
    .def(py::self + float())
    .def(py::self += float())
    .def(py::self * float())
    .def(py::self *= float())
    .def_readwrite("x", &glm::vec3::x)
    .def_readwrite("y", &glm::vec3::y)
    .def_readwrite("z", &glm::vec3::z)
    .def_readwrite("r", &glm::vec3::r)
    .def_readwrite("g", &glm::vec3::g)
    .def_readwrite("b", &glm::vec3::b);

    py::class_<glm::vec4>(m, "Vector4")
    .def(py::init<float>())
    .def(py::init<float, float, float, float>())
    .def("__getitem__", [](const glm::vec4& vec, int32_t key) { return vec[key]; })
    .def("__setitem__", [](glm::vec4& vec, int32_t key, float value) { vec[key] = value; })
    .def("ToString", &InternalTypeUtils::ToString<glm::vec4>)
    .def("__str__", &InternalTypeUtils::ToString<glm::vec4>)
    .def(py::self * py::self)
    .def(py::self *= py::self)
    .def(py::self + py::self)
    .def(py::self += py::self)
    .def(py::self + float())
    .def(py::self += float())
    .def(py::self * float())
    .def(py::self *= float())
    .def_readwrite("x", &glm::vec4::x)
    .def_readwrite("y", &glm::vec4::y)
    .def_readwrite("z", &glm::vec4::z)
    .def_readwrite("w", &glm::vec4::w)
    .def_readwrite("r", &glm::vec4::r)
    .def_readwrite("g", &glm::vec4::g)
    .def_readwrite("b", &glm::vec4::b)
    .def_readwrite("a", &glm::vec4::a);

    py::class_<glm::mat2>(m, "Matrix2")
    .def(py::init<float>())
    .def("ToString", &InternalTypeUtils::ToString<glm::mat2>)
    .def("__getitem__", &InternalTypeUtils::GetMatrixIndex<glm::mat2, glm::vec2>)
    .def("__getitem__", &InternalTypeUtils::GetMatrix2DIndex<glm::mat2>)
    .def("__setitem__", &InternalTypeUtils::AssignMatrixIndex<glm::mat2, glm::vec2>)
    .def("__setitem__", &InternalTypeUtils::AssignMatrixIndex<glm::mat2, float>)
    .def("toString", &InternalTypeUtils::ToMatString<2, 2, float>)
    .def("__str__", &InternalTypeUtils::ToMatString<2, 2, float>)
    .def(py::self * py::self)
    .def(py::self *= py::self)
    .def(py::self + py::self)
    .def(py::self += py::self)
    .def(py::self + float())
    .def(py::self += float())
    .def(py::self * float())
    .def(py::self *= float());

    py::class_<glm::mat3>(m, "Matrix3")
    .def(py::init<float>())
    .def("ToString", &InternalTypeUtils::ToString<glm::mat3>)
    .def("__getitem__", &InternalTypeUtils::GetMatrixIndex<glm::mat3, glm::vec3>)
    .def("__getitem__", &InternalTypeUtils::GetMatrix2DIndex<glm::mat3>)
    .def("__setitem__", &InternalTypeUtils::AssignMatrixIndex<glm::mat3, glm::vec3>)
    .def("__setitem__", &InternalTypeUtils::AssignMatrixIndex<glm::mat3, float>)
    .def("toString", &InternalTypeUtils::ToMatString<3, 3, float>)
    .def("__str__", &InternalTypeUtils::ToMatString<3, 3, float>)
    .def(py::self * py::self)
    .def(py::self *= py::self)
    .def(py::self + py::self)
    .def(py::self += py::self)
    .def(py::self + float())
    .def(py::self += float())
    .def(py::self * float())
    .def(py::self *= float());

    py::class_<glm::mat4>(m, "Matrix4")
    .def(py::init<float>())
    .def("ToString", &InternalTypeUtils::ToString<glm::mat4>)
    .def("__getitem__", &InternalTypeUtils::GetMatrixIndex<glm::mat4, glm::vec4>)
    .def("__getitem__", &InternalTypeUtils::GetMatrix2DIndex<glm::mat4>)
    .def("__setitem__", &InternalTypeUtils::AssignMatrixIndex<glm::mat4, glm::vec4>)
    .def("__setitem__", &InternalTypeUtils::AssignMatrixIndex<glm::mat4, float>)
    .def("toString", &InternalTypeUtils::ToMatString<4, 4, float>)
    .def("__str__", &InternalTypeUtils::ToMatString<4, 4, float>)
    .def(py::self * py::self)
    .def(py::self *= py::self)
    .def(py::self + py::self)
    .def(py::self += py::self)
    .def(py::self + float())
    .def(py::self += float())
    .def(py::self * float())
    .def(py::self *= float());

    py::class_<SpriteComponent>(m, "SpriteComponent")
    .def(py::init<std::string>())
    .def("ToString", &InternalTypeUtils::ToString<SpriteComponent>)
    .def("__str__", &InternalTypeUtils::ToString<SpriteComponent>)
    .def_readwrite("color", &SpriteComponent::color)
    .def_readwrite("position", &SpriteComponent::position)
    .def_readwrite("rotation", &SpriteComponent::rotation)
    .def_readwrite("scale", &SpriteComponent::scale)
    .def_readwrite("isTextured", &SpriteComponent::isTextured);

    // This object is not supposed to be used in the python side
    // it's to make the Python interpreter happy while instancing
    // a class derived from OrthographicCameraComponent
    py::class_<OrthographicCameraController>(m, "OrthographicCameraController");

    py::class_<OrthographicCameraComponent>(m, "OrthographicCameraComponent")
    .def(py::init<const std::string&, OrthographicCameraController*>())
    .def("ToString", &InternalTypeUtils::ToString<OrthographicCameraComponent>)
    .def("__str__", &InternalTypeUtils::ToString<OrthographicCameraComponent>)
    .def("Move", &OrthographicCameraComponent::Move)
    .def("Translate", &OrthographicCameraComponent::Translate)
    .def("Rotate", &OrthographicCameraComponent::Rotate)
    .def("SetCoords", &OrthographicCameraComponent::SetCoords);

    py::class_<Timestep>(m, "Timestep")
    .def(py::init<float>())
    .def("ToString", &InternalTypeUtils::ToString<Timestep>)
    .def("__str__", &InternalTypeUtils::ToString<Timestep>)
    .def("GetSeconds", &Timestep::GetSeconds)
    .def("GetMilliseconds", &Timestep::GetMilliseconds)
    .def(py::self + float())
    .def(py::self - float())
    .def(py::self * float());

    py::class_<PythonAPI::Core>(m, "Core")
    .def_static("Print", &PythonAPI::Core::Print);

    py::class_<PythonInternalMath>(m, "Math")
    .def("Cross", [](const glm::vec3& x, const glm::vec3& y) {
        return glm::cross(x ,y);
    })
    .def("Normalize", [](const glm::vec2& x) { return glm::normalize(x); })
    .def("Normalize", [](const glm::vec3& x) { return glm::normalize(x); })
    .def("Normalize", [](const glm::vec4& x) { return glm::normalize(x); });
}

namespace Mouton
{

    void PythonScriptEngine::Init()
    {
        static py::scoped_interpreter interpreter{};
    }

    void PythonScriptEngine::Restart()
    {
    }

    void PythonScriptEngine::Stop()
    {
        // if(interpreter)
        //     delete interpreter;
    }



} // namespace Mouton
