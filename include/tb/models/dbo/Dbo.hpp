/*
================================================================================
 CHANGE LOG
================================================================================
 Date       | Author        | Task ID       | Description
------------+---------------+---------------+-----------------------------------
 2026-11-12 | Diego Vaccher | DM-0000010-M  | Data Model Refactor
================================================================================
*/

#ifndef TB_MODELS_DBO_IDENTITY_HPP
#define TB_MODELS_DBO_IDENTITY_HPP

#include <Wt/Dbo/Dbo.h>
#include <Wt/WDateTime.h>
#include <Wt/Dbo/WtSqlTraits.h>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <string>

// Forward declarations of DBOs for traits definition
namespace tb::models::dbo
{

/* Base Types */
class BaseEntity;

/* Authentication & Identity Types */
class Identity;
class PasswordCredential;

/* Container Types */
class Book;

/* Entities Types */
class Partner;
class Account;

/* Operations Types */
class Transaction;
class TransactionItem;
class Product;

/*Code List Types*/
class BookStatus;
class Currency;
class AccountType;

} // ns tb::models::dbo

#define TB_SET_DBO_STRING_ID_TRAIT(full_class) namespace Wt::Dbo \
{ \
template<>\
struct dbo_traits<full_class> : public dbo_default_traits\
{\
    using IdType = std::string;\
    static IdType invalidId() { return std::string(); }\
    static const char* surrogateIdField() { return nullptr; }\
};\
} // #define TB_SET_DBO_STRING_ID_TRAIT

TB_SET_DBO_STRING_ID_TRAIT(tb::models::dbo::BaseEntity);
TB_SET_DBO_STRING_ID_TRAIT(tb::models::dbo::Identity);
TB_SET_DBO_STRING_ID_TRAIT(tb::models::dbo::PasswordCredential);
TB_SET_DBO_STRING_ID_TRAIT(tb::models::dbo::Book);
TB_SET_DBO_STRING_ID_TRAIT(tb::models::dbo::Partner);
TB_SET_DBO_STRING_ID_TRAIT(tb::models::dbo::Account);
TB_SET_DBO_STRING_ID_TRAIT(tb::models::dbo::Transaction);
TB_SET_DBO_STRING_ID_TRAIT(tb::models::dbo::TransactionItem);
TB_SET_DBO_STRING_ID_TRAIT(tb::models::dbo::Product);
TB_SET_DBO_STRING_ID_TRAIT(tb::models::dbo::BookStatus);
TB_SET_DBO_STRING_ID_TRAIT(tb::models::dbo::Currency);
TB_SET_DBO_STRING_ID_TRAIT(tb::models::dbo::AccountType);

// Definition of DBOs Entities
namespace tb::models::dbo
{

// -----------------------------------------------------------------------------
// Base Entities
// -----------------------------------------------------------------------------
/*
    Table: N/D -> This is a DBO BaseEntity used internally to facilitate the definition
    of common fields.
    
    | Column Name |   SQL Type  |    C++ Type   |        C++ Field        |               Notes               |
    |:-----------:|:-----------:|:-------------:|:-----------------------:|:---------------------------------:|
    |     guid    |     UUID    |  std::string  | BaseEntity::m_guid      | Auto-generated at object creation |
    |  created_on | TIMESTAMPTZ | Wt::WDateTime | BaseEntity::m_createdOn | Auto filled                       |
    |  updated_on | TIMESTAMPTZ | Wt::WDateTime | BaseEntity::m_updatedOn | Auto-filled                       |
*/
class BaseEntity
{
public:
    BaseEntity()
    {
        static thread_local boost::uuids::random_generator gen;
        m_guid = boost::uuids::to_string(gen());
    }

    template<class Action>
    void persist(Action& action)
    {
        // Auto-update timestamps when writing to database
        if (!action.getsValue())
        {
            m_updatedOn = Wt::WDateTime::currentDateTime();
            if (m_createdOn.isNull())
            {
                m_createdOn = m_updatedOn;
            }
        }

        Wt::Dbo::id(action, m_guid, "guid", 36);
        Wt::Dbo::field(action, m_createdOn, "created_on");
        Wt::Dbo::field(action, m_updatedOn, "updated_on");
    }

    inline const std::string& GetId() const { return m_guid; }
    inline const Wt::WDateTime& GetCreatedOn() const { return m_createdOn; }
    inline const Wt::WDateTime& GetUpdatedOn() const { return m_updatedOn; }

protected:
    std::string m_guid;
    Wt::WDateTime m_createdOn;
    Wt::WDateTime m_updatedOn;
}; // cl BaseEntity

// -----------------------------------------------------------------------------
// Authentication & Identity Types
// -----------------------------------------------------------------------------
/*
    Table: identity -> Defines the Identity and Metadata of the User registering and connecting to TinyBudget.

    | Column Name |   SQL Type  |                        C++ Type                        |            C++ Field           |                                  Notes                                 |
    |:-----------:|:-----------:|:------------------------------------------------------:|:------------------------------:|:----------------------------------------------------------------------:|
    |     guid    |     UUID    |                       std::string                      |       BaseEntity::m_guid       | Auto-generated at object creation                                      |
    |  created_on | TIMESTAMPTZ |                      Wt::WDateTime                     |     BaseEntity::m_createdOn    | Auto filled                                                            |
    |  updated_on | TIMESTAMPTZ |                      Wt::WDateTime                     |     BaseEntity::m_updatedOn    | Auto-filled                                                            |
    |    email    |   VARCHAR   |                       std::string                      |        Identity::m_email       |                                                                        |
    |  first_name |   VARCHAR   |                       std::string                      |      Identity::m_firstName     |                                                                        |
    |  last_name  |   VARCHAR   |                       std::string                      |      Identity::m_lastName      |                                                                        |
    |    -N/D-    |    -N/D-    | Wt::Dbo::weak_ptr<tb::models::dbo::PasswordCredential> | Identity::m_passwordCredential | Internal pointer to PasswordCredential record.                         |
    |    -N/D-    |    -N/D-    |       Wt::Dbo::collection<tb::models::dbo::Book>       |        Identity::m_books       | Internal collection of pointers to Book records owned by the Identity. |
*/
class Identity : public tb::models::dbo::BaseEntity
{
public:
    Identity() = default;

