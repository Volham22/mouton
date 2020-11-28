#include "SceneExplorer.h"

#include "imgui.h"
#include "Ecs/Entity.h"

#include "EditorPropertiesPanels.h"
#include "Scripting/ScriptSkeletonFactory.h"

#include <sstream>

using namespace Mouton;

static bool AddPythonBehaviourComponent(Scene& scene, const std::string& name,
    const std::array<char, 255>& moduleName, Component* boundComponent, PythonBehaviourType type);

static void ShowPythonBehaviourCreation(Scene& scene, std::array<char, 255>& moduleName,
    int& selectedBehaviourType, Component*& boundComponent);

static std::string CreateComponentComboList(Scene& scene);
static std::string GetElementSequenceName(const std::string& sequence, int n);

SceneExplorer::SceneExplorer()
    : m_ComponentShown(nullptr), m_CustomCamera(nullptr)
{
    EditorPropertiesPanels::Init();
}

void SceneExplorer::InitProperties()
{
    EditorPropertiesPanels::LoadProjectTextures();
}

void SceneExplorer::ShowSceneExplorer(Scene &scene)
{
    ImGui::Begin("Scene explorer");

    if (ImGui::CollapsingHeader("Scene Entities"))
    {
        const auto &entities = scene.GetEntities();

        for (Entity *ent : entities)
        {
            ShowEntity(ent, scene);
            ImGui::Separator();
        }

        ShowCreateComponent(scene);
        ShowCreateEntity(scene);
    }

    ImGui::End();

    // Show Component Properties panel if any is selected
    if (m_ComponentShown)
    {
        ImGui::Begin("Component Properties");
        ShowProperties();
        ImGui::End();
    }
}

void SceneExplorer::SetUserCamera(std::shared_ptr<OrthographicCameraController>& camera)
{
    m_CustomCamera = camera->GetCameraInstance();
}

void SceneExplorer::SetDefaultCamera()
{
    m_CustomCamera = nullptr;
}

Component* SceneExplorer::CreateComponentFromType(Scene& scene, Component::ComponentType type, const std::string &name) const
{
    switch (type)
    {
    case Component::ComponentType::SpriteComponent:
        return new SpriteComponent(name);

    case Component::ComponentType::OrthographicCamera:
        return new OrthographicCameraComponent(name,
            std::make_shared<Mouton::OrthographicCameraController>(
                std::make_shared<Mouton::OrthographicCamera>(0.0f, 100.0f, 0.0f, 100.0f)));
        break;

    default:
        return nullptr;
    }
}

void SceneExplorer::ShowProperties()
{
    using Type = Component::ComponentType;
    using namespace Mouton;

    switch (m_ComponentShown->GetComponentType())
    {
    case Type::SpriteComponent:
        EditorPropertiesPanels::ShowSpriteComponentPanel(static_cast<SpriteComponent*>(m_ComponentShown));
        break;

    case Type::PythonBehaviourComponent:
        EditorPropertiesPanels::ShowPythonBehaviourComponentPanel(static_cast<PythonBehaviourComponent<PythonBinder>*>(m_ComponentShown));
        break;

    case Type::OrthographicCamera:
        EditorPropertiesPanels::ShowOrthographicCameraComponent(static_cast<OrthographicCameraComponent*>(m_ComponentShown), this);
        break;

    default:
        MTN_WARN("Unknown Component Properties to show !");
    }
}

void SceneExplorer::ShowEntity(Mouton::Entity *entity, Mouton::Scene &scene)
{
    if (ImGui::TreeNode(entity->GetName().c_str()))
    {
        const auto &entityComponents = scene.GetEntityComponent(entity->GetName());

        for (Component *comp : entityComponents)
            ShowComponent(entity, comp, scene);

        if (ImGui::Button("Add Component"))
            ImGui::OpenPopup("components_add");

        if (ImGui::BeginPopup("components_add"))
        {
            ImGui::Text("Choose a component to add");
            ImGui::Separator();

            const auto &components = scene.GetComponents(Component::ComponentType::Any);
            for (Component *comp : components)
            {
                if (ImGui::Selectable(comp->GetComponentName().c_str()))
                    scene.AddComponentToEntity(entity->GetName().c_str(), comp->GetComponentType(), comp->GetComponentName().c_str());
            }

            ImGui::EndPopup();
        }

        ImGui::SameLine();
        if (ImGui::Button("Remove entity"))
            ImGui::OpenPopup("Do you really want to do it ?");

        if (ImGui::BeginPopup("Do you really want to do it ?"))
        {
            ImGui::TextColored({1.0f, 0.0f, 0.0f, 1.0f}, "You're about to remove an entity do you really want to do it ?");
            ImGui::Separator();

            if (ImGui::Button("Yes"))
                scene.RemoveEntity(entity->GetName());

            ImGui::SameLine();

            if (ImGui::Button("No keep my entity !"))
                ImGui::CloseCurrentPopup();

            ImGui::EndPopup();
        }

        ImGui::TreePop();
    }
}

