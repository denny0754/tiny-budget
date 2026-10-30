#ifndef TB_API_SERVICE_HPP
#define TB_API_SERVICE_HPP

#include <tb/core/Context.hpp>
#include <tb/api/Client.hpp>
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <cassert>
#include <utility>

namespace tb::api
{

class Service
{
public:
    Service(std::shared_ptr<tb::core::SessionContext> ctx);
    
    ~Service();

    template<typename TInterface>
    [[nodiscard]] std::shared_ptr<TInterface> GetClient() const
    {
        static_assert(std::is_base_of_v<tb::api::Client, TInterface>,
            "TInterface must derive from tb::api::Client.");

        auto typeIndex = std::type_index(typeid(TInterface));
        auto it = m_clients.find(typeIndex);

        assert(it != m_clients.end() && "Requested API client interface is not registered!");

        if (it != m_clients.end())
        {
            return std::static_pointer_cast<TInterface>(it->second);
        }

        return nullptr;
    }

    [[nodiscard]] const std::shared_ptr<tb::core::SessionContext>& GetSessionContext() const
    {
        return m_sessionContext;
    }

protected:
    template<typename TInterface>
    void RegisterClient()
    {
        static_assert(std::is_base_of_v<tb::api::Client, TInterface>,
            "TInterface must derive from tb::api::Client.");

        auto typeIndex = std::type_index(typeid(TInterface));

        auto client = std::make_shared<TInterface>(m_sessionContext, m_dbSession);
        m_clients[typeIndex] = std::move(client);
    }

private:
    std::unordered_map<std::type_index, std::shared_ptr<tb::api::Client>> m_clients;

    std::shared_ptr<tb::core::SessionContext> m_sessionContext;

    std::shared_ptr<Wt::Dbo::Session> m_dbSession;
};

} // ns tb::api

#endif // TB_API_SERVICE_HPP