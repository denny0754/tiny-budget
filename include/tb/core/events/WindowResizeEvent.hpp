#ifndef TB_CORE_EVENTS_WINDOW_RESIZE_EVENT_HPP
#define TB_CORE_EVENTS_WINDOW_RESIZE_EVENT_HPP

#include <tb/core/events/BaseEvent.hpp>

namespace tb::core::events
{
    
struct WindowResizeEvent : public BaseEvent
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

} // ns tb::core::events

#endif