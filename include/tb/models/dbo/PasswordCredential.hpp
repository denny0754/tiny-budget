#ifndef TB_APP_MODELS_DB_PASSWORD_CREDENTIAL_HPP
#define TB_APP_MODELS_DB_PASSWORD_CREDENTIAL_HPP

#include <Wt/Dbo/Dbo.h>
#include <Wt/WDateTime.h>
#include <Wt/Dbo/WtSqlTraits.h>
#include <string>

#include <tb/app/models/db/Identity.hpp>

namespace tb::app::models::db
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

    inline Wt::Dbo::ptr<Identity> GetIdentity() const { return m_identity; }
    inline const std::string& GetPasswordHash() const { return m_passwordHash; }
    inline const std::string& GetPasswordAlgo() const { return m_passwordAlgo; }
    inline int GetFailedAttempts() const { return m_failedAttempts; }
    inline const Wt::WDateTime& GetUpdatedOn() const { return m_updatedOn; }

    inline void SetIdentity(const Wt::Dbo::ptr<Identity>& identity) { m_identity = identity; }
    inline void SetPasswordHash(const std::string& password_hash) { m_passwordHash = password_hash; }
    inline void SetPasswordAlgo(const std::string& password_algo) { m_passwordAlgo = password_algo; }
    inline void SetUpdatedOn(const Wt::WDateTime& updated_on) { m_updatedOn = updated_on; }
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