    template<class Action>
    void persist(Action& action)
    {
        tb::models::dbo::BaseEntity::persist(action);

        Wt::Dbo::field(action, m_email, "email");
        Wt::Dbo::field(action, m_firstName, "first_name");
        Wt::Dbo::field(action, m_lastName, "last_name");

        Wt::Dbo::hasOne(action, m_passwordCredential, "identity");
        Wt::Dbo::hasMany(action, m_books, Wt::Dbo::ManyToOne, "identity");
    }

    void SetEmail(const std::string& email) { m_email = email; }
    void SetFirstName(const std::string& first_name) { m_firstName = first_name; }
    void SetLastName(const std::string& last_name) { m_lastName = last_name; }

    const std::string& GetEmail() const { return m_email; }
    const std::string& GetFirstName() const { return m_firstName; }
    const std::string& GetLastName() const { return m_lastName; }
    inline Wt::Dbo::weak_ptr<tb::models::dbo::PasswordCredential> GetPasswordCredential() const { return m_passwordCredential; }
    inline Wt::Dbo::collection<tb::models::dbo::Book> GetFinancialBooks() const { return m_books; }

private:
    std::string m_firstName;
    std::string m_lastName;

    std::string m_email;

    Wt::Dbo::weak_ptr<tb::models::dbo::PasswordCredential> m_passwordCredential;
    Wt::Dbo::collection<tb::models::dbo::Book> m_books;
}; // cl Identity

/*
    Table: password_credential -> Defines basic password authentication method to sign-up and sign-in to TinyBudget.

    |  Column Name  |   SQL Type  |                 C++ Type                |              C++ Field             |                            Notes                            |
    |:-------------:|:-----------:|:---------------------------------------:|:----------------------------------:|:-----------------------------------------------------------:|
    |      guid     |     UUID    |               std::string               |         BaseEntity::m_guid         | Auto-generated at object creation                           |
    |   created_on  | TIMESTAMPTZ |              Wt::WDateTime              |       BaseEntity::m_createdOn      | Auto filled                                                 |
    |   updated_on  | TIMESTAMPTZ |              Wt::WDateTime              |       BaseEntity::m_updatedOn      | Auto-filled                                                 |
    | password_hash |   VARCHAR   |               std::string               | PasswordCredential::m_passwordHash | Argon2id Hashed Password                                    |
    | identity_guid |     UUID    | Wt::Dbo::ptr<tb::models::dbo::Identity> |   PasswordCredential::m_identity   | Foreign key and reference to the Password Credential record |
*/
class PasswordCredential : public tb::models::dbo::BaseEntity
{
public:
    PasswordCredential() = default;

    template<class Action>
    void persist(Action& action)
    {
        tb::models::dbo::BaseEntity::persist(action);

        Wt::Dbo::belongsTo(action, m_identity, "identity");
        Wt::Dbo::field(action, m_passwordHash, "password_hash");
    }

    inline Wt::Dbo::ptr<tb::models::dbo::Identity> GetIdentity() const { return m_identity; }
    inline const std::string& GetPasswordHash() const { return m_passwordHash; }

    inline void SetIdentity(const Wt::Dbo::ptr<tb::models::dbo::Identity>& identity) { m_identity = identity; }
    inline void SetPasswordHash(const std::string& password_hash) { m_passwordHash = password_hash; }

private:
    std::string m_passwordHash;

    Wt::Dbo::ptr<tb::models::dbo::Identity> m_identity;
}; // cl PasswordCredential

// -----------------------------------------------------------------------------
// Container Types
// -----------------------------------------------------------------------------
/*
    Table: book -> Defines a container(Book) for all Operations and Entities.

    |  Column Name  |   SQL Type  |                 C++ Type                |            C++ Field           |                            Notes                            |
    |:-------------:|:-----------:|:---------------------------------------:|:------------------------------:|:-----------------------------------------------------------:|
    |      guid     |     UUID    |               std::string               |       BaseEntity::m_guid       | Auto-generated at object creation                           |
    |   created_on  | TIMESTAMPTZ |              Wt::WDateTime              |     BaseEntity::m_createdOn    | Auto filled                                                 |
    |   updated_on  | TIMESTAMPTZ |              Wt::WDateTime              |     BaseEntity::m_updatedOn    | Auto-filled                                                 |
    |      name     |   VARCHAR   |               std::string               |          Book::m_name          | Name of the Book                                            |
    |  description  |   VARCHAR   |               std::string               |       Book::m_description      | Description of the Book                                     |
    | identity_guid |     UUID    | Wt::Dbo::ptr<tb::models::dbo::Identity> | PasswordCredential::m_identity | Foreign key and reference to the Password Credential record |
*/
class Book : public tb::models::dbo::BaseEntity
{
public:
    Book() = default;

