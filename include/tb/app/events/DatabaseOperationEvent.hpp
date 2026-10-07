#ifndef TB_APP_EVENTS_DATABASE_OPERATION_EVENT_HPP
#define TB_APP_EVENTS_DATABASE_OPERATION_EVENT_HPP

#include <Wt/Dbo/Dbo.h>

#include <functional>

#include <tb/core/ev/Event.hpp>

namespace tb::app::events
{

enum class DBOpType
{
    Action,
    Query
};

struct DatabaseOperationEvent : public tb::core::ev::Event
{
    DBOpType Type;
    std::function<void(Wt::Dbo::Session& session)> Payload;

    // Constructor for Actions (Writes/Transactions)
    explicit DatabaseOperationEvent(std::function<void(Wt::Dbo::Session&)> payload)
        : Type(DBOpType::Action), Payload(std::move(payload)) {}

    // Constructor for Queries (Reads) - explicitly named or overloaded if needed
    DatabaseOperationEvent(DBOpType type, std::function<void(Wt::Dbo::Session&)> payload)
        : Type(type), Payload(std::move(payload)) {}

    const char* GetName() const override { return "DatabaseOperationEvent"; }
};

} // ns tb::app::events
 
#endif