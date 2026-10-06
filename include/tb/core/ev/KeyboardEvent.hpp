#ifndef TB_CORE_EV_KEYBOARD_EVENT_HPP
#define TB_CORE_EV_KEYBOARD_EVENT_HPP

#include <tb/core/ev/Event.hpp>

namespace tb::core::ev
{
    
struct KeyboardEvent : public Event
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

} // ns tb::core::ev

#endif