#ifndef MOUSE_EVENTS_H
#define MOUSE_EVENTS_H

#include "MoutonPch.h"

namespace Mouton
{

    // TODO: Add button code and mouse related stuff

    class MouseButtonPressedEvent : public Event
    {
        virtual const char* GetName() const override { return "MouseButtonPressedEvent"; };
        virtual EventType GetType() const override { return EventType::MouseButtonPressed; };
        virtual EventCategory GetCategory() const override { return (EventCategory)(EventCategory::MouseCategory | EventCategory::MouseCategory); };
    };

    class MouseButtonReleased : public Event
    {
        virtual const char* GetName() const override { return "MouseButtonReleased"; };
        virtual EventType GetType() const override { return EventType::MouseButtonReleased; };
        virtual EventCategory GetCategory() const override { return (EventCategory)(EventCategory::MouseCategory | EventCategory::KeysCategory); };
    };

    class MouseMovedEvent : public Event
    {
        virtual const char* GetName() const override { return "MouseMovedEvent"; };
        virtual EventType GetType() const override { return EventType::MouseMoved; };
        virtual EventCategory GetCategory() const override { return (EventCategory)(EventCategory::MouseCategory | EventCategory::KeysCategory); };
    };

    class MouseScrolledEvent : public Event
    {
        virtual const char* GetName() const override { return "MouseScrolledEvent"; };
        virtual EventType GetType() const override { return EventType::MouseScrolled; };
        virtual EventCategory GetCategory() const override { return (EventCategory)(EventCategory::MouseCategory | EventCategory::KeysCategory); };
    };

} // namespace Mouton


#endif