#ifndef TB_CORE_EV_WINDOW_CLOSE_EVENT_HPP
#define TB_CORE_EV_WINDOW_CLOSE_EVENT_HPP

#include <tb/core/ev/Event.hpp>

namespace tb::core::ev
{
    
struct WindowCloseEvent : public Event
{
public:
    WindowCloseEvent()
    {
    }

    const char* GetName() const override { return "WindowCloseEvent"; };

};

} // ns tb::core::ev

#endif