#ifndef APPLICATION_H
#define APPLICATION_H

#include "MoutonPch.h"

namespace Mouton {
    // TODO: Window events

    class ApplicationEvent : public Event
    {
      public:
        virtual const char* GetName() const override
        {
            return "ApplicationEvent";
        };
        virtual EventType GetType() const override
        {
            return EventType::ApplicationEvent;
        };
        virtual EventCategory GetCategory() const override
        {
            return EventCategory::ApplicationCategory;
        };
    };

} // namespace Mouton

#endif