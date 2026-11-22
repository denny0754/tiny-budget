/*
==========================================================================
 CHANGE LOG
==========================================================================
 Date       | Author        | Task ID | Description
------------+---------------+---------+-----------------------------------
 2026-11-20 | Diego Vaccher | TB-14   | Definition of Database Objects Model
==========================================================================
*/

#ifndef TB_MODELS_DBO_SECURITY_HPP
#define TB_MODELS_DBO_SECURITY_HPP

#include "Common.hpp"

namespace tb::models::dbo
{

class Identity;
class PasswordCredential;

} // ns tb::models::dbo

/*
	Note(https://www.webtoolkit.eu/wt/doc/reference/html/structWt_1_1Dbo_1_1dbo__traits.html):
	>> The safe pattern to define traits is before the class definition,
	>> based on a forward declaration. This is necessary since the persist()
	>> function relies on this specialization.
*/
DEF_WT_DBO_STRING_TRAIT(tb::models::dbo::Identity);
DEF_WT_DBO_STRING_TRAIT(tb::models::dbo::PasswordCredential);

namespace tb::models::dbo
{

class Identity : public tb::models::dbo::BaseObject
{
public:
	/**
	 * @brief Default constructor.
	*/
	Identity() = default;

	/**
	 * @brief Performs a persistence mapping operation on the Identity instance.
	 * @tparam Action Wt::Dbo action type.
	 * @param action Database persistence action.
	 */
	template<class Action>
	void persist(Action& action)
	{
		tb::models::dbo::BaseObject::persist(action);

		Wt::Dbo::field(action, m_email, "email");
		Wt::Dbo::field(action, m_firstName, "first_name");
		Wt::Dbo::field(action, m_lastName, "last_name");

		Wt::Dbo::hasOne(action, m_passwordCredential, "identity");
	}

	/**
	 * @brief Returns the user's email address.
	 * @return Const reference to the email string.
	 */
	inline const std::string& GetEmail() const { return m_email; }

	/**
	 * @brief Returns the user's first name.
	 * @return Const reference to the first name string.
	 */
	inline const std::string& GetFirstName() const { return m_firstName; }

	/**
	 * @brief Returns the user's last name.
	 * @return Const reference to the last name string.
	 */
	inline const std::string& GetLastName() const { return m_lastName; }

	/**
	 * @brief Returns a weak pointer to the associated password credential.
	 * @return Weak DBO pointer referencing the PasswordCredential entity.
	 */
	inline Wt::Dbo::weak_ptr<tb::models::dbo::PasswordCredential> GetPasswordCredential() const { return m_passwordCredential; }

	/**
	 * @brief Sets the user's email address.
	 * @param email Email address to assign.
	 */
	void SetEmail(const std::string& email) { m_email = email; }

	/**
	 * @brief Sets the user's first name.
	 * @param first_name First name to assign.
	 */
	void SetFirstName(const std::string& first_name) { m_firstName = first_name; }

	/**
	 * @brief Sets the user's last name.
	 * @param last_name Last name to assign.
	 */
	void SetLastName(const std::string& last_name) { m_lastName = last_name; }

private:
	std::string m_firstName;

	std::string m_lastName;

	std::string m_email;

	Wt::Dbo::weak_ptr<tb::models::dbo::PasswordCredential> m_passwordCredential;

}; // cl Identity

class PasswordCredential : public tb::models::dbo::BaseObject
{
public:
	/**
	 * @brief Default constructor.
	*/
	PasswordCredential() = default;

	/**
	 * @brief Performs a persistence mapping operation on the PasswordCredential instance.
	 * @tparam Action Wt::Dbo action type.
	 * @param action Database persistence action.
	 */
	template<class Action>
	void persist(Action& action)
	{
		tb::models::dbo::BaseObject::persist(action);

		Wt::Dbo::belongsTo(action, m_identity, "identity");
		Wt::Dbo::field(action, m_passwordHash, "password_hash");
	}

	/**
	 * @brief Returns a pointer to the associated identity.
	 * @return DBO pointer referencing the Identity entity.
	 */
	inline Wt::Dbo::ptr<tb::models::dbo::Identity> GetIdentity() const { return m_identity; }

	/**
	 * @brief Returns the password hash.
	 * @return Const reference to the password hash string.
	 */
	inline const std::string& GetPasswordHash() const { return m_passwordHash; }

	/**
	 * @brief Sets the associated identity.
	 * @param identity DBO pointer referencing the Identity entity to assign.
	 */
	void SetIdentity(const Wt::Dbo::ptr<tb::models::dbo::Identity>& identity) { m_identity = identity; }

	/**
	 * @brief Sets the password hash.
	 * @param password_hash Password hash string to assign.
	 */
	void SetPasswordHash(const std::string& password_hash) { m_passwordHash = password_hash; }

private:
	std::string m_passwordHash;

	Wt::Dbo::ptr<tb::models::dbo::Identity> m_identity;
}; // cl PasswordCredential

} // ns tb::models::dbo

#endif