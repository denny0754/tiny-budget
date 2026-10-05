#ifndef TB_CORE_EV_EVENT_HPP
#define TB_CORE_EV_EVENT_HPP

#include <string>

namespace tb::core::ev
{

class Event
{
public:
    virtual ~Event() = default;

    // Mutable allows listeners to consume the event even when passed as const
    mutable bool Handled = false;

    // Forces derived events to provide a name for logging/debugging
    virtual const char* GetName() const = 0;
    
    virtual std::string ToString() const {
        return GetName();
    }
};

} // ns tb::core::ev

#endif