void SceneExplorer::ShowComponent(Mouton::Entity *entity, Mouton::Component *comp, Mouton::Scene &scene)
{
    if (ImGui::TreeNode(comp->GetComponentName().c_str()))
    {
        if (ImGui::Button("Remove", {150, 20}))
        {
            scene.RemoveComponentToEntity(entity->GetName().c_str(),
                                          comp->GetComponentType(),
                                          comp->GetComponentName());
        }

        if (ImGui::Button("Show properties", {150, 20}))
            m_ComponentShown = comp;

        ImGui::TreePop();
    }
}

void SceneExplorer::ShowCreateComponent(Mouton::Scene &scene) const
{
    if (ImGui::Button("Create a new Component ..."))
        ImGui::OpenPopup("Create component");

    if (ImGui::BeginPopupModal("Create component", nullptr, ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoMove))
    {
        ImGui::Text("Create a new Component");

        static char nameBuffer[200] = "";
        static int item = 1;

        // Python Behaviour creation
        static int selectedPythonBehaviourType = 0;
        static std::array<char, 255> pythonModuleName;
        static Component* boundComponent = nullptr;


        // The item value must match with the Mouton::Component::ComponentType enum
        ImGui::Combo("Select Component Type", &item,
                "SpriteComponent\0Behaviour Component\0Python Behaviour Component\0Orthographic Camera Component\0\0", 5);

        ImGui::InputTextWithHint("Component Name", "type a name", nameBuffer, IM_ARRAYSIZE(nameBuffer));
        ImGui::Separator();

        auto toComponentType = [](auto x) {
            return (Component::ComponentType)(x + 1);
        };

        auto toBehaviourType = [](auto x) {
            return (PythonBehaviourType)(x + 1);
        };

        if(toComponentType(item) == Component::ComponentType::PythonBehaviourComponent)
            ShowPythonBehaviourCreation(scene, pythonModuleName, selectedPythonBehaviourType, boundComponent);

        if (ImGui::Button("Add"))
        {
            // if (std::strlen(nameBuffer) > 0 && scene.AddComponent(toComponentType(item),
            //                                         CreateComponentFromType(scene, toComponentType(item), std::string(nameBuffer))))
            //     ImGui::CloseCurrentPopup();
            // else
            //     ImGui::OpenPopup("Incorrect Name !");

            switch(toComponentType(item))
            {
            case Component::ComponentType::SpriteComponent:
                if(!scene.AddComponent(toComponentType(item),
                                                    CreateComponentFromType(scene, toComponentType(item), std::string(nameBuffer))))
                    ImGui::OpenPopup("Incorrect Name !");
                else
                    ImGui::CloseCurrentPopup();
                break;

            case Component::ComponentType::OrthographicCamera:
                if(!scene.AddComponent(toComponentType(item),
                                                    CreateComponentFromType(scene, toComponentType(item), std::string(nameBuffer))))
                    ImGui::OpenPopup("Incorrect Name !");
                else
                    ImGui::CloseCurrentPopup();
                break;

            case Component::ComponentType::PythonBehaviourComponent:
                if(!AddPythonBehaviourComponent(scene, std::string(nameBuffer), pythonModuleName, boundComponent, toBehaviourType(selectedPythonBehaviourType)))
                    ImGui::OpenPopup("Incorrect Name !");
                else
                    ImGui::CloseCurrentPopup();
                break;

            default:
                MTN_ERROR("Unknow component to create !");
                ImGui::CloseCurrentPopup();
            }
        }

        if (ImGui::BeginPopupModal("Incorrect Name !"))
        {
            ImGui::Text("Component name not valid or already used !");
            ImGui::Separator();

            if (ImGui::Button("Close."))
                ImGui::CloseCurrentPopup();

            ImGui::EndPopup();
        }

        ImGui::SameLine();

        if (ImGui::Button("Cancel."))
            ImGui::CloseCurrentPopup();

        ImGui::EndPopup();
    }
}