    template<class Action>
    void persist(Action& action)
    {
        BaseEntity::persist(action);

        Wt::Dbo::belongsTo(action, m_identity, "identity");
        Wt::Dbo::field(action, m_name, "name");
        Wt::Dbo::field(action, m_description, "description");
    }

    inline Wt::Dbo::ptr<Identity> GetIdentity() const { return m_identity; }
    inline const std::string& GetName() const { return m_name; }
    inline const std::string& GetDescription() const { return m_description; }

    inline void SetIdentity(const Wt::Dbo::ptr<Identity>& identity) { m_identity = identity; }
    inline void SetName(const std::string& name) { m_name = name; }
    inline void SetDescription(const std::string& description) { m_description = description; }

private:
    Wt::Dbo::ptr<Identity> m_identity;
    std::string m_name;
    std::string m_description;

}; // cl Book

// -----------------------------------------------------------------------------
// Entities Types
// -----------------------------------------------------------------------------
/*
    Table: partner -> Partner are entities with which the user makes transactions with.

    |  Column Name  |   SQL Type  |                 C++ Type                |        C++ Field        |                     Notes                        |
    |:-------------:|:-----------:|:---------------------------------------:|:-----------------------:|:------------------------------------------------:|
    |      guid     |     UUID    |               std::string               |    BaseEntity::m_guid   | Auto-generated at object creation                |
    |   created_on  | TIMESTAMPTZ |              Wt::WDateTime              | BaseEntity::m_createdOn | Auto filled                                      |
    |   updated_on  | TIMESTAMPTZ |              Wt::WDateTime              | BaseEntity::m_updatedOn | Auto-filled                                      |
    |     name1     |   VARCHAR   |               std::string               |     Partner::m_name1    | Name 1 of the Partner                            |
    |     name2     |   VARCHAR   |               std::string               |     Partner::m_name2    | Name 2 of the Partner                            |
    |     name3     |   VARCHAR   |               std::string               |     Partner::m_name3    | Name 3 of the Partner                            |
    |   book_guid   |     UUID    |   Wt::Dbo::ptr<tb::models::dbo::Book>   |     Partner::m_book     | Foreign key and reference to the Book record     |
    | identity_guid |     UUID    | Wt::Dbo::ptr<tb::models::dbo::Identity> |   Partner::m_identity   | Foreign key and reference to the Identity record |
*/
class Partner : public  tb::models::dbo::BaseEntity
{
public:
    Partner() = default;

    template<class Action>
    void persist(Action& action)
    {
        BaseEntity::persist(action);

        Wt::Dbo::field(action, m_name1, "name1");
        Wt::Dbo::field(action, m_name2, "name2");
        Wt::Dbo::field(action, m_name3, "name3");
        Wt::Dbo::belongsTo(action, m_identity, "identity");
        Wt::Dbo::belongsTo(action, m_book, "book");
    }

    const std::string& GetName1() const { return m_name1; }
    const std::string& GetName2() const { return m_name2; }
    const std::string& GetName3() const { return m_name3; }
    const Wt::Dbo::ptr<tb::models::dbo::Book>& GetBook() const { return m_book; }
    const Wt::Dbo::ptr<tb::models::dbo::Identity>& GetIdentity() const { return m_identity; }

    void SetName1(const std::string& name) { m_name1 = name; }
    void SetName2(const std::string& name) { m_name2 = name; }
    void SetName3(const std::string& name) { m_name3 = name; }
    void SetBook(const Wt::Dbo::ptr<tb::models::dbo::Book>& book) { m_book = book; }
    void SetIdentity(const Wt::Dbo::ptr<tb::models::dbo::Identity>& identity) { m_identity = identity; }

private:

    std::string m_name1;
    std::string m_name2;
    std::string m_name3;
    Wt::Dbo::ptr<tb::models::dbo::Book> m_book;
    Wt::Dbo::ptr<tb::models::dbo::Identity> m_identity;
}; // cl Partner

/*
    Table: account -> Account are entities which the user uses to make transactions.

    |  Column Name  |   SQL Type  |                 C++ Type                |        C++ Field        |                       Notes                      |
    |:-------------:|:-----------:|:---------------------------------------:|:-----------------------:|:------------------------------------------------:|
    |      guid     |     UUID    |               std::string               |    BaseEntity::m_guid   | Auto-generated at object creation                |
    |   created_on  | TIMESTAMPTZ |              Wt::WDateTime              | BaseEntity::m_createdOn | Auto filled                                      |
    |   updated_on  | TIMESTAMPTZ |              Wt::WDateTime              | BaseEntity::m_updatedOn | Auto-filled                                      |
    |     name1     |   VARCHAR   |               std::string               |     Account::m_name1    | Name 1 of the Account                            |
    |     name2     |   VARCHAR   |               std::string               |     Account::m_name2    | Name 2 of the Account                            |
    |     name3     |   VARCHAR   |               std::string               |     Account::m_name3    | Name 3 of the Account                            |
    |   book_guid   |     UUID    |   Wt::Dbo::ptr<tb::models::dbo::Book>   |     Partner::m_book     | Foreign key and reference to the Book record     |
    | identity_guid |   VARCHAR   | Wt::Dbo::ptr<tb::models::dbo::Identity> |   Partner::m_identity   | Foreign key and reference to the Identity record |
*/
class Account : public  tb::models::dbo::BaseEntity
{
public:
    Account() = default; 

    template<class Action>
    void persist(Action& action)
    {
        BaseEntity::persist(action);

        Wt::Dbo::field(action, m_name1, "name1");
        Wt::Dbo::field(action, m_name2, "name2");
        Wt::Dbo::field(action, m_name3, "name3");
        Wt::Dbo::belongsTo(action, m_identity, "identity");
        Wt::Dbo::belongsTo(action, m_book, "book");
    }

