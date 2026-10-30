#ifndef TB_EVENTS_KEYBOARD_EVENT_HPP
#define TB_EVENTS_KEYBOARD_EVENT_HPP

#include <tb/events/Event.hpp>

namespace tb::events
{
    
struct KeyboardEvent : public tb::events::Event
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

} // ns tb::events

#endif