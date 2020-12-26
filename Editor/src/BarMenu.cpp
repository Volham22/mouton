#include "BarMenu.h"

#include <imgui.h>
#include <rapidjson/prettywriter.h>


void BarMenu::ShowMenu(const Mouton::Scene& scene)
{
    static bool menuOpened = false;

    if(ImGui::BeginMenuBar())
    {
        if(ImGui::BeginMenu("File"))
        {
            if(ImGui::MenuItem("New scene ...")) {}

            if(ImGui::MenuItem("Open scene")) {}

            if(ImGui::BeginMenu("Save ..."))
            {
                if(ImGui::MenuItem("Save scene"))
                {
                    rapidjson::StringBuffer sb;
                    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);

                    scene.Serialize(writer);

                    MTN_INFO("Saved scene \n{}", sb.GetString());
                }

                if(ImGui::MenuItem("Save as ..."))
                {

                }

                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

}