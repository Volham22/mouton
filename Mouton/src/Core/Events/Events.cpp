#include "Events.h"

namespace Mouton
{

    bool EventSystem::IsInCategories(Event& event, uint8_t categories)
    {
        return event.GetCategory() & categories;
    }

} // namespace Mouton
