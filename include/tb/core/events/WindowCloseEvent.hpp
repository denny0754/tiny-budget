#ifndef TB_CORE_EVENTS_WINDOW_CLOSE_EVENT_HPP
#define TB_CORE_EVENTS_WINDOW_CLOSE_EVENT_HPP

#include <tb/core/events/BaseEvent.hpp>

namespace tb::core::events
{
    
struct WindowCloseEvent : public BaseEvent
{
public:
    WindowCloseEvent()
    {
    }

    const char* GetName() const override { return "WindowCloseEvent"; };

};

} // ns tb::core::events

#endif