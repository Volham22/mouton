#ifndef SCRIPT_SKELETON_FACTORY
#define SCRIPT_SKELETON_FACTORY

#include "MoutonPch.h"

namespace Mouton {

    class ScriptSkeletonFactory
    {
      public:
        static void
        CreateSpriteComponentSkeleton(const std::string& moduleName,
                                      const std::string& templateFile);
    };

} // namespace Mouton

#endif