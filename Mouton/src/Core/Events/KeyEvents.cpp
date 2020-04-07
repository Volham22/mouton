#include "KeyEvents.h"

namespace Mouton
{

    KeyEvent::KeyEvent(int keyCode)
        : p_KeyCode(keyCode)
    {
    }

    KeyPressedEvent::KeyPressedEvent(int keyCode)
        : KeyEvent(keyCode)
    {
    }

    KeyReleasedEvent::KeyReleasedEvent(int keyCode)
        : KeyEvent(keyCode)
    {
    }

    KeyMaintainedEvent::KeyMaintainedEvent(int keyCode)
        : KeyEvent(keyCode)
    {
    }

} // namespace Mouton
