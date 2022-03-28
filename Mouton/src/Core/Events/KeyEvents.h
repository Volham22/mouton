#ifndef KEY_EVENTS_H
#define KEY_EVENTS_H

#include "MoutonPch.h"

namespace Mouton {

    class KeyEvent : public Event
    {
      public:
        KeyEvent(int keyCode);
        int GetCode() const { return p_KeyCode; }
        virtual EventCategory GetCategory() const override
        {
            return EventCategory::KeysCategory;
        }

      protected:
        int p_KeyCode;
    };

    class KeyPressedEvent : public KeyEvent
    {
      public:
        KeyPressedEvent(int keyCode);
        virtual const char* GetName() const override
        {
            return "KeyPressedEvent";
        };
        virtual EventType GetType() const override
        {
            return EventType::KeyPressed;
        };
    };

    class KeyReleasedEvent : public KeyEvent
    {
      public:
        KeyReleasedEvent(int keyCode);
        virtual const char* GetName() const override
        {
            return "KeyReleasedEvent";
        };
        virtual EventType GetType() const override
        {
            return EventType::KeyReleased;
        };
    };

    class KeyMaintainedEvent : public KeyEvent
    {
      public:
        KeyMaintainedEvent(int keyCode);
        virtual const char* GetName() const override
        {
            return "KeyMaintainedEvent";
        };
        virtual EventType GetType() const override
        {
            return EventType::KeyMaintained;
        };
    };

} // namespace Mouton

#endif