    const std::string& GetName1() const { return m_name1; }
    const std::string& GetName2() const { return m_name2; }
    const std::string& GetName3() const { return m_name3; }
    const Wt::Dbo::ptr<tb::models::dbo::Book>& GetBook() const { return m_book; }
    const Wt::Dbo::ptr<tb::models::dbo::Identity>& GetIdentity() const { return m_identity; }

    void SetName1(const std::string& name) { m_name1 = name; }
    void SetName2(const std::string& name) { m_name2 = name; }
    void SetName3(const std::string& name) { m_name3 = name; }
    void SetBook(const Wt::Dbo::ptr<tb::models::dbo::Book>& book) { m_book = book; }
    void SetIdentity(const Wt::Dbo::ptr<tb::models::dbo::Identity>& identity) { m_identity = identity; }

private:

    std::string m_name1;
    std::string m_name2;
    std::string m_name3;
    Wt::Dbo::ptr<tb::models::dbo::Book> m_book;
    Wt::Dbo::ptr<tb::models::dbo::Identity> m_identity;
}; // cl Account


// -----------------------------------------------------------------------------
// Operations Types
// -----------------------------------------------------------------------------
/*
    Table: transaction -> Defines the header of a Transaction.

    |  Column Name  |   SQL Type  |                 C++ Type                |          C++ Field         |                           Notes                           |
    |:-------------:|:-----------:|:---------------------------------------:|:--------------------------:|:---------------------------------------------------------:|
    |      guid     |     UUID    |               std::string               |     BaseEntity::m_guid     | Auto-generated at object creation                         |
    |   created_on  | TIMESTAMPTZ |              Wt::WDateTime              |   BaseEntity::m_createdOn  | Auto filled                                               |
    |   updated_on  | TIMESTAMPTZ |              Wt::WDateTime              |   BaseEntity::m_updatedOn  | Auto-filled                                               |
    |  executed_on  | TIMESTAMPTZ |              Wt::WDateTime              |  Transaction::m_executedOn | Timestamp on which the Transaction has occured            |
    |   settled_on  | TIMESTAMPTZ |              Wt::WDateTime              |  Transaction::m_settledOn  | Timestamp on which the Transaction is settled by the Bank |
    |     notes     |   VARCHAR   |               std::string               |    Transaction::m_notes    | Notes                                                     |
    |  description  |   VARCHAR   |               std::string               | Transaction::m_description | Description                                               |
    | currency_guid |     UUID    | Wt::Dbo::ptr<tb::models::dbo::Currency> |   Transaction::m_currency  | Foreign key and reference to the Currency                 |
    |   book_guid   |     UUID    |   Wt::Dbo::ptr<tb::models::dbo::Book>   |     Transaction::m_book    | Foreign key and reference to the Book record              |
    | identity_guid |     UUID    | Wt::Dbo::ptr<tb::models::dbo::Identity> |   Transaction::m_identity  | Foreign key and reference to the Identity record          |
*/
class Transaction : public  tb::models::dbo::BaseEntity
{
public:
    Transaction() = default;

    template<class Action>
    void persist(Action& action)
    {
        BaseEntity::persist(action);

        Wt::Dbo::field(action, m_executedOn, "executed_on");
        Wt::Dbo::field(action, m_settledOn, "settled_on");
        Wt::Dbo::field(action, m_notes, "notes");
        Wt::Dbo::field(action, m_description, "description");
        Wt::Dbo::belongsTo(action, m_currency, "currency");
        Wt::Dbo::belongsTo(action, m_book, "book");
        Wt::Dbo::belongsTo(action, m_identity, "identity");
    }

    const Wt::WDateTime& GetExecutedOn() const { return m_executedOn; }
    const Wt::WDateTime& GetSettledOn() const { return m_settledOn; }
    const std::string& GetNotes() const { return m_notes; }
    const std::string& GetDescription() const { return m_description; }
    const Wt::Dbo::ptr<tb::models::dbo::Currency>& GetCurrency() const { return m_currency; }
    const Wt::Dbo::ptr<tb::models::dbo::Book>& GetBook() const { return m_book; }
    const Wt::Dbo::ptr<tb::models::dbo::Identity>& GetIdentity() const { return m_identity; }

