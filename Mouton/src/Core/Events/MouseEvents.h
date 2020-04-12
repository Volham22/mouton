#ifndef MOUSE_EVENTS_H
#define MOUSE_EVENTS_H

#include "MoutonPch.h"

namespace Mouton
{

    class MouseButtonEvent : public Event
    {
    public:
        MouseButtonEvent(int keyCode) : p_Keycode(keyCode) {};
        int GetCode() const { return p_Keycode; };
        virtual const char* GetName() const = 0;
        virtual EventType GetType() const = 0;
        virtual EventCategory GetCategory() const override { return EventCategory::MouseCategory; };

    protected:
        int p_Keycode;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int keycode) : MouseButtonEvent(keycode) {};
        virtual const char* GetName() const override { return "MouseButtonPressedEvent"; };
        virtual EventType GetType() const override { return EventType::MouseButtonPressed; };
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int keycode) : MouseButtonEvent(keycode) {};
        virtual const char* GetName() const override { return "MouseButtonReleased"; };
        virtual EventType GetType() const override { return EventType::MouseButtonReleased; };
    };

    class MouseButtonMaintainedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonMaintainedEvent(int keycode) : MouseButtonEvent(keycode) {};
        virtual const char* GetName() const override { return "MouseButtonMaintained"; };
        virtual EventType GetType() const override { return EventType::MouseButtonMaintained; };
    };

    class MouseMovedEvent : public Event
    {
    public:
        virtual const char* GetName() const override { return "MouseMovedEvent"; };
        virtual EventType GetType() const override { return EventType::MouseMoved; };
        virtual EventCategory GetCategory() const override { return EventCategory::MouseCategory; };

    };

    class MouseScrolledEvent : public Event
    {
    public:
        virtual const char* GetName() const override { return "MouseScrolledEvent"; };
        virtual EventType GetType() const override { return EventType::MouseScrolled; };
        virtual EventCategory GetCategory() const override { return EventCategory::MouseCategory; };
    };

} // namespace Mouton


#endif