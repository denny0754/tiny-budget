#ifndef TB_APP_MODELS_PASSWORD_CREDENTIAL_HPP
#define TB_APP_MODELS_PASSWORD_CREDENTIAL_HPP

#include <Wt/Dbo/Dbo.h>
#include <Wt/WDateTime.h>
#include <Wt/Dbo/WtSqlTraits.h>
#include <string>

#include <tb/app/models/Identity.hpp>

namespace tb::app::models
{

class PasswordCredential
{
public:
    template<class Action>
    void persist(Action& action)
    {
        Wt::Dbo::belongsTo(action, m_identity, "identity_id");
        Wt::Dbo::field(action, m_passwordHash, "password_hash");
        Wt::Dbo::field(action, m_passwordAlgo, "password_algo");
        Wt::Dbo::field(action, m_failedAttempts, "failed_attempts");
        Wt::Dbo::field(action, m_updatedOn, "updated_on");
    }

    inline const std::string& GetPasswordHash() { return m_passwordHash; }

    inline const std::string& GetPasswordAlgo() { return m_passwordAlgo; }

    inline int GetFailedAttempts() { return m_failedAttempts; }

    inline const Wt::WDateTime& GetUpdatedOn() { return m_updatedOn; }

    inline void SetPasswordHash(const std::string& password_hash) { m_passwordHash = password_hash; }

    inline void SetPasswordAlgo(const std::string& password_algo) { m_passwordAlgo = password_algo; }

    inline void IncrementFailedAttempts() { m_failedAttempts++; }

    inline void ResetFailedAttempts() { m_failedAttempts = 0; }

private:
    Wt::Dbo::ptr<Identity> m_identity;
    std::string m_passwordHash;
    std::string m_passwordAlgo;
    int m_failedAttempts{0};
    Wt::WDateTime m_updatedOn;
};

} // ns tb::app::models

#endif