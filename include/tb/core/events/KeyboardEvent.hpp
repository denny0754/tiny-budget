#ifndef TB_CORE_EVENTS_KEYBOARD_EVENT_HPP
#define TB_CORE_EVENTS_KEYBOARD_EVENT_HPP

#include <tb/core/events/BaseEvent.hpp>

namespace tb::core::events
{
    
struct KeyboardEvent : public BaseEvent
{
public:
    KeyboardEvent(int key, int scancode, int action, int mods)
        : Key(key), Scancode(scancode), Action(action), Mods(mods)
    {

    }

    const char* GetName() const override { return "KeyboardEvent"; };

    int Key;
    int Action;
    int Scancode;
    int Mods;
};

} // ns tb::core::events

#endif