void SceneExplorer::ShowCreateEntity(Mouton::Scene& scene) const
{
    ImGui::SameLine();
    if (ImGui::Button("Add new Entity"))
        ImGui::OpenPopup("Add Entity");

    if (ImGui::BeginPopupModal("Add Entity"))
    {
        ImGui::Text("Add a new entity");
        static char entityNameBuffer[200] = "";

        ImGui::InputTextWithHint("Entity name", "enter new entity name ...", entityNameBuffer, IM_ARRAYSIZE(entityNameBuffer));

        ImGui::Separator();
        if (ImGui::Button("Add Entity"))
        {
            if (strlen(entityNameBuffer) > 0 && strlen(entityNameBuffer) < 200 &&
                scene.AddEntity(new Entity(std::string(entityNameBuffer))))
                ImGui::CloseCurrentPopup();
            else
                ImGui::OpenPopup("Incorrect Entity name !");
        }

        ImGui::SameLine();
        if(ImGui::Button("Cancel."))
            ImGui::CloseCurrentPopup();

        if (ImGui::BeginPopupModal("Incorrect Entity name !"))
        {
            ImGui::Text("Entity name not valid or already used !");
            ImGui::Separator();

            if (ImGui::Button("Close"))
                ImGui::CloseCurrentPopup();

            ImGui::EndPopup();
        }

        ImGui::EndPopup();
    }
}

SceneExplorer::~SceneExplorer()
{
    EditorPropertiesPanels::Stop();
}

// TODO: Handle different component type properly, for now it's only SpriteBehaviour
bool AddPythonBehaviourComponent(Scene& scene, const std::string& name,
    const std::array<char, 255>& moduleName, Component* boundComponent, PythonBehaviourType type)
{
    ScriptSkeletonFactory::CreateSpriteComponentSkeleton(std::string(moduleName.data()));
    PythonBehaviourComponent<PythonBinder>* comp = nullptr;

    switch(type)
    {
    case PythonBehaviourType::SpriteBehaviour:
    {
        auto spriteComp = new PythonBehaviourComponent<SpriteComponentScriptable>(name, moduleName.data(), static_cast<SpriteComponent*>(boundComponent));
        return scene.AddComponent(Component::ComponentType::PythonBehaviourComponent, spriteComp);
    }

    case PythonBehaviourType::OrthographicCameraBehaviour:
    {
        auto orthoComp = new PythonBehaviourComponent<OrthographicCameraComponentScriptable>(name, moduleName.data(), static_cast<OrthographicCameraComponent*>(boundComponent));
        return scene.AddComponent(Component::ComponentType::PythonBehaviourComponent, orthoComp);
    }

    default:
        return false;
    }
}

void ShowPythonBehaviourCreation(Scene& scene, std::array<char, 255>& moduleName, int& selectedBehaviourType, Component*& boundComponent)
{
    static int selectedScriptableComponent = 0;
    std::string componentComboSequence = CreateComponentComboList(scene);

    auto onTypeCallback = [](ImGuiInputTextCallbackData* event) -> int {
        if(!strstr(event->Buf, ".py"))
            ImGui::TextColored({ 1.0f, 0.0f, 0.0f, 1.0f }, "Please do not put .py in module name !");

        return 0;
    };

    ImGui::InputTextWithHint("Python Module name", "type Python module name", moduleName.data(), moduleName.size(), 0, onTypeCallback);

    ImGui::Combo("Python behaviour type", &selectedBehaviourType, "SpriteBehaviour\0Orthographic Camera Behaviour\0");

    ImGui::Combo("Choosed scriptable components", &selectedScriptableComponent, componentComboSequence.c_str());

    boundComponent = scene.GetComponentByName(GetElementSequenceName(componentComboSequence, selectedScriptableComponent));

    ImGui::Separator();
}

std::string CreateComponentComboList(Scene& scene)
{
    std::stringstream ss;

    scene.ForEachComponents(Component::ComponentType::Any, [&ss](Component& comp) {
        if(comp.IsScriptable())
            ss << comp.GetComponentName() << '\0';
    });

    ss << '\0';

    return ss.str();
}

std::string GetElementSequenceName(const std::string& sequence, int n)
{
    uint32_t index = 0;
    for(uint32_t zerosSeen = 0; (index < sequence.size()) && ((int)zerosSeen < n); index++)
    {
        if(sequence[index] == '\0')
            zerosSeen++;
    }

    uint32_t seqSize = 0;
    while(((index + seqSize) < sequence.size()) && (sequence[index + seqSize] != '\0'))
        seqSize++;

    return sequence.substr(index, index + seqSize);
}
