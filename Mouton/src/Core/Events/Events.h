#ifndef EVENTS_H
#define EVENTS_H

#include "MoutonPch.h"

namespace Mouton {
    enum class EventType {
        // Keys
        KeyPressed,
        KeyReleased,
        KeyMaintained,
        // Mouse
        MouseButtonPressed,
        MouseButtonReleased,
        MouseButtonMaintained,
        MouseMoved,
        MouseScrolled,
        // Window
        WindowFocus,
        WindowLostFocus,
        WindowResize,
        WindowClose,
        WindowMoved,
        WindowMinimized,
        // Application
        ApplicationEvent
    };

    // EventCategory is a bitmask
    enum EventCategory : uint8_t {
        KeysCategory = 0x01,
        WindowCategory = 0x01 << 1,
        MouseCategory = 0x01 << 2,
        ApplicationCategory = 0x01 << 3
    };

    class Event
    {
      public:
        virtual const char* GetName() const = 0;
        virtual EventType GetType() const = 0;
        virtual EventCategory GetCategory() const = 0;
        bool& Handled() { return p_Handled; }

      protected:
        bool p_Handled = false;
    };

    class EventSystem
    {
      public:
        template<typename T>
        static bool ApplyFunction(Event* event,
                                  std::function<bool(Event&)> func)
        {
            if (dynamic_cast<T*>(event))
            {
                event->Handled() = func(*event);
                return true;
            } else
                return false;
        }

        static bool IsInCategories(Event& event, uint8_t categories);
    };

} // namespace Mouton

#endif