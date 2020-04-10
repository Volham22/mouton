#include "WindowEvents.h"

namespace Mouton
{
    WindowMovedEvent::WindowMovedEvent(int x, int y)
        : m_XPos(x), m_YPos(y)
    {
    }

    WindowResizeEvent::WindowResizeEvent(int width, int height)
        : m_Width(width), m_Height(height)
    {
    }

} // namespace Mouton
