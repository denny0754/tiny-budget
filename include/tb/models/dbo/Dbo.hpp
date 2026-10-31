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
class BaseEntity;
class Identity;
class PasswordCredential;
class Partner;
class PartnerAddress;
class PartnerCommunication;
class Account;
class FinancialBook;
class Transaction;
class TransactionItem;
class Product;
class CodeList;
class Currency;
} // ns tb::models::dbo

#define TB_WT_DBO_ID_STRING_TRAIT(full_class) namespace Wt::Dbo \
{ \
template<>\
struct dbo_traits<full_class> : public dbo_default_traits\
{\
    using IdType = std::string;\
    static IdType invalidId() { return std::string(); }\
    static const char* surrogateIdField() { return nullptr; }\
};\
}

TB_WT_DBO_ID_STRING_TRAIT(tb::models::dbo::Identity)
TB_WT_DBO_ID_STRING_TRAIT(tb::models::dbo::PasswordCredential)
TB_WT_DBO_ID_STRING_TRAIT(tb::models::dbo::FinancialBook)
TB_WT_DBO_ID_STRING_TRAIT(tb::models::dbo::Partner)
TB_WT_DBO_ID_STRING_TRAIT(tb::models::dbo::PartnerAddress)
TB_WT_DBO_ID_STRING_TRAIT(tb::models::dbo::PartnerCommunication)
TB_WT_DBO_ID_STRING_TRAIT(tb::models::dbo::Account)
TB_WT_DBO_ID_STRING_TRAIT(tb::models::dbo::Transaction)
TB_WT_DBO_ID_STRING_TRAIT(tb::models::dbo::TransactionItem)
TB_WT_DBO_ID_STRING_TRAIT(tb::models::dbo::Product)
TB_WT_DBO_ID_STRING_TRAIT(tb::models::dbo::CodeList)
TB_WT_DBO_ID_STRING_TRAIT(tb::models::dbo::Currency)

namespace tb::models::dbo
{

// -----------------------------------------------------------------------------
// Base Entity
// -----------------------------------------------------------------------------
class BaseEntity
{
public:
    BaseEntity()
    {
        static thread_local boost::uuids::random_generator gen;
        m_id = boost::uuids::to_string(gen());
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

        Wt::Dbo::id(action, m_id, "guid", 36);
        Wt::Dbo::field(action, m_createdOn, "created_on");
        Wt::Dbo::field(action, m_updatedOn, "updated_on");
    }

    inline const std::string& GetId() const { return m_id; }
    inline const Wt::WDateTime& GetCreatedOn() const { return m_createdOn; }
    inline const Wt::WDateTime& GetUpdatedOn() const { return m_updatedOn; }

protected:
    std::string m_id;
    Wt::WDateTime m_createdOn;
    Wt::WDateTime m_updatedOn;
};

// -----------------------------------------------------------------------------
// Identity & Authentication
// -----------------------------------------------------------------------------
class Identity : public BaseEntity
{
public:
    Identity() = default;

    template<class Action>
    void persist(Action& action)
    {
        BaseEntity::persist(action);

        Wt::Dbo::field(action, m_email, "email");
        Wt::Dbo::field(action, m_firstName, "first_name");
        Wt::Dbo::field(action, m_lastName, "last_name");

        Wt::Dbo::hasOne(action, m_passwordCredential, "identity");
        Wt::Dbo::hasMany(action, m_financialBooks, Wt::Dbo::ManyToOne, "identity");
    }

    inline const std::string& GetEmail() const { return m_email; }
    inline const std::string& GetFirstName() const { return m_firstName; }
    inline const std::string& GetLastName() const { return m_lastName; }
    inline Wt::Dbo::weak_ptr<PasswordCredential> GetPasswordCredential() const { return m_passwordCredential; }
    inline Wt::Dbo::collection<Wt::Dbo::ptr<FinancialBook>> GetFinancialBooks() const { return m_financialBooks; }

