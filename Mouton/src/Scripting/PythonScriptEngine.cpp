#include "PythonScriptEngine.h"

#include "Core/Timestep.h"
#include "PythonBehaviourBinder.h"
#include "PythonCoreAPI.h"
#include "MoutonComponents/SpriteComponent.h"
#include "MoutonComponents/PythonBehaviourComponent.h"
#include "InternalTypesUtilities.h"

#include <pybind11/embed.h>
#include <pybind11/operators.h>

namespace py = pybind11;

PYBIND11_EMBEDDED_MODULE(Mouton, m)
{
    using namespace Mouton;

    py::class_<glm::vec2>(m, "Vector2")
    .def(py::init<float>())
    .def(py::init<float, float>())
    .def("length", &glm::vec2::length)
    .def("ToString", &InternalTypeUtils::ToString<glm::vec2>)
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
    .def("length", &glm::vec3::length)
    .def("ToString", &InternalTypeUtils::ToString<glm::vec3>)
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
    .def("length", &glm::vec3::length)
    .def("ToString", &InternalTypeUtils::ToString<glm::vec4>)
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

    py::class_<SpriteComponent>(m, "SpriteComponent")
    .def(py::init<std::string>())
    .def("ToString", &InternalTypeUtils::ToString<SpriteComponent>)
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
    .def("Move", &OrthographicCameraComponent::Move)
    .def("Translate", &OrthographicCameraComponent::Translate)
    .def("Rotate", &OrthographicCameraComponent::Rotate)
    .def("SetCoords", &OrthographicCameraComponent::SetCoords);

    py::class_<Timestep>(m, "Timestep")
    .def(py::init<float>())
    .def("ToString", &InternalTypeUtils::ToString<Timestep>)
    .def("GetSeconds", &Timestep::GetSeconds)
    .def("GetMilliseconds", &Timestep::GetMilliseconds)
    .def(py::self + float())
    .def(py::self - float())
    .def(py::self * float());

    py::class_<PythonAPI::Core>(m, "Core")
    .def_static("Print", &PythonAPI::Core::Print);
}

namespace Mouton
{

    void PythonScriptEngine::Init()
    {
        static py::scoped_interpreter interpreter{};
    }

    void PythonScriptEngine::Stop()
    {
    }

} // namespace Mouton
