#ifndef TB_MODELS_DBO_IDENTITY_HPP
#define TB_MODELS_DBO_IDENTITY_HPP

#include <Wt/Dbo/Dbo.h>
#include <Wt/WDateTime.h>
#include <Wt/Dbo/WtSqlTraits.h>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <string>

// Forward Declarations
namespace tb::models::dbo
{
class Identity;
class PasswordCredential;
} // ns tb::models::dbo

namespace Wt::Dbo
{

template<>
struct dbo_traits<tb::models::dbo::Identity> : public dbo_default_traits
{
    using IdType = std::string;
    static IdType invalidId() { return std::string(); }
    static const char* surrogateIdField() { return nullptr; }
};

template<>
struct dbo_traits<tb::models::dbo::PasswordCredential> : public dbo_default_traits
{
    using IdType = std::string;
    static IdType invalidId() { return std::string(); }
    static const char* surrogateIdField() { return nullptr; }
};

} // ns Wt::Dbo

namespace tb::models::dbo
{

class Identity
{
public:
    Identity()
    {
        static thread_local boost::uuids::random_generator gen;
        m_id = boost::uuids::to_string(gen());
    }

    template<class Action>
    void persist(Action& action)
    {
        Wt::Dbo::id(action, m_id, "guid", 36);
        Wt::Dbo::field(action, m_email, "email");
        Wt::Dbo::field(action, m_firstName, "first_name");
        Wt::Dbo::field(action, m_lastName, "last_name");
        Wt::Dbo::field(action, m_createdOn, "created_on");
        Wt::Dbo::field(action, m_updatedOn, "updated_on");
        Wt::Dbo::hasOne(action, m_passwordCredential, "identity");
    }

    inline const std::string& GetId() const { return m_id; }
    inline const std::string& GetEmail() const { return m_email; }
    inline const std::string& GetFirstName() const { return m_firstName; }
    inline const std::string& GetLastName() const { return m_lastName; }
    inline const Wt::WDateTime& GetCreatedOn() const { return m_createdOn; }
    inline const Wt::WDateTime& GetUpdatedOn() const { return m_updatedOn; }
    inline Wt::Dbo::weak_ptr<PasswordCredential> GetPasswordCredential() const { return m_passwordCredential; }

    inline void SetEmail(const std::string& email) { m_email = email; }
    inline void SetFirstName(const std::string& first_name) { m_firstName = first_name; }
    inline void SetLastName(const std::string& last_name) { m_lastName = last_name; }
    inline void SetCreatedOn(const Wt::WDateTime& created_on) { m_createdOn = created_on; }
    inline void SetUpdatedOn(const Wt::WDateTime& updated_on) { m_updatedOn = updated_on; }

private:
    std::string m_id;
    std::string m_email;
    std::string m_firstName;
    std::string m_lastName;
    Wt::WDateTime m_createdOn;
    Wt::WDateTime m_updatedOn;

    Wt::Dbo::weak_ptr<PasswordCredential> m_passwordCredential;
}; // cl Identity

class PasswordCredential
{
public:
    PasswordCredential()
    {
        static thread_local boost::uuids::random_generator gen;
        m_id = boost::uuids::to_string(gen());
    }

    template<class Action>
    void persist(Action& action)
    {
        Wt::Dbo::id(action, m_id, "guid", 36);
        Wt::Dbo::belongsTo(action, m_identity, "identity");
        Wt::Dbo::field(action, m_passwordHash, "password_hash");
        Wt::Dbo::field(action, m_failedAttempts, "failed_attempts");
        Wt::Dbo::field(action, m_updatedOn, "updated_on");
    }

    inline const std::string& GetId() const { return m_id; }
    inline Wt::Dbo::ptr<Identity> GetIdentity() const { return m_identity; }
    inline const std::string& GetPasswordHash() const { return m_passwordHash; }
    inline int GetFailedAttempts() const { return m_failedAttempts; }
    inline const Wt::WDateTime& GetUpdatedOn() const { return m_updatedOn; }

    inline void SetIdentity(const Wt::Dbo::ptr<Identity>& identity) { m_identity = identity; }
    inline void SetPasswordHash(const std::string& password_hash) { m_passwordHash = password_hash; }
    inline void SetUpdatedOn(const Wt::WDateTime& updated_on) { m_updatedOn = updated_on; }
    inline void IncrementFailedAttempts() { m_failedAttempts++; }
    inline void ResetFailedAttempts() { m_failedAttempts = 0; }

private:
    std::string m_id;
    Wt::Dbo::ptr<Identity> m_identity;
    std::string m_passwordHash;
    int m_failedAttempts{ 0 };
    Wt::WDateTime m_updatedOn;
}; // cl PasswordCredential



} // ns tb::models::dbo

#endif // TB_MODELS_DBO_IDENTITY_HPP