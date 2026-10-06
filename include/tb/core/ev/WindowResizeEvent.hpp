#ifndef TB_CORE_EV_WINDOW_RESIZE_EVENT_HPP
#define TB_CORE_EV_WINDOW_RESIZE_EVENT_HPP

#include <tb/core/ev/Event.hpp>

namespace tb::core::ev
{
    
struct WindowResizeEvent : public Event
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

} // ns tb::core::ev

#endif