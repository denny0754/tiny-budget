#ifndef TB_EVENTS_MOUSE_EVENT_HPP
#define TB_EVENTS_MOUSE_EVENT_HPP

#include <tb/events/Event.hpp>

namespace tb::events
{

struct MouseEvent : public tb::events::Event
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

} // ns tb::events

#endif