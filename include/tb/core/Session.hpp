#ifndef TB_CORE_SESSION_HPP
#define TB_CORE_SESSION_HPP

#include <tb/events/EventDispatcher.hpp>

#include <memory>

namespace tb::core
{

class Session
{
public:
	Session(std::shared_ptr<tb::events::EventDispatcher> dispatcher);

private:
	std::shared_ptr<tb::events::EventDispatcher> m_eventDispatcher;

}; // cl Session

} // ns tb::core

#endif