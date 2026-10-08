#include <tb/app/api/LocalApiProvider.hpp>

#include <Wt/Dbo/backend/Sqlite3.h>
#include <tb/app/models/db/Identity.hpp>
#include <tb/app/models/db/PasswordCredential.hpp>


namespace tb::app::api
{

void LocalApiProvider::Init()
{
	auto sqlite3Session = std::make_unique<Wt::Dbo::backend::Sqlite3>(":memory:");

	m_dbSession.setConnection(std::move(sqlite3Session));

	m_dbSession.mapClass<tb::app::models::db::Identity>("identity");
	m_dbSession.mapClass<tb::app::models::db::PasswordCredential>("password_credential");
}

void LocalApiProvider::SignUp(
	const tb::app::models::api::SignUpRequest& data,
	APICallback<tb::app::models::api::SignUpResponse> callback
)
{
    Wt::Dbo::Transaction trx(m_dbSession);

    auto now = Wt::WDateTime::currentDateTime();

    // 1. Instantiation and property assignment for Identity
    auto identity = std::make_unique<tb::app::models::db::Identity>();
    identity->SetEmail(data.Email);
    identity->SetFirstName(data.FirstName);
    identity->SetLastName(data.LastName);
    identity->SetCreatedOn(now);
    identity->SetUpdatedOn(now);

    // 2. Add Identity to session -> produces a Wt::Dbo::ptr handle
    Wt::Dbo::ptr<tb::app::models::db::Identity> identityPtr = m_dbSession.add(std::move(identity));

    // 3. Instantiation and property assignment for PasswordCredential
    auto cred = std::make_unique<tb::app::models::db::PasswordCredential>();
    cred->SetIdentity(identityPtr); // Assign foreign key relation (belongsTo side)
    cred->SetPasswordAlgo("argon2id"); // Set actual hash algorithms
    cred->SetPasswordHash(data.Password); //!TODO: Hashing the password before actually sending it to the Database.
    cred->SetUpdatedOn(now);

    // 4. Add PasswordCredential to session
    Wt::Dbo::ptr<tb::app::models::db::PasswordCredential> credPtr = m_dbSession.add(std::move(cred));

    // Commit writes both rows inside the database transaction block
    trx.commit();
}

void LocalApiProvider::SignIn(
	const tb::app::models::api::SignInRequest& data,
	APICallback<tb::app::models::api::SignInResponse> callback
)
{

}

} // ns tb::app::api