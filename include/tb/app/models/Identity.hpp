#ifndef TB_APP_MODELS_IDENTITY_HPP
#define TB_APP_MODELS_IDENTITY_HPP

#include <Wt/Dbo/Dbo.h>
#include <Wt/WDateTime.h>
#include <Wt/Dbo/WtSqlTraits.h>
#include <string>

namespace tb::app::models
{

class PasswordCredential;

class Identity
{
public:
    template<class Action>
    void persist(Action& action)
    {
        Wt::Dbo::field(action, m_email, "email");
        Wt::Dbo::field(action, m_firstName, "first_name");
        Wt::Dbo::field(action, m_lastName, "last_name");
        Wt::Dbo::field(action, m_createdOn, "created_on");
        Wt::Dbo::field(action, m_updatedOn, "updated_on");
        Wt::Dbo::hasOne(action, m_passwordCredential, "identity_id");
    }

    inline const std::string& GetEmail() { return m_email; }

    inline const std::string& GetFirstName() { return m_firstName; }

    inline const std::string& GetLastName() { return m_lastName; }

    inline const Wt::WDateTime& GetCreatedOn() { return m_createdOn; }

    inline const Wt::WDateTime& GetUpdatedOn() { return m_updatedOn; }

    inline Wt::Dbo::weak_ptr<PasswordCredential> GetPasswordCredential() { return m_passwordCredential; }

    inline void SetEmail(const std::string& email) { m_email = email; }

    inline void SetFirstName(const std::string& first_name) { m_firstName = first_name; }

    inline void SetLastName(const std::string& last_name) { m_lastName = last_name; }

private:
    std::string m_email;

    std::string m_firstName;

    std::string m_lastName;

    Wt::WDateTime m_createdOn;

    Wt::WDateTime m_updatedOn;

    Wt::Dbo::weak_ptr<PasswordCredential> m_passwordCredential;
};

} // ns tb::app::models

#endif