    void SetExecutedOn(const Wt::WDateTime& executedOn) { m_executedOn = executedOn; }
    void SetSettledOn(const Wt::WDateTime& settledOn) { m_settledOn = settledOn; }
    void SetNotes(const std::string& notes) { m_notes = notes; }
    void SetDescription(const std::string& description) { m_description = description; }
    void SetCurrency(const Wt::Dbo::ptr<tb::models::dbo::Currency>& currency) { m_currency = currency; }
    void SetBook(const Wt::Dbo::ptr<tb::models::dbo::Book>& book) { m_book = book; }
    void SetIdentity(const Wt::Dbo::ptr<tb::models::dbo::Identity>& identity) { m_identity = identity; }

private:
    Wt::WDateTime m_executedOn;
    Wt::WDateTime m_settledOn;
    std::string m_notes;
    std::string m_description;
    Wt::Dbo::ptr<tb::models::dbo::Currency> m_currency;
    Wt::Dbo::ptr<tb::models::dbo::Book> m_book;
    Wt::Dbo::ptr<tb::models::dbo::Identity> m_identity;
}; // cl Transaction

/*
    Table: transaction_item -> Defines the Item of a Transaction

    |    Column Name   |   SQL Type  |                  C++ Type                  |          C++ Field         |                                    Notes                                   |
    |:----------------:|:-----------:|:------------------------------------------:|:--------------------------:|:--------------------------------------------------------------------------:|
    |       guid       |     UUID    |                 std::string                |     BaseEntity::m_guid     | Auto-generated at object creation                                          |
    |    created_on    | TIMESTAMPTZ |                Wt::WDateTime               |   BaseEntity::m_createdOn  | Auto filled                                                                |
    |    updated_on    | TIMESTAMPTZ |                Wt::WDateTime               |   BaseEntity::m_updatedOn  | Auto-filled                                                                |
    |    line_number   |   INTEGER   |                std::uint32_t               |  Transaction::m_lineNumber | Item Line Number                                                           |
    |      amount      |   INTEGER   |                std::int64_t                |    Transaction::m_amount   | Amount of the Transaction(Item). =Product*Qty if Product is not specified. |
    |     quantity     |   INTEGER   |                   double                   |   Transaction::m_quantity  | Quanitity involved                                                         |
    |       memo       |   VARCHAR   |                 std::string                |     Transaction::m_memo    | Line specific note                                                         |
    | transaction_guid |     UUID    | Wt::Dbo::ptr<tb::models::dbo::Transaction> | Transaction::m_transaction | Transaction Header Record                                                  |
    |   account_guid   |     UUID    |   Wt::Dbo::ptr<tb::models::dbo::Account>   |   Transaction::m_account   | Account used for the Transaction(Item)                                     |
    |   partner_guid   |     UUID    |   Wt::Dbo::ptr<tb::models::dbo::Partner>   |   Transaction::m_partner   | Partner used for the Transaction(Item)                                     |
    |   product_guid   |     UUID    |   Wt::Dbo::ptr<tb::models::dbo::Product>   |   Transaction::m_product   | Product used for the Transaction(Optional)                                 |
    |   currency_guid  |     UUID    |   Wt::Dbo::ptr<tb::models::dbo::Currency>  |   Transaction::m_currency  | Foreign key and reference to the Currency                                  |
    |     book_guid    |     UUID    |     Wt::Dbo::ptr<tb::models::dbo::Book>    |     Transaction::m_book    | Foreign key and reference to the Book record                               |
    |   identity_guid  |     UUID    |   Wt::Dbo::ptr<tb::models::dbo::Identity>  |   Transaction::m_identity  | Foreign key and reference to the Identity record                           |
*/
class TransactionItem : public  tb::models::dbo::BaseEntity
{
public:
    TransactionItem() = default;

    template<class Action>
    void persist(Action& action)
    {
        tb::models::dbo::BaseEntity::persist(action);

        Wt::Dbo::field(action, m_lineNumber, "line_number");
        Wt::Dbo::field(action, m_amount, "amount");
        Wt::Dbo::field(action, m_quantity, "quantity");
        Wt::Dbo::field(action, m_memo, "memo");
        Wt::Dbo::belongsTo(action, m_transaction, "transaction");
        Wt::Dbo::belongsTo(action, m_account, "account");
        Wt::Dbo::belongsTo(action, m_partner, "partner");
        Wt::Dbo::belongsTo(action, m_product, "product");
        Wt::Dbo::belongsTo(action, m_currency, "currency");
        Wt::Dbo::belongsTo(action, m_book, "book");
        Wt::Dbo::belongsTo(action, m_identity, "identity");
    }

    std::uint32_t GetLineNumber() const { return m_lineNumber; }
    std::int64_t GetAmount() const { return m_amount; }
    double GetQuantity() const { return m_quantity; }
    const std::string& GetMemo() const { return m_memo; }
    const Wt::Dbo::ptr<tb::models::dbo::Transaction>& GetTransaction() const { return m_transaction; }
    const Wt::Dbo::ptr<tb::models::dbo::Account>& GetAccount() const { return m_account; }
    const Wt::Dbo::ptr<tb::models::dbo::Partner>& GetPartner() const { return m_partner; }
    const Wt::Dbo::ptr<tb::models::dbo::Product>& GetProduct() const { return m_product; }
    const Wt::Dbo::ptr<tb::models::dbo::Currency>& GetCurrency() const { return m_currency; }
    const Wt::Dbo::ptr<tb::models::dbo::Book>& GetBook() const { return m_book; }
    const Wt::Dbo::ptr<tb::models::dbo::Identity>& GetIdentity() const { return m_identity; }