    inline void SetEmail(const std::string& email) { m_email = email; }
    inline void SetFirstName(const std::string& first_name) { m_firstName = first_name; }
    inline void SetLastName(const std::string& last_name) { m_lastName = last_name; }

private:
    std::string m_email;
    std::string m_firstName;
    std::string m_lastName;

    Wt::Dbo::weak_ptr<PasswordCredential> m_passwordCredential;
    Wt::Dbo::collection< Wt::Dbo::ptr<FinancialBook> > m_financialBooks;
}; // cl Identity

class PasswordCredential : public BaseEntity
{
public:
    PasswordCredential() = default;

    template<class Action>
    void persist(Action& action)
    {
        BaseEntity::persist(action);

        Wt::Dbo::belongsTo(action, m_identity, "identity");
        Wt::Dbo::field(action, m_passwordHash, "password_hash");
        Wt::Dbo::field(action, m_failedAttempts, "failed_attempts");
    }

    inline Wt::Dbo::ptr<Identity> GetIdentity() const { return m_identity; }
    inline const std::string& GetPasswordHash() const { return m_passwordHash; }
    inline int GetFailedAttempts() const { return m_failedAttempts; }

    inline void SetIdentity(const Wt::Dbo::ptr<Identity>& identity) { m_identity = identity; }
    inline void SetPasswordHash(const std::string& password_hash) { m_passwordHash = password_hash; }
    inline void SetFailedAttempts(int failed_attempts) { m_failedAttempts = failed_attempts; }
    inline void IncrementFailedAttempts() { m_failedAttempts++; }
    inline void ResetFailedAttempts() { m_failedAttempts = 0; }

private:
    Wt::Dbo::ptr<Identity> m_identity;
    std::string m_passwordHash;
    int m_failedAttempts{ 0 };
}; // cl PasswordCredential

// -----------------------------------------------------------------------------
// Financial Book
// -----------------------------------------------------------------------------
class FinancialBook : public BaseEntity
{
public:
    FinancialBook() = default;

    template<class Action>
    void persist(Action& action)
    {
        BaseEntity::persist(action);

        Wt::Dbo::belongsTo(action, m_identity, "identity");
        Wt::Dbo::field(action, m_name, "name");
        Wt::Dbo::field(action, m_description, "description");
        Wt::Dbo::belongsTo(action, m_defaultCurrency, "default_currency");

        Wt::Dbo::hasMany(action, m_accounts, Wt::Dbo::ManyToOne, "financial_book");
        Wt::Dbo::hasMany(action, m_transactions, Wt::Dbo::ManyToOne, "financial_book");
        Wt::Dbo::hasMany(action, m_partners, Wt::Dbo::ManyToOne, "financial_book");
    }

    inline Wt::Dbo::ptr<Identity> GetIdentity() const { return m_identity; }
    inline const std::string& GetName() const { return m_name; }
    inline const std::string& GetDescription() const { return m_description; }
    inline Wt::Dbo::collection<Wt::Dbo::ptr<Account>> GetAccounts() const { return m_accounts; }
    inline Wt::Dbo::collection<Wt::Dbo::ptr<Transaction>> GetTransactions() const { return m_transactions; }
    inline Wt::Dbo::collection<Wt::Dbo::ptr<Partner>> GetPartners() const { return m_partners; }
    inline Wt::Dbo::ptr<Currency> GetDefaultCurrency() const { return m_defaultCurrency; }

    inline void SetIdentity(const Wt::Dbo::ptr<Identity>& identity) { m_identity = identity; }
    inline void SetName(const std::string& name) { m_name = name; }
    inline void SetDescription(const std::string& description) { m_description = description; }
    inline void SetDefaultCurrency(const Wt::Dbo::ptr<Currency>& currency) { m_defaultCurrency = currency; }

private:
    Wt::Dbo::ptr<Identity> m_identity;
    std::string m_name;
    std::string m_description;
    Wt::Dbo::ptr<Currency> m_defaultCurrency;

    Wt::Dbo::collection<Wt::Dbo::ptr<Account>> m_accounts;
    Wt::Dbo::collection<Wt::Dbo::ptr<Transaction>> m_transactions;
    Wt::Dbo::collection<Wt::Dbo::ptr<Partner>> m_partners;
}; // cl FinancialBook

// -----------------------------------------------------------------------------
// Account
// -----------------------------------------------------------------------------
class Account : public BaseEntity
{
public:
    Account() = default;

    template<class Action>
    void persist(Action& action)
    {
        BaseEntity::persist(action);

        Wt::Dbo::belongsTo(action, m_book, "financial_book");
        Wt::Dbo::belongsTo(action, m_type, "type_code_id");
        Wt::Dbo::field(action, m_name1, "name1");
        Wt::Dbo::field(action, m_name2, "name2");
        Wt::Dbo::field(action, m_notes, "notes");

        Wt::Dbo::hasMany(action, m_transactionItems, Wt::Dbo::ManyToOne, "account");
    }

    inline Wt::Dbo::ptr<FinancialBook> GetFinancialBook() const { return m_book; }
    inline const std::string& GetName1() const { return m_name1; }
    inline const std::string& GetName2() const { return m_name2; }
    inline Wt::Dbo::ptr<CodeList> GetType() const { return m_type; }
    inline const std::string& GetNotes() const { return m_notes; }
    inline Wt::Dbo::collection<Wt::Dbo::ptr<TransactionItem>> GetTransactionItems() const { return m_transactionItems; }

    inline void SetFinancialBook(const Wt::Dbo::ptr<FinancialBook>& book) { m_book = book; }
    inline void SetName1(const std::string& name1) { m_name1 = name1; }
    inline void SetName2(const std::string& name2) { m_name2 = name2; }
    inline void SetType(const Wt::Dbo::ptr<CodeList>& type) { m_type = type; }
    inline void SetNotes(const std::string& notes) { m_notes = notes; }

private:
    Wt::Dbo::ptr<FinancialBook> m_book;

    std::string m_name1;
    std::string m_name2;

    // CodeList.list_code = "AC0" (Loan, Bank Account, Credit Card, Liability, Asset)
    Wt::Dbo::ptr<CodeList> m_type;

    std::string m_notes;

    Wt::Dbo::collection<Wt::Dbo::ptr<TransactionItem>> m_transactionItems;
}; // cl Account

// -----------------------------------------------------------------------------
// Transaction & TransactionItem
// -----------------------------------------------------------------------------
class Transaction : public BaseEntity
{
public:
    Transaction() = default;

    template<class Action>
    void persist(Action& action)
    {
        BaseEntity::persist(action);

        Wt::Dbo::belongsTo(action, m_book, "financial_book");
        Wt::Dbo::belongsTo(action, m_type, "type_code_id");
        Wt::Dbo::field(action, m_notes, "notes");

        Wt::Dbo::hasMany(action, m_items, Wt::Dbo::ManyToOne, "transaction");
    }

    inline Wt::Dbo::ptr<FinancialBook> GetFinancialBook() const { return m_book; }
    inline Wt::Dbo::ptr<CodeList> GetType() const { return m_type; }
    inline const std::string& GetNotes() const { return m_notes; }
    inline Wt::Dbo::collection<Wt::Dbo::ptr<TransactionItem>> GetItems() const { return m_items; }

    inline void SetFinancialBook(const Wt::Dbo::ptr<FinancialBook>& book) { m_book = book; }
    inline void SetType(const Wt::Dbo::ptr<CodeList>& type) { m_type = type; }
    inline void SetNotes(const std::string& notes) { m_notes = notes; }

private:
    std::string m_notes;

    Wt::Dbo::ptr<FinancialBook> m_book;
    // CodeList.list_code == "T00"
    Wt::Dbo::ptr<CodeList> m_type;

    Wt::Dbo::collection<Wt::Dbo::ptr<TransactionItem>> m_items;
}; // cl Transaction

class TransactionItem : public BaseEntity
{
public:
    TransactionItem() = default;

    template<class Action>
    void persist(Action& action)
    {
        BaseEntity::persist(action);

        Wt::Dbo::belongsTo(action, m_transaction, "transaction");
        Wt::Dbo::belongsTo(action, m_account, "account");
        Wt::Dbo::belongsTo(action, m_businessPartner, "partner");
        Wt::Dbo::field(action, m_shortDescription, "short_description");
        Wt::Dbo::field(action, m_notes, "notes");
        Wt::Dbo::field(action, m_grossValue, "gross_value");
    }

    inline Wt::Dbo::ptr<Transaction> GetTransaction() const { return m_transaction; }
    inline Wt::Dbo::ptr<Account> GetAccount() const { return m_account; }
    inline Wt::Dbo::ptr<Partner> GetBusinessPartner() const { return m_businessPartner; }
    inline const std::string& GetShortDescription() const { return m_shortDescription; }
    inline const std::string& GetNotes() const { return m_notes; }
    inline double GetGrossValue() const { return m_grossValue; }

    inline void SetTransaction(const Wt::Dbo::ptr<Transaction>& transaction) { m_transaction = transaction; }
    inline void SetAccount(const Wt::Dbo::ptr<Account>& account) { m_account = account; }
    inline void SetBusinessPartner(const Wt::Dbo::ptr<Partner>& partner) { m_businessPartner = partner; }
    inline void SetShortDescription(const std::string& short_desc) { m_shortDescription = short_desc; }
    inline void SetNotes(const std::string& notes) { m_notes = notes; }
    inline void SetGrossValue(double gross_value) { m_grossValue = gross_value; }

private:
    std::string m_shortDescription;
    std::string m_notes;

    Wt::Dbo::ptr<Transaction> m_transaction;
    Wt::Dbo::ptr<Account> m_account;
    Wt::Dbo::ptr<Partner> m_businessPartner;

    double m_grossValue{ 0.0 };
}; // cl TransactionItem

// -----------------------------------------------------------------------------
// Partner, PartnerCommunication & PartnerAddress
// -----------------------------------------------------------------------------
class Partner : public BaseEntity
{
public:
    Partner() = default;

    template<class Action>
    void persist(Action& action)
    {
        BaseEntity::persist(action);

        Wt::Dbo::belongsTo(action, m_book, "financial_book");
        Wt::Dbo::belongsTo(action, m_role, "role_code_id");
        Wt::Dbo::field(action, m_name1, "name1");
        Wt::Dbo::field(action, m_name2, "name2");
        Wt::Dbo::field(action, m_notes, "notes");

        Wt::Dbo::hasMany(action, m_communications, Wt::Dbo::ManyToOne, "partner");
        Wt::Dbo::hasMany(action, m_addresses, Wt::Dbo::ManyToOne, "partner");
    }

    inline Wt::Dbo::ptr<FinancialBook> GetFinancialBook() const { return m_book; }
    inline const std::string& GetName1() const { return m_name1; }
    inline const std::string& GetName2() const { return m_name2; }
    inline Wt::Dbo::ptr<CodeList> GetRole() const { return m_role; }
    inline const std::string& GetNotes() const { return m_notes; }
    inline Wt::Dbo::collection<Wt::Dbo::ptr<PartnerCommunication>> GetCommunications() const { return m_communications; }
    inline Wt::Dbo::collection<Wt::Dbo::ptr<PartnerAddress>> GetAddresses() const { return m_addresses; }

    inline void SetFinancialBook(const Wt::Dbo::ptr<FinancialBook>& book) { m_book = book; }
    inline void SetName1(const std::string& name1) { m_name1 = name1; }
    inline void SetName2(const std::string& name2) { m_name2 = name2; }
    inline void SetRole(const Wt::Dbo::ptr<CodeList>& role) { m_role = role; }
    inline void SetNotes(const std::string& notes) { m_notes = notes; }

private:
    Wt::Dbo::ptr<FinancialBook> m_book;

    std::string m_name1;
    std::string m_name2;

    // CodeList.list_code = "PA0" (SYSTEM, Vendor, Customer) 
    Wt::Dbo::ptr<CodeList> m_role;

    std::string m_notes;

    Wt::Dbo::collection<Wt::Dbo::ptr<PartnerCommunication>> m_communications;
    Wt::Dbo::collection<Wt::Dbo::ptr<PartnerAddress>> m_addresses;
}; // cl Partner

class PartnerCommunication : public BaseEntity
{
public:
    PartnerCommunication() = default;

    template<class Action>
    void persist(Action& action)
    {
        BaseEntity::persist(action);

        Wt::Dbo::belongsTo(action, m_partner, "partner");
        Wt::Dbo::belongsTo(action, m_type, "type_code_id");
        Wt::Dbo::field(action, m_value, "value");
        Wt::Dbo::field(action, m_contactPerson, "contact_person");
        Wt::Dbo::field(action, m_isMain, "is_main");
        Wt::Dbo::field(action, m_isActive, "is_active");
    }

    inline Wt::Dbo::ptr<Partner> GetPartner() const { return m_partner; }
    inline Wt::Dbo::ptr<CodeList> GetType() const { return m_type; }
    inline const std::string& GetValue() const { return m_value; }
    inline const std::string& GetContactPerson() const { return m_contactPerson; }
    inline bool IsMain() const { return m_isMain; }
    inline bool IsActive() const { return m_isActive; }

    inline void SetPartner(const Wt::Dbo::ptr<Partner>& partner) { m_partner = partner; }
    inline void SetType(const Wt::Dbo::ptr<CodeList>& type) { m_type = type; }
    inline void SetValue(const std::string& value) { m_value = value; }
    inline void SetContactPerson(const std::string& contact_person) { m_contactPerson = contact_person; }
    inline void SetIsMain(bool is_main) { m_isMain = is_main; }
    inline void SetIsActive(bool is_active) { m_isActive = is_active; }

private:
    Wt::Dbo::ptr<Partner> m_partner;

    // CodeList.list_code == "CM0" (Email, Mobile, Phone, Fax, Website, Support Portal)
    Wt::Dbo::ptr<CodeList> m_type;

    std::string m_value;          // The email, phone number, or URL
    std::string m_contactPerson;  // e.g. "Customer Care", "John Doe"

    bool m_isMain{ false };
    bool m_isActive{ true };
}; // cl PartnerCommunication

class PartnerAddress : public BaseEntity
{
public:
    PartnerAddress() = default;

    template<class Action>
    void persist(Action& action)
    {
        BaseEntity::persist(action);

        Wt::Dbo::belongsTo(action, m_partner, "partner");
        Wt::Dbo::belongsTo(action, m_countryCode, "country_code_id");
        Wt::Dbo::field(action, m_street1, "street1");
        Wt::Dbo::field(action, m_street2, "street2");
        Wt::Dbo::field(action, m_city, "city");
        Wt::Dbo::field(action, m_stateRegion, "state_region");
        Wt::Dbo::field(action, m_postalCode, "postal_code");
        Wt::Dbo::field(action, m_isMain, "is_main");
        Wt::Dbo::field(action, m_isActive, "is_active");
    }

    inline Wt::Dbo::ptr<Partner> GetPartner() const { return m_partner; }
    inline const std::string& GetStreet1() const { return m_street1; }
    inline const std::string& GetStreet2() const { return m_street2; }
    inline const std::string& GetCity() const { return m_city; }
    inline const std::string& GetStateRegion() const { return m_stateRegion; }
    inline const std::string& GetPostalCode() const { return m_postalCode; }
    inline Wt::Dbo::ptr<CodeList> GetCountryCode() const { return m_countryCode; }
    inline bool IsMain() const { return m_isMain; }
    inline bool IsActive() const { return m_isActive; }

    inline void SetPartner(const Wt::Dbo::ptr<Partner>& partner) { m_partner = partner; }
    inline void SetStreet1(const std::string& street1) { m_street1 = street1; }
    inline void SetStreet2(const std::string& street2) { m_street2 = street2; }
    inline void SetCity(const std::string& city) { m_city = city; }
    inline void SetStateRegion(const std::string& state_region) { m_stateRegion = state_region; }
    inline void SetPostalCode(const std::string& postal_code) { m_postalCode = postal_code; }
    inline void SetCountryCode(const Wt::Dbo::ptr<CodeList>& country_code) { m_countryCode = country_code; }
    inline void SetIsMain(bool is_main) { m_isMain = is_main; }
    inline void SetIsActive(bool is_active) { m_isActive = is_active; }

private:
    Wt::Dbo::ptr<Partner> m_partner;

    std::string m_street1;
    std::string m_street2;
    std::string m_city;
    std::string m_stateRegion; // State / Province / Region
    std::string m_postalCode;  // String to allow alphanumeric codes

    // Country Code (CodeList.list_code == "CC0" e.g., "IT", "US", "DE")
    Wt::Dbo::ptr<CodeList> m_countryCode;

    bool m_isMain{ false };
    bool m_isActive{ true };
}; // cl PartnerAddress

// -----------------------------------------------------------------------------
// CodeList & Product
// -----------------------------------------------------------------------------
class CodeList : public BaseEntity
{
public:
    CodeList() = default;

    template<class Action>
    void persist(Action& action)
    {
        BaseEntity::persist(action);

        Wt::Dbo::field(action, m_listCode, "list_code");
        Wt::Dbo::field(action, m_value, "value");
        Wt::Dbo::field(action, m_description, "description");
    }

    inline const std::string& GetListCode() const { return m_listCode; }
    inline const std::string& GetValue() const { return m_value; }
    inline const std::string& GetDescription() const { return m_description; }

    inline void SetListCode(const std::string& list_code) { m_listCode = list_code; }
    inline void SetValue(const std::string& value) { m_value = value; }
    inline void SetDescription(const std::string& description) { m_description = description; }

private:
    std::string m_listCode;
    std::string m_value;
    std::string m_description;
}; // cl CodeList

class Product : public BaseEntity
{
public:
    Product() = default;

    template<class Action>
    void persist(Action& action)
    {
        BaseEntity::persist(action);

        Wt::Dbo::field(action, m_name, "name");
        Wt::Dbo::field(action, m_description, "description");
    }

    inline const std::string& GetName() const { return m_name; }
    inline const std::string& GetDescription() const { return m_description; }

    inline void SetName(const std::string& name) { m_name = name; }
    inline void SetDescription(const std::string& description) { m_description = description; }

private:
    std::string m_name;
    std::string m_description;
}; // cl Product


class Currency : public BaseEntity
{
public:
    Currency() = default;

    inline const std::string& GetName() const { return m_name; }
    inline const std::string& GetLabel() const { return m_label; }
    inline const std::string& GetSymbol() const { return m_symbol; }

    inline void SetName(const std::string& name) { m_name = name; }
    inline void SetLabel(const std::string& label) { m_label = label; }
    inline void SetSymbol(const std::string& symbol) { m_symbol = symbol; }

private:
    std::string m_name;
    std::string m_label;
    std::string m_symbol;
}; // cl Currency

} // ns tb::models::dbo

#endif // TB_MODELS_DBO_IDENTITY_HPP