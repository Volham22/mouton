#include "ScriptSkeletonFactory.h"

#include <fstream>
#include <sstream>

#define MTN_TEMPLATES_DIR ".PythonBehaviourScriptsTemplates/"

namespace Mouton {

    void ScriptSkeletonFactory::CreateSpriteComponentSkeleton(
        const std::string& moduleName, const std::string& templateName)
    {
        std::string fileName
            = moduleName.substr(moduleName.find_last_of('.') + 1) != ".py"
                  ? moduleName + ".py"
                  : moduleName;
        char buffer[255];
        sprintf(buffer, "%s%s", MTN_TEMPLATES_DIR, templateName.c_str());
        MTN_TRACE(buffer);

        std::ifstream templateFile(buffer, std::ifstream::in);

        std::stringstream result;

        MTN_ASSERT(templateFile.is_open(),
                   "SpriteComponent template file not found !");

        for (std::string line; getline(templateFile, line);)
        {
            for (auto it = line.find("%name%"); it != std::string::npos;
                 it = line.find("%name%"))
                line.replace(it, 6, moduleName);

            result << line << '\n';
        }

        std::ofstream fileResult(fileName);
        fileResult << result.str();

        templateFile.close();
        fileResult.flush();
        fileResult.close();
    }

} // namespace Mouton