    void SetLineNumber(std::uint32_t lineNumber) { m_lineNumber = lineNumber; }
    void SetAmount(std::int64_t amount) { m_amount = amount; }
    void SetQuantity(double quantity) { m_quantity = quantity; }
    void SetMemo(const std::string& memo) { m_memo = memo; }
    void SetTransaction(const Wt::Dbo::ptr<tb::models::dbo::Transaction>& transaction) { m_transaction = transaction; }
    void SetAccount(const Wt::Dbo::ptr<tb::models::dbo::Account>& account) { m_account = account; }
    void SetPartner(const Wt::Dbo::ptr<tb::models::dbo::Partner>& partner) { m_partner = partner; }
    void SetProduct(const Wt::Dbo::ptr<tb::models::dbo::Product>& product) { m_product = product; }
    void SetCurrency(const Wt::Dbo::ptr<tb::models::dbo::Currency>& currency) { m_currency = currency; }
    void SetBook(const Wt::Dbo::ptr<tb::models::dbo::Book>& book) { m_book = book; }
    void SetIdentity(const Wt::Dbo::ptr<tb::models::dbo::Identity>& identity) { m_identity = identity; }

private:
    std::uint32_t m_lineNumber{ 0 };
    std::int64_t m_amount{ 0 };
    double m_quantity{ 0.0 };
    std::string m_memo;
    Wt::Dbo::ptr<tb::models::dbo::Transaction> m_transaction;
    Wt::Dbo::ptr<tb::models::dbo::Account> m_account;
    Wt::Dbo::ptr<tb::models::dbo::Partner> m_partner;
    Wt::Dbo::ptr<tb::models::dbo::Product> m_product;
    Wt::Dbo::ptr<tb::models::dbo::Currency> m_currency;
    Wt::Dbo::ptr<tb::models::dbo::Book> m_book;
    Wt::Dbo::ptr<tb::models::dbo::Identity> m_identity;
}; // cl TransactionItem

/*
    Table: product -> Represents a catalog good, service, subscription, or utility
    that can be referenced by transaction line items.

    |     Column Name      |   SQL Type   |                C++ Type                 |          C++ Field          |                       Notes                        |
    |:--------------------:|:------------:|:---------------------------------------:|:---------------------------:|:--------------------------------------------------:|
    |         guid         |     UUID     |               std::string               |     BaseEntity::m_guid      | Auto-generated at object creation                  |
    |      created_on      | TIMESTAMPTZ  |              Wt::WDateTime              |   BaseEntity::m_createdOn   | Auto-filled                                        |
    |      updated_on      | TIMESTAMPTZ  |              Wt::WDateTime              |   BaseEntity::m_updatedOn   | Auto-filled                                        |
    |         name         | VARCHAR(255) |               std::string               |       Product::m_name       | Product or service name                            |
    |         code         | VARCHAR(64)  |               std::string               |       Product::m_code       | Optional SKU, EAN/barcode, or internal short code  |
    |     description      |     TEXT     |               std::string               |   Product::m_description    | Optional product specs, contract details, or notes |
    |   unit_of_measure    | VARCHAR(32)  |               std::string               |  Product::m_unitOfMeasure   | Unit paired with item quantity (e.g., pcs, kg, L)  |
    |  default_unit_price  |    BIGINT    |                 int64_t                 | Product::m_defaultUnitPrice | Optional reference price in minor units            |
    |       is_group       |   BOOLEAN    |                  bool                   |     Product::m_isGroup      | True if acting as a grouping parent product        |
    |      is_active       |   BOOLEAN    |                  bool                   |     Product::m_isActive     | Soft-archive flag (defaults to true)               |
    |     parent_guid      |     UUID     | Wt::Dbo::ptr<tb::models::dbo::Product>  |      Product::m_parent      | Optional self-reference to parent product family   |
    |    currency_guid     |     UUID     | Wt::Dbo::ptr<tb::models::dbo::Currency> |     Product::m_currency     | Foreign key and reference to the Currency          |
    |    partner_guid      |     UUID     | Wt::Dbo::ptr<tb::models::dbo::Partner>  |     Product::m_partner      | Optional default Partner (vendor/provider)         |
    |      book_guid       |     UUID     |   Wt::Dbo::ptr<tb::models::dbo::Book>   |       Product::m_book       | Foreign key and reference to the Book record       |
    |    identity_guid     |     UUID     | Wt::Dbo::ptr<tb::models::dbo::Identity> |     Product::m_identity     | Foreign key and reference to the Identity record   |
*/
class Product : public  tb::models::dbo::BaseEntity
{
public:
    Product() = default;

    template<class Action>
    void persist(Action& action)
    {
        tb::models::dbo::BaseEntity::persist(action);

        Wt::Dbo::field(action, m_name, "name", 255);
        Wt::Dbo::field(action, m_code, "code", 64);
        Wt::Dbo::field(action, m_description, "description");
        Wt::Dbo::field(action, m_unitOfMeasure, "unit_of_measure", 32);
        Wt::Dbo::field(action, m_defaultUnitPrice, "default_unit_price");
        Wt::Dbo::field(action, m_isGroup, "is_group");
        Wt::Dbo::field(action, m_isActive, "is_active");
        Wt::Dbo::belongsTo(action, m_parent, "parent");
        Wt::Dbo::belongsTo(action, m_currency, "currency");
        Wt::Dbo::belongsTo(action, m_partner, "default_partner");
        Wt::Dbo::belongsTo(action, m_book, "book");
        Wt::Dbo::belongsTo(action, m_identity, "identity");
    }

    const std::string& GetName() const { return m_name; }
    const std::string& GetCode() const { return m_code; }
    const std::string& GetDescription() const { return m_description; }
    const std::string& GetUnitOfMeasure() const { return m_unitOfMeasure; }
    int64_t GetDefaultUnitPrice() const { return m_defaultUnitPrice; }
    bool IsGroup() const { return m_isGroup; }
    bool IsActive() const { return m_isActive; }
    const Wt::Dbo::ptr<tb::models::dbo::Product>& GetParent() const { return m_parent; }
    const Wt::Dbo::ptr<tb::models::dbo::Currency>& GetCurrency() const { return m_currency; }
    const Wt::Dbo::ptr<tb::models::dbo::Partner>& GetPartner() const { return m_partner; }
    const Wt::Dbo::ptr<tb::models::dbo::Book>& GetBook() const { return m_book; }
    const Wt::Dbo::ptr<tb::models::dbo::Identity>& GetIdentity() const { return m_identity; }

    void SetName(const std::string& name) { m_name = name; }
    void SetCode(const std::string& code) { m_code = code; }
    void SetDescription(const std::string& description) { m_description = description; }
    void SetUnitOfMeasure(const std::string& unitOfMeasure) { m_unitOfMeasure = unitOfMeasure; }
    void SetDefaultUnitPrice(int64_t defaultUnitPrice) { m_defaultUnitPrice = defaultUnitPrice; }
    void SetIsGroup(bool isGroup) { m_isGroup = isGroup; }
    void SetIsActive(bool isActive) { m_isActive = isActive; }
    void SetParent(const Wt::Dbo::ptr<tb::models::dbo::Product>& parent) { m_parent = parent; }
    void SetCurrency(const Wt::Dbo::ptr<tb::models::dbo::Currency>& currency) { m_currency = currency; }
    void SetPartner(const Wt::Dbo::ptr<tb::models::dbo::Partner>& partner) { m_partner = partner; }
    void SetBook(const Wt::Dbo::ptr<tb::models::dbo::Book>& book) { m_book = book; }
    void SetIdentity(const Wt::Dbo::ptr<tb::models::dbo::Identity>& identity) { m_identity = identity; }

private:
    std::string m_name;
    std::string m_code;
    std::string m_description;
    std::string m_unitOfMeasure;
    int64_t m_defaultUnitPrice{ 0 };
    bool m_isGroup{ false };
    bool m_isActive{ true };
    Wt::Dbo::ptr<tb::models::dbo::Product> m_parent;
    Wt::Dbo::ptr<tb::models::dbo::Currency> m_currency;
    Wt::Dbo::ptr<tb::models::dbo::Account> m_defaultAccount;
    Wt::Dbo::ptr<tb::models::dbo::Partner> m_partner;
    Wt::Dbo::ptr<tb::models::dbo::Book> m_book;
    Wt::Dbo::ptr<tb::models::dbo::Identity> m_identity;
}; // cl Product

// -----------------------------------------------------------------------------
// Code List Types
// -----------------------------------------------------------------------------

/*
    Table: book_status -> Global code list defining the lifecycle state of a Book
    (e.g., Active, Archived, Closed).

    | Column Name  |  SQL Type   |   C++ Type    |        C++ Field         |                       Notes                         |
    |:------------:|:-----------:|:-------------:|:------------------------:|:---------------------------------------------------:|
    |     guid     |    UUID     |  std::string  |    BaseEntity::m_guid    | Auto-generated at object creation                   |
    |  created_on  | TIMESTAMPTZ | Wt::WDateTime | BaseEntity::m_createdOn  | Auto-filled                                         |
    |  updated_on  | TIMESTAMPTZ | Wt::WDateTime | BaseEntity::m_updatedOn  | Auto-filled                                         |
    |     code     | VARCHAR(32) |  std::string  |    BookStatus::m_code    | Unique system code (e.g., ACTIVE, ARCHIVED, CLOSED) |
    |     name     | VARCHAR(64) |  std::string  |    BookStatus::m_name    | Human-readable display label                        |
    | description  |    TEXT     |  std::string  | BookStatus::m_description| Optional description of status behavior             |
    | is_read_only |   BOOLEAN   |     bool      | BookStatus::m_isReadOnly | True if books in this state block new postings      |
    |  is_active   |   BOOLEAN   |     bool      |  BookStatus::m_isActive  | Soft-disable flag for the code list entry           |
*/
class BookStatus : public tb::models::dbo::BaseEntity
{
public:
    BookStatus() = default;

    template<class Action>
    void persist(Action& action)
    {
        tb::models::dbo::BaseEntity::persist(action);

        Wt::Dbo::field(action, m_code, "code", 32);
        Wt::Dbo::field(action, m_name, "name", 64);
        Wt::Dbo::field(action, m_description, "description");
        Wt::Dbo::field(action, m_isReadOnly, "is_read_only");
        Wt::Dbo::field(action, m_isActive, "is_active");
    }

    const std::string& GetCode() const { return m_code; }
    const std::string& GetName() const { return m_name; }
    const std::string& GetDescription() const { return m_description; }
    bool IsReadOnly() const { return m_isReadOnly; }
    bool IsActive() const { return m_isActive; }

    void SetCode(const std::string& code) { m_code = code; }
    void SetName(const std::string& name) { m_name = name; }
    void SetDescription(const std::string& description) { m_description = description; }
    void SetIsReadOnly(bool isReadOnly) { m_isReadOnly = isReadOnly; }
    void SetIsActive(bool isActive) { m_isActive = isActive; }

private:
    std::string m_code;
    std::string m_name;
    std::string m_description;
    bool m_isReadOnly{ false };
    bool m_isActive{ true };
}; // cl BookStatus

/*
    Table: currency -> Global ISO 4217 currency code list defining formatting
    rules and minor-unit scaling factors for monetary amounts.

    |    Column Name    |  SQL Type   |   C++ Type    |          C++ Field          |                         Notes                          |
    |:-----------------:|:-----------:|:-------------:|:---------------------------:|:------------------------------------------------------:|
    |       guid        |    UUID     |  std::string  |     BaseEntity::m_guid      | Auto-generated at object creation                      |
    |    created_on     | TIMESTAMPTZ | Wt::WDateTime |   BaseEntity::m_createdOn   | Auto-filled                                            |
    |    updated_on     | TIMESTAMPTZ | Wt::WDateTime |   BaseEntity::m_updatedOn   | Auto-filled                                            |
    |       code        | VARCHAR(3)  |  std::string  |      Currency::m_code       | ISO 4217 alphabetic code (e.g., EUR, USD, JPY)         |
    |   numeric_code    | VARCHAR(3)  |  std::string  |   Currency::m_numericCode   | Optional ISO 4217 numeric code (e.g., 978, 840)        |
    |       name        | VARCHAR(64) |  std::string  |      Currency::m_name       | Full currency name (e.g., Euro, US Dollar)             |
    |      symbol       | VARCHAR(8)  |  std::string  |     Currency::m_symbol      | Currency symbol (e.g., €, $, £)                        |
    |  decimal_places   |   INTEGER   |      int      |  Currency::m_decimalPlaces  | Fractional digit count (e.g., 2 for EUR, 0 for JPY)    |
    |   symbol_before   |   BOOLEAN   |     bool      |  Currency::m_symbolBefore   | Formatting position (true: $10.00, false: 10.00 €)     |
    |     is_active     |   BOOLEAN   |     bool      |    Currency::m_isActive     | Enables or hides currency in UI selection lists        |
*/
class Currency : public tb::models::dbo::BaseEntity
{
public:
    Currency() = default;

    template<class Action>
    void persist(Action& action)
    {
        tb::models::dbo::BaseEntity::persist(action);

        Wt::Dbo::field(action, m_code, "code", 3);
        Wt::Dbo::field(action, m_numericCode, "numeric_code", 3);
        Wt::Dbo::field(action, m_name, "name", 64);
        Wt::Dbo::field(action, m_symbol, "symbol", 8);
        Wt::Dbo::field(action, m_decimalPlaces, "decimal_places");
        Wt::Dbo::field(action, m_symbolBefore, "symbol_before");
        Wt::Dbo::field(action, m_isActive, "is_active");
    }

    const std::string& GetCode() const { return m_code; }
    const std::string& GetNumericCode() const { return m_numericCode; }
    const std::string& GetName() const { return m_name; }
    const std::string& GetSymbol() const { return m_symbol; }
    int GetDecimalPlaces() const { return m_decimalPlaces; }
    bool IsSymbolBefore() const { return m_symbolBefore; }
    bool IsActive() const { return m_isActive; }

    void SetCode(const std::string& code) { m_code = code; }
    void SetNumericCode(const std::string& numericCode) { m_numericCode = numericCode; }
    void SetName(const std::string& name) { m_name = name; }
    void SetSymbol(const std::string& symbol) { m_symbol = symbol; }
    void SetDecimalPlaces(int decimalPlaces) { m_decimalPlaces = decimalPlaces; }
    void SetSymbolBefore(bool symbolBefore) { m_symbolBefore = symbolBefore; }
    void SetIsActive(bool isActive) { m_isActive = isActive; }

private:
    std::string m_code;
    std::string m_numericCode;
    std::string m_name;
    std::string m_symbol;
    int m_decimalPlaces{ 2 };
    bool m_symbolBefore{ true };
    bool m_isActive{ true };
}; // cl Currency

/*
    Table: account_type -> Global double-entry account classification code list
    (Asset, Liability, Equity, Income, Expense) with balance polarity metadata.

    |  Column Name   |  SQL Type   |   C++ Type    |          C++ Field           |                           Notes                           |
    |:--------------:|:-----------:|:-------------:|:----------------------------:|:---------------------------------------------------------:|
    |      guid      |    UUID     |  std::string  |      BaseEntity::m_guid      | Auto-generated at object creation                         |
    |   created_on   | TIMESTAMPTZ | Wt::WDateTime |   BaseEntity::m_createdOn    | Auto-filled                                               |
    |   updated_on   | TIMESTAMPTZ | Wt::WDateTime |   BaseEntity::m_updatedOn    | Auto-filled                                               |
    |      code      | VARCHAR(32) |  std::string  |     AccountType::m_code      | Unique code (ASSET, LIABILITY, EQUITY, INCOME, EXPENSE)   |
    |      name      | VARCHAR(64) |  std::string  |     AccountType::m_name      | Human-readable display label                              |
    |  description   |    TEXT     |  std::string  |  AccountType::m_description  | Optional explanation of accounting behavior               |
    |  normal_sign   |   INTEGER   |      int      |  AccountType::m_normalSign   | +1 for Debit-normal (Asset/Expense), -1 for Credit-normal |
    |   is_active    |   BOOLEAN   |     bool      |   AccountType::m_isActive    | Enables or hides account type in UI selection lists       |
*/
class AccountType : public tb::models::dbo::BaseEntity
{
public:
    AccountType() = default;

    template<class Action>
    void persist(Action& action)
    {
        tb::models::dbo::BaseEntity::persist(action);

        Wt::Dbo::field(action, m_code, "code", 32);
        Wt::Dbo::field(action, m_name, "name", 64);
        Wt::Dbo::field(action, m_description, "description");
        Wt::Dbo::field(action, m_normalSign, "normal_sign");
        Wt::Dbo::field(action, m_isActive, "is_active");
    }

    const std::string& GetCode() const { return m_code; }
    const std::string& GetName() const { return m_name; }
    const std::string& GetDescription() const { return m_description; }
    int GetNormalSign() const { return m_normalSign; }
    bool IsActive() const { return m_isActive; }

    void SetCode(const std::string& code) { m_code = code; }
    void SetName(const std::string& name) { m_name = name; }
    void SetDescription(const std::string& description) { m_description = description; }
    void SetNormalSign(int normalSign) { m_normalSign = normalSign; }
    void SetIsActive(bool isActive) { m_isActive = isActive; }

private:
    std::string m_code;
    std::string m_name;
    std::string m_description;
    int m_normalSign{ 1 };
    bool m_isActive{ true };
}; // cl AccountType

} // ns tb::models::dbo

#endif // TB_MODELS_DBO_IDENTITY_HPP