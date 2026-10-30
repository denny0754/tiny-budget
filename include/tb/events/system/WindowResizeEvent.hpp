#ifndef TB_EVENTS_WINDOW_RESIZE_EVENT_HPP
#define TB_EVENTS_WINDOW_RESIZE_EVENT_HPP

#include <tb/events/Event.hpp>

namespace tb::events
{
    
struct WindowResizeEvent : public tb::events::Event
{
public:
    explicit WindowResizeEvent(int width, int height)
        : Width(width), Height(height)
    {

    }

    const char* GetName() const override { return "WindowResizeEvent"; };

    int Width;
    int Height;
};

} // ns tb::events

#endif