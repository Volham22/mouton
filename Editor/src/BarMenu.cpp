#include "BarMenu.h"

#include "EditorLayer.h"

#include <imgui.h>
#include <rapidjson/prettywriter.h>

#include <cstdio>
#include <fstream>
#include <sstream>


// Show a file dialog to save the serialized scene
static void saveToFile(const std::string& json)
{
    FILE* fileDialogPipe = popen("zenity --file-selection --save --title=\"Save scene as ...\"", "r");

    if(fileDialogPipe)
    {
        char name[1024] = { 0 };

        while(!feof(fileDialogPipe))
            fgets(name, sizeof(name), fileDialogPipe);

        if(strlen(name) > 0)
        {
            char* transformedName = strtok(name, "\n");
            sprintf(transformedName, "%s.mtnscn", name);
            MTN_INFO("Selected path {}", transformedName);
            FILE* saveFile = fopen(transformedName, "w");

            if(saveFile)
            {
                fprintf(saveFile, "%s", json.c_str());
                fclose(saveFile);
            }
            else
                MTN_ERROR("Unable to save file to {}", name);
        }

        pclose(fileDialogPipe);
    }
    else
        MTN_ERROR("Failed to save scene to file !");
}

static std::optional<std::string> OpenDialog()
{
    FILE* fileDialogPipe = popen("zenity --file-selection --title=\"Select a Mouton scene file ...\"", "r");

    if(fileDialogPipe)
    {
        char path[1024] = { 0 };

        while(!feof(fileDialogPipe))
            fgets(path, sizeof(path), fileDialogPipe);

        pclose(fileDialogPipe);

        if(strlen(path) > 0)
            return std::string(strtok(path, "\n"));
    }

    return std::nullopt;
}

static std::string LoadJsonFromFile(const std::string& filepath)
{
    std::ifstream file(filepath);
    std::stringstream ss;

    if(file.is_open())
        ss << file.rdbuf();
    else
        MTN_ERROR("Failed to read scene from file {}", filepath.c_str());

    return ss.str();
}

static std::string SerializeScene(const Mouton::Scene& scene)
{
    rapidjson::StringBuffer sb;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);

    scene.Serialize(writer);

    return sb.GetString();
}

void BarMenu::ShowMenu(const std::shared_ptr<Mouton::Scene>& scene, EditorLayer* editorLayer)
{
    static bool menuOpened = false;
    static std::string openedScene;

    if(ImGui::BeginMenuBar())
    {
        if(ImGui::BeginMenu("File"))
        {
            if(ImGui::MenuItem("New scene ...")) {}

            if(ImGui::MenuItem("Open scene"))
            {
                // MTN_TRACE("Path {}", OpenDialog().c_str());
                auto path = OpenDialog();

                if(path)
                {
                    auto newScene = Mouton::Scene::FromJson(LoadJsonFromFile(path.value()));
                    editorLayer->SetScene(newScene);
                }
            }

            if(ImGui::BeginMenu("Save ..."))
            {
                if(ImGui::MenuItem("Save scene", "", nullptr, !openedScene.empty()))
                {
                    auto json = SerializeScene(*scene.get());
                    MTN_INFO("Saved scene \n{}", json.c_str());
                }

                if(ImGui::MenuItem("Save as ..."))
                {
                    saveToFile(SerializeScene(*scene.get()));
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

}