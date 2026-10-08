#ifndef TB_CORE_EVENTS_MOUSE_EVENT_HPP
#define TB_CORE_EVENTS_MOUSE_EVENT_HPP

#include <tb/core/events/BaseEvent.hpp>

namespace tb::core::events
{

struct MouseEvent : public BaseEvent
{
public:
    MouseEvent(int button, int action, int mods)
        : Button(button), Action(action), Mods(mods)
    {

    }

    const char* GetName() const override { return "MouseEvent"; };

    int Button;
    int Action;
    int Mods;
};

} // ns tb::core::events

#endif