#include "BarMenu.h"

#include <imgui.h>
#include <rapidjson/prettywriter.h>

#include <cstdio>


// Show a file dialog to save the serialized scene
static void saveToFile(const std::string& json)
{
    FILE* fileDialogPipe = popen("zenity --file-selection --save", "r");

    if(fileDialogPipe)
    {
        char name[1024] = { 0 };

        while(!feof(fileDialogPipe))
            fgets(name, sizeof(name), fileDialogPipe);

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

        pclose(fileDialogPipe);
    }
    else
        MTN_ERROR("Failed to save scene to file !");
}

static std::string SerializeScene(const Mouton::Scene& scene)
{
    rapidjson::StringBuffer sb;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);

    scene.Serialize(writer);

    return sb.GetString();
}

void BarMenu::ShowMenu(const Mouton::Scene& scene)
{
    static bool menuOpened = false;
    static std::string openedScene;

    if(ImGui::BeginMenuBar())
    {
        if(ImGui::BeginMenu("File"))
        {
            if(ImGui::MenuItem("New scene ...")) {}

            if(ImGui::MenuItem("Open scene")) {}

            if(ImGui::BeginMenu("Save ..."))
            {
                if(ImGui::MenuItem("Save scene", "", nullptr, !openedScene.empty()))
                {
                    auto json = SerializeScene(scene);
                    MTN_INFO("Saved scene \n{}", json.c_str());
                }

                if(ImGui::MenuItem("Save as ..."))
                {
                    saveToFile(SerializeScene(scene));
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

}