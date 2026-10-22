#include <tb/core/Session.hpp>

namespace tb::core
{

Session::Session(std::shared_ptr < tb::events::EventDispatcher dispatcher)
	: m_eventDispatcher(dispatcher)
{

}

} // ns tb::core