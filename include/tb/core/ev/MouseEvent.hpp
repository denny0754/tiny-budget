#ifndef TB_CORE_EV_MOUSE_EVENT_HPP
#define TB_CORE_EV_MOUSE_EVENT_HPP

#include <tb/core/ev/Event.hpp>

namespace tb::core::ev
{
class MouseEvent : public Event
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

} // ns tb::core::ev

#endif