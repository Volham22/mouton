#ifndef WINDOW_EVENT_H
#define WINDOW_EVENT_H

#include "MoutonPch.h"

namespace Mouton
{

    class WindowEvent : public Event
    {
    public:
        virtual const char* GetName() const = 0;
        virtual EventType GetType() const = 0;
        EventCategory GetCategory() const override { return EventCategory::WindowCategory; };
    };

    class WindowFocusEvent : public WindowEvent
    {
    public:
        virtual const char* GetName() const { return "WindowFocusEvent"; };
        virtual EventType GetType() const { return EventType::WindowFocus; };
    };

    class WindowLostFocusEvent : public WindowEvent
    {
    public:
        virtual const char* GetName() const { return "WindowLostFocusEvent"; };
        virtual EventType GetType() const { return EventType::WindowLostFocus; };
    };

    class WindowResizeEvent : public WindowEvent
    {
    public:
        WindowResizeEvent(int width, int height);
        virtual const char* GetName() const { return "WindowResizeEvent"; };
        virtual EventType GetType() const { return EventType::WindowResize; };

        inline int GetWidth() const { return m_Width; }
        inline int GetHeight() const { return m_Height; }
    
    private:
        int m_Width, m_Height;
    };

    class WindowMovedEvent : public WindowEvent
    {
    public:
        WindowMovedEvent(int x, int y);
        virtual const char* GetName() const { return "WindowMovedEvent"; };
        virtual EventType GetType() const { return EventType::WindowMoved; };

        inline int GetXPos() const { return m_XPos; }
        inline int GetYPos() const { return m_YPos; }

    private:
        int m_XPos, m_YPos;
    };

    class WindowCloseEvent : public WindowEvent
    {
    public:
        virtual const char* GetName() const { return "WindowCloseEvent"; };
        virtual EventType GetType() const { return EventType::WindowClose; };
    };

    class WindowMinimizedEvent : public WindowEvent
    {
    public:
        virtual const char* GetName() const { return "WindowMinimizedEvent"; };
        virtual EventType GetType() const { return EventType::WindowMinimized; };
    };

} // namespace Mouton


#endif