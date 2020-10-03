#include "ScriptSkeletonFactory.h"

#include <fstream>
#include <sstream>

#define MTN_TEMPLATES_DIR ".PythonBehaviourScriptsTemplates"

namespace Mouton
{

    void ScriptSkeletonFactory::CreateSpriteComponentSkeleton(const std::string& moduleName)
    {
        std::string fileName = moduleName.substr(moduleName.find_last_of('.') + 1) != ".py" ? moduleName + ".py" : moduleName;

        std::ifstream templateFile(MTN_TEMPLATES_DIR "/SpriteComponentScriptTemplate.mtnt", std::ifstream::in);
        std::stringstream result;

        MTN_ASSERT(templateFile.is_open(), "SpriteComponent template file not found !");

        for(std::string line; getline(templateFile, line);)
        {
            for(auto it = line.find("%name%"); it != std::string::npos; it = line.find("%name%"))
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
