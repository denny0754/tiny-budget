/*
==========================================================================
 CHANGE LOG
==========================================================================
 Date       | Author        | Task ID | Description
------------+---------------+---------+-----------------------------------
 2026-11-20 | Diego Vaccher | TB-14   | Definition of Database Objects Model
==========================================================================
*/

#ifndef TB_CORE_MODELS_DBO_USER_HPP
#define TB_CORE_MODELS_DBO_USER_HPP

#include "Common.hpp"

namespace tb::models::dbo
{

class Book;

class Account;

class Partner;

class Transaction;

class TransactionItem;

class Product;

class BookStatus;

class BookStatusText;

class Currency;

class CurrencyText;

class AccountType;

class AccountTypeText;

class Language;

} // tb::models::dbo

/*
    Note(https://www.webtoolkit.eu/wt/doc/reference/html/structWt_1_1Dbo_1_1dbo__traits.html):
    >> The safe pattern to define traits is before the class definition,
    >> based on a forward declaration. This is necessary since the persist()
    >> function relies on this specialization.
*/
DEF_WT_DBO_STRING_TRAIT(tb::models::dbo::Book);
DEF_WT_DBO_STRING_TRAIT(tb::models::dbo::Account);
DEF_WT_DBO_STRING_TRAIT(tb::models::dbo::Partner);
DEF_WT_DBO_STRING_TRAIT(tb::models::dbo::Transaction);
DEF_WT_DBO_STRING_TRAIT(tb::models::dbo::TransactionItem);
DEF_WT_DBO_STRING_TRAIT(tb::models::dbo::Product);
DEF_WT_DBO_STRING_TRAIT(tb::models::dbo::BookStatus);
DEF_WT_DBO_STRING_TRAIT(tb::models::dbo::BookStatusText);
DEF_WT_DBO_STRING_TRAIT(tb::models::dbo::Currency);
DEF_WT_DBO_STRING_TRAIT(tb::models::dbo::CurrencyText);
DEF_WT_DBO_STRING_TRAIT(tb::models::dbo::AccountType);
DEF_WT_DBO_STRING_TRAIT(tb::models::dbo::AccountTypeText);
DEF_WT_DBO_STRING_TRAIT(tb::models::dbo::Language);

namespace tb::models::dbo
{

class Book : public tb::models::dbo::BaseObject
{
public:
    /**
     * @brief Default constructor.
    */
    Book() = default;

    /**
     * @brief Performs a persistence mapping operation on the Book instance.
     * @tparam Action Wt::Dbo action type.
     * @param action Database persistence action.
     */
    template<class Action>
    void persist(Action& action)
    {
        tb::models::dbo::BaseObject::persist(action);

        Wt::Dbo::field(action, m_name, "name");
        Wt::Dbo::field(action, m_description, "description");
    }

    /**
     * @brief Returns the book's name.
     * @return Const reference to the name string.
     */
    inline const std::string& GetName() const { return m_name; }

    /**
     * @brief Returns the book's description.
     * @return Const reference to the description string.
     */
    inline const std::string& GetDescription() const { return m_description; }

    /**
     * @brief Sets the book's name.
     * @param name Name string to assign.
     */
    void SetName(const std::string& name) { m_name = name; }

    /**
     * @brief Sets the book's description.
     * @param description Description string to assign.
     */
    void SetDescription(const std::string& description) { m_description = description; }

private:

    std::string m_name;

    std::string m_description;

}; // cl Book

class Account : public tb::models::dbo::BaseObject
{
public:

    /**
     * @brief Default constructor.
    */
    Account() = default;

    /**
     * @brief Performs a persistence mapping operation on the Account instance.
     * @tparam Action Wt::Dbo action type.
     * @param action Database persistence action.
     */
    template<class Action>
    void persist(Action& action)
    {
        tb::models::dbo::BaseObject::persist(action);

        Wt::Dbo::field(action, m_name1, "name1");
        Wt::Dbo::field(action, m_name2, "name2");
        Wt::Dbo::field(action, m_name3, "name3");
        Wt::Dbo::belongsTo(action, m_book, "book");
        Wt::Dbo::belongsTo(action, m_type, "type");
    }

    /**
     * @brief Returns the account's primary name.
     * @return Const reference to the primary name string.
     */
    inline const std::string& GetName1() const { return m_name1; }

    /**
     * @brief Returns the account's secondary name.
     * @return Const reference to the secondary name string.
     */
    inline const std::string& GetName2() const { return m_name2; }

    /**
     * @brief Returns the account's tertiary name.
     * @return Const reference to the tertiary name string.
     */
    inline const std::string& GetName3() const { return m_name3; }

    /**
     * @brief Returns a pointer to the associated book.
     * @return Const reference to the DBO pointer referencing the Book entity.
     */
    inline const Wt::Dbo::ptr<tb::models::dbo::Book>& GetBook() const { return m_book; }

    /**
     * @brief Returns a pointer to the associated account type.
     * @return Const reference to the DBO pointer referencing the AccountType entity.
     */
    inline const Wt::Dbo::ptr<tb::models::dbo::AccountType>& GetType() const { return m_type; }

    /**
     * @brief Sets the account's primary name.
     * @param name Primary name string to assign.
     */
    void SetName1(const std::string& name) { m_name1 = name; }

    /**
     * @brief Sets the account's secondary name.
     * @param name Secondary name string to assign.
     */
    void SetName2(const std::string& name) { m_name2 = name; }

    /**
     * @brief Sets the account's tertiary name.
     * @param name Tertiary name string to assign.
     */
    void SetName3(const std::string& name) { m_name3 = name; }

    /**
     * @brief Sets the associated book.
     * @param book DBO pointer referencing the Book entity to assign.
     */
    void SetBook(const Wt::Dbo::ptr<tb::models::dbo::Book>& book) { m_book = book; }

    /**
     * @brief Sets the associated account type.
     * @param type DBO pointer referencing the AccountType entity to assign.
     */
    void SetType(const Wt::Dbo::ptr<tb::models::dbo::AccountType>& type) { m_type = type; }

private:
    std::string m_name1;
    std::string m_name2;
    std::string m_name3;

    Wt::Dbo::ptr<tb::models::dbo::AccountType> m_type;
    Wt::Dbo::ptr<tb::models::dbo::Book> m_book;
};

class Partner : public  tb::models::dbo::BaseObject
{
public:
    /**
         * @brief Default constructor.
         */
    Partner() = default;

    /**
     * @brief Performs a persistence mapping operation on the Partner instance.
     * @tparam Action Wt::Dbo action type.
     * @param action Database persistence action.
     */
    template<class Action>
    void persist(Action& action)
    {
        tb::models::dbo::BaseObject::persist(action);

        Wt::Dbo::field(action, m_name1, "name1");
        Wt::Dbo::field(action, m_name2, "name2");
        Wt::Dbo::field(action, m_name3, "name3");
        Wt::Dbo::belongsTo(action, m_book, "book");
    }

    /**
     * @brief Returns the partner's primary name.
     * @return Const reference to the primary name string.
     */
    inline const std::string& GetName1() const { return m_name1; }

    /**
     * @brief Returns the partner's secondary name.
     * @return Const reference to the secondary name string.
     */
    inline const std::string& GetName2() const { return m_name2; }

    /**
     * @brief Returns the partner's tertiary name.
     * @return Const reference to the tertiary name string.
     */
    inline const std::string& GetName3() const { return m_name3; }

    /**
     * @brief Returns a pointer to the associated book.
     * @return Const reference to the DBO pointer referencing the Book entity.
     */
    inline const Wt::Dbo::ptr<tb::models::dbo::Book>& GetBook() const { return m_book; }

    /**
     * @brief Sets the partner's primary name.
     * @param name Primary name string to assign.
     */
    void SetName1(const std::string& name) { m_name1 = name; }

    /**
     * @brief Sets the partner's secondary name.
     * @param name Secondary name string to assign.
     */
    void SetName2(const std::string& name) { m_name2 = name; }

    /**
     * @brief Sets the partner's tertiary name.
     * @param name Tertiary name string to assign.
     */
    void SetName3(const std::string& name) { m_name3 = name; }

    /**
     * @brief Sets the associated book.
     * @param book DBO pointer referencing the Book entity to assign.
     */
    void SetBook(const Wt::Dbo::ptr<tb::models::dbo::Book>& book) { m_book = book; }

private:

    std::string m_name1;
    std::string m_name2;
    std::string m_name3;
    Wt::Dbo::ptr<tb::models::dbo::Book> m_book;
}; // cl Partner

class Transaction : public tb::models::dbo::BaseObject
{
public:
    /**
     * @brief Default constructor.
    */
    Transaction() = default;

    /**
     * @brief Performs a persistence mapping operation on the Transaction instance.
     * @tparam Action Wt::Dbo action type.
     * @param action Database persistence action.
     */
    template<class Action>
    void persist(Action& action)
    {
        tb::models::dbo::BaseObject::persist(action);

        Wt::Dbo::field(action, m_postedOn, "posted_date");
        Wt::Dbo::field(action, m_recordedAt, "recorded_at");
        Wt::Dbo::field(action, m_description, "description");
        Wt::Dbo::field(action, m_notes, "notes");

        Wt::Dbo::belongsTo(action, m_currency, "currency");
        Wt::Dbo::belongsTo(action, m_book, "book");
    }

    /**
     * @brief Returns the date the transaction was posted.
     * @return Const reference to the posted date.
     */
    inline const Wt::WDate& GetPostedOn() const { return m_postedOn; }

    /**
     * @brief Returns the timestamp when the transaction was recorded.
     * @return Const reference to the recorded date and time.
     */
    inline const Wt::WDateTime& GetRecordedAt() const { return m_recordedAt; }

    /**
     * @brief Returns the transaction's description.
     * @return Const reference to the description string.
     */
    inline const std::string& GetDescription() const { return m_description; }

    /**
     * @brief Returns additional notes associated with the transaction.
     * @return Const reference to the notes string.
     */
    inline const std::string& GetNotes() const { return m_notes; }

    /**
     * @brief Returns a pointer to the associated currency.
     * @return Const reference to the DBO pointer referencing the Currency entity.
     */
    inline const Wt::Dbo::ptr<tb::models::dbo::Currency>& GetCurrency() const { return m_currency; }

    /**
     * @brief Returns a pointer to the associated book.
     * @return Const reference to the DBO pointer referencing the Book entity.
     */
    inline const Wt::Dbo::ptr<tb::models::dbo::Book>& GetBook() const { return m_book; }

    /**
     * @brief Sets the date the transaction was posted.
     * @param posted_on Posted date to assign.
     */
    void SetPostedOn(const Wt::WDate& posted_on) { m_postedOn = posted_on; }

    /**
     * @brief Sets the timestamp when the transaction was recorded.
     * @param recorded_at Recorded date and time to assign.
     */
    void SetRecorded(const Wt::WDateTime& recorded_at) { m_recordedAt = recorded_at; }

    /**
     * @brief Sets the transaction's description.
     * @param description Description string to assign.
     */
    void SetDescription(const std::string& description) { m_description = description; }

    /**
     * @brief Sets additional notes for the transaction.
     * @param notes Notes string to assign.
     */
    void SetNotes(const std::string& notes) { m_notes = notes; }

    /**
     * @brief Sets the associated currency.
     * @param currency DBO pointer referencing the Currency entity to assign.
     */
    void SetCurrency(const Wt::Dbo::ptr<tb::models::dbo::Currency>& currency) { m_currency = currency; }

    /**
     * @brief Sets the associated book.
     * @param book DBO pointer referencing the Book entity to assign.
     */
    void SetBook(const Wt::Dbo::ptr<tb::models::dbo::Book>& book) { m_book = book; }

private:

    Wt::WDate m_postedOn;
    Wt::WDateTime m_recordedAt;

    std::string m_description;
    std::string m_notes;

    Wt::Dbo::ptr<tb::models::dbo::Currency> m_currency;
    Wt::Dbo::ptr<tb::models::dbo::Book> m_book;
}; // cl Transaction

class TransactionItem : public tb::models::dbo::BaseObject
{
public:
    /**
     * @brief Default constructor.
    */
    TransactionItem() = default;

    /**
     * @brief Performs a persistence mapping operation on the TransactionItem instance.
     * @tparam Action Wt::Dbo action type.
     * @param action Database persistence action.
     */
    template<class Action>
    void persist(Action& action)
    {
        tb::models::dbo::BaseObject::persist(action);

        Wt::Dbo::field(action, m_lineNumber, "line_number");
        Wt::Dbo::field(action, m_amount, "amount");
        Wt::Dbo::field(action, m_quantity, "quantity");
        Wt::Dbo::field(action, m_memo, "memo");

        Wt::Dbo::belongsTo(action, m_transaction, "transaction");
        Wt::Dbo::belongsTo(action, m_account, "account");
        Wt::Dbo::belongsTo(action, m_partner, "partner");
        Wt::Dbo::belongsTo(action, m_product, "product");
        Wt::Dbo::belongsTo(action, m_book, "book");
    }

    /**
     * @brief Returns the line number of the transaction item.
     * @return Line number integer.
     */
    inline std::int32_t GetLineNumber() const { return m_lineNumber; }

    /**
     * @brief Returns the monetary amount of the transaction item.
     * @return Monetary amount value.
     */
    inline double GetAmount() const { return m_amount; }

    /**
     * @brief Returns the quantity of the transaction item.
     * @return Quantity value.
     */
    inline double GetQuantity() const { return m_quantity; }

    /**
     * @brief Returns the memo associated with the transaction item.
     * @return Const reference to the memo string.
     */
    inline const std::string& GetMemo() const { return m_memo; }

    /**
     * @brief Returns a pointer to the parent transaction.
     * @return Const reference to the DBO pointer referencing the Transaction entity.
     */
    inline const Wt::Dbo::ptr<tb::models::dbo::Transaction>& GetTransaction() const { return m_transaction; }

    /**
     * @brief Returns a pointer to the associated account.
     * @return Const reference to the DBO pointer referencing the Account entity.
     */
    inline const Wt::Dbo::ptr<tb::models::dbo::Account>& GetAccount() const { return m_account; }

    /**
     * @brief Returns a pointer to the associated partner.
     * @return Const reference to the DBO pointer referencing the Partner entity.
     */
    inline const Wt::Dbo::ptr<tb::models::dbo::Partner>& GetPartner() const { return m_partner; }

    /**
     * @brief Returns a pointer to the associated product.
     * @return Const reference to the DBO pointer referencing the Product entity.
     */
    inline const Wt::Dbo::ptr<tb::models::dbo::Product>& GetProduct() const { return m_product; }

    /**
     * @brief Returns a pointer to the associated book.
     * @return Const reference to the DBO pointer referencing the Book entity.
     */
    inline const Wt::Dbo::ptr<tb::models::dbo::Book>& GetBook() const { return m_book; }

    /**
     * @brief Sets the line number of the transaction item.
     * @param lineNumber Line number integer to assign.
     */
    void SetLineNumber(std::int32_t lineNumber) { m_lineNumber = lineNumber; }

    /**
     * @brief Sets the monetary amount of the transaction item.
     * @param amount Monetary amount value to assign.
     */
    void SetAmount(double amount) { m_amount = amount; }

    /**
     * @brief Sets the quantity of the transaction item.
     * @param quantity Quantity value to assign.
     */
    void SetQuantity(double quantity) { m_quantity = quantity; }

    /**
     * @brief Sets the memo associated with the transaction item.
     * @param memo Memo string to assign.
     */
    void SetMemo(const std::string& memo) { m_memo = memo; }

    /**
     * @brief Sets the parent transaction.
     * @param transaction DBO pointer referencing the Transaction entity to assign.
     */
    void SetTransaction(const Wt::Dbo::ptr<tb::models::dbo::Transaction>& transaction) { m_transaction = transaction; }

    /**
     * @brief Sets the associated account.
     * @param account DBO pointer referencing the Account entity to assign.
     */
    void SetAccount(const Wt::Dbo::ptr<tb::models::dbo::Account>& account) { m_account = account; }

    /**
     * @brief Sets the associated partner.
     * @param partner DBO pointer referencing the Partner entity to assign.
     */
    void SetPartner(const Wt::Dbo::ptr<tb::models::dbo::Partner>& partner) { m_partner = partner; }

    /**
     * @brief Sets the associated product.
     * @param product DBO pointer referencing the Product entity to assign.
     */
    void SetProduct(const Wt::Dbo::ptr<tb::models::dbo::Product>& product) { m_product = product; }

    /**
     * @brief Sets the associated book.
     * @param book DBO pointer referencing the Book entity to assign.
     */
    void SetBook(const Wt::Dbo::ptr<tb::models::dbo::Book>& book) { m_book = book; }

private:

    std::int32_t m_lineNumber;
    double m_amount;
    double m_quantity;
    std::string m_memo;

    Wt::Dbo::ptr<tb::models::dbo::Transaction> m_transaction;
    Wt::Dbo::ptr<tb::models::dbo::Account> m_account;
    Wt::Dbo::ptr<tb::models::dbo::Partner> m_partner;
    Wt::Dbo::ptr<tb::models::dbo::Product> m_product;
    Wt::Dbo::ptr<tb::models::dbo::Book> m_book;
}; // cl TransactionItem

class Product : public tb::models::dbo::BaseObject
{
public:
    /**
     * @brief Default constructor.
    */
    Product() = default;

    /**
     * @brief Performs a persistence mapping operation on the Product instance.
     * @tparam Action Wt::Dbo action type.
     * @param action Database persistence action.
     */
    template<class Action>
    void persist(Action& action)
    {
        tb::models::dbo::BaseObject::persist(action);

        Wt::Dbo::field(action, m_name, "name");
        Wt::Dbo::field(action, m_description, "description");
        Wt::Dbo::field(action, m_depth, "depth_level");
        Wt::Dbo::field(action, m_isLeaf, "is_leaf");
        Wt::Dbo::field(action, m_validFrom, "valid_from");
        Wt::Dbo::field(action, m_validTo, "valid_to");
        Wt::Dbo::field(action, m_price, "price");

        Wt::Dbo::belongsTo(action, m_parent, "parent");
        Wt::Dbo::belongsTo(action, m_replacedBy, "replaced_by");
        Wt::Dbo::belongsTo(action, m_currency, "currency");
        Wt::Dbo::belongsTo(action, m_partner, "partner");
        Wt::Dbo::belongsTo(action, m_book, "book");
    }

    /**
     * @brief Returns the product's name.
     * @return Const reference to the name string.
     */
    inline const std::string& GetName() const { return m_name; }

    /**
     * @brief Returns the product's description.
     * @return Const reference to the description string.
     */
    inline const std::string& GetDescription() const { return m_description; }

    /**
     * @brief Returns a pointer to the parent product in the hierarchy.
     * @return Const reference to the DBO pointer referencing the parent Product entity.
     */
    inline const Wt::Dbo::ptr<tb::models::dbo::Product>& GetParent() const { return m_parent; }

    /**
     * @brief Returns the depth level of the product in the hierarchy.
     * @return Hierarchy depth integer.
     */
    inline std::int32_t GetDepth() const { return m_depth; }

    /**
     * @brief Checks whether the product is a leaf node in the hierarchy.
     * @return True if the product has no child products, false otherwise.
     */
    inline bool IsLeaf() const { return m_isLeaf; }

    /**
     * @brief Returns a pointer to the superseding replacement product.
     * @return Const reference to the DBO pointer referencing the replacement Product entity.
     */
    inline const Wt::Dbo::ptr<tb::models::dbo::Product>& GetReplacedBy() const { return m_replacedBy; }

    /**
     * @brief Returns the start timestamp of the product's validity period.
     * @return Const reference to the validity start date and time.
     */
    inline const Wt::WDateTime& GetValidFrom() const { return m_validFrom; }

    /**
     * @brief Returns the end timestamp of the product's validity period.
     * @return Const reference to the validity end date and time.
     */
    inline const Wt::WDateTime& GetValidTo() const { return m_validTo; }

    /**
     * @brief Returns the unit price of the product.
     * @return Monetary price value.
     */
    inline double GetPrice() const { return m_price; }

    /**
     * @brief Returns a pointer to the associated currency.
     * @return Const reference to the DBO pointer referencing the Currency entity.
     */
    inline const Wt::Dbo::ptr<tb::models::dbo::Currency>& GetCurrency() const { return m_currency; }

    /**
     * @brief Returns a pointer to the associated partner.
     * @return Const reference to the DBO pointer referencing the Partner entity.
     */
    inline const Wt::Dbo::ptr<tb::models::dbo::Partner>& GetPartner() const { return m_partner; }

    /**
     * @brief Returns a pointer to the associated book.
     * @return Const reference to the DBO pointer referencing the Book entity.
     */
    inline const Wt::Dbo::ptr<tb::models::dbo::Book>& GetBook() const { return m_book; }

    /**
     * @brief Sets the product's name.
     * @param name Name string to assign.
     */
    void SetName(const std::string& name) { m_name = name; }

    /**
     * @brief Sets the product's description.
     * @param description Description string to assign.
     */
    void SetDescription(const std::string& description) { m_description = description; }

    /**
     * @brief Sets the parent product in the hierarchy.
     * @param parent DBO pointer referencing the parent Product entity to assign.
     */
    void SetParent(const Wt::Dbo::ptr<tb::models::dbo::Product>& parent) { m_parent = parent; }

    /**
     * @brief Sets the depth level of the product in the hierarchy.
     * @param depth Hierarchy depth integer to assign.
     */
    void SetDepth(std::int32_t depth) { m_depth = depth; }

    /**
     * @brief Sets whether the product is a leaf node in the hierarchy.
     * @param is_leaf Boolean flag indicating leaf status.
     */
    void MarkAsLeaf(bool is_leaf) { m_isLeaf = is_leaf; }

    /**
     * @brief Sets the superseding replacement product.
     * @param product DBO pointer referencing the replacement Product entity to assign.
     */
    void SetReplaceBy(const Wt::Dbo::ptr<tb::models::dbo::Product>& product) { m_replacedBy = product; }

    /**
     * @brief Sets the start timestamp of the product's validity period.
     * @param valid_from Validity start date and time to assign.
     */
    void SetValidFrom(const Wt::WDateTime& valid_from) { m_validFrom = valid_from; }

    /**
     * @brief Sets the end timestamp of the product's validity period.
     * @param valid_to Validity end date and time to assign.
     */
    void SetValidTo(const Wt::WDateTime& valid_to) { m_validTo = valid_to; }

    /**
     * @brief Sets the unit price of the product.
     * @param price Monetary price value to assign.
     */
    void SetPrice(double price) { m_price = price; }

    /**
     * @brief Sets the associated currency.
     * @param currency DBO pointer referencing the Currency entity to assign.
     */
    void SetCurrency(const Wt::Dbo::ptr<tb::models::dbo::Currency>& currency) { m_currency = currency; }

    /**
     * @brief Sets the associated partner.
     * @param partner DBO pointer referencing the Partner entity to assign.
     */
    void SetPartner(const Wt::Dbo::ptr<tb::models::dbo::Partner>& partner) { m_partner = partner; }

    /**
     * @brief Sets the associated book.
     * @param book DBO pointer referencing the Book entity to assign.
     */
    void SetBook(const Wt::Dbo::ptr<tb::models::dbo::Book>& book) { m_book = book; }

private:

    std::string m_name;
    std::string m_description;

    Wt::Dbo::ptr<tb::models::dbo::Product> m_parent;
    std::int32_t m_depth;
    bool m_isLeaf;

    Wt::Dbo::ptr<tb::models::dbo::Product> m_replacedBy;

    Wt::WDateTime m_validFrom;
    Wt::WDateTime m_validTo;

    double m_price;

    Wt::Dbo::ptr<tb::models::dbo::Currency> m_currency;
    Wt::Dbo::ptr<tb::models::dbo::Partner> m_partner;
    Wt::Dbo::ptr<tb::models::dbo::Book> m_book;
}; // cl Product

class BookStatusText : public tb::models::dbo::BaseObject
{
public:
    /**
     * @brief Default constructor.
    */
    BookStatusText() = default;

    /**
     * @brief Performs a persistence mapping operation on the BookStatusText instance.
     * @tparam Action Wt::Dbo action type.
     * @param action Database persistence action.
     */
    template<class Action>
    void persist(Action& action)
    {
        tb::models::dbo::BaseObject::persist(action);

        Wt::Dbo::field(action, m_languageIsoCode, "language_iso_code");
        Wt::Dbo::field(action, m_label, "label");
        Wt::Dbo::field(action, m_description, "description");

        Wt::Dbo::belongsTo(action, m_bookStatus, "book_status");
    }

    /**
     * @brief Returns the ISO language code for this localized text.
     * @return Const reference to the ISO language code string.
     */
    const std::string& GetLanguageIsoCode() const { return m_languageIsoCode; }

    /**
     * @brief Returns the localized display label.
     * @return Const reference to the label string.
     */
    const std::string& GetLabel() const { return m_label; }

    /**
     * @brief Returns the localized description text.
     * @return Const reference to the description string.
     */
    const std::string& GetDescription() const { return m_description; }

    /**
     * @brief Returns a pointer to the associated book status.
     * @return DBO pointer referencing the BookStatus entity.
     */
    const Wt::Dbo::ptr<tb::models::dbo::BookStatus> GetBookStatus() const { return m_bookStatus; }

    /**
     * @brief Sets the ISO language code for this localized text.
     * @param language_code ISO language code string to assign.
     */
    void SetLanguageIsoCode(const std::string& language_code) { m_languageIsoCode = language_code; }

    /**
     * @brief Sets the localized display label.
     * @param label Label string to assign.
     */
    void SetLabel(const std::string& label) { m_label = label; }

    /**
     * @brief Sets the localized description text.
     * @param description Description string to assign.
     */
    void SetDescription(const std::string& description) { m_description = description; }

    /**
     * @brief Sets the associated book status.
     * @param book_status DBO pointer referencing the BookStatus entity to assign.
     */
    void SetBookStatus(const Wt::Dbo::ptr<tb::models::dbo::BookStatus>& book_status) { m_bookStatus = book_status; }

private:

    Wt::Dbo::ptr<tb::models::dbo::BookStatus> m_bookStatus;

    std::string m_languageIsoCode;

    std::string m_label;

    std::string m_description;

}; // cl BookStatusText

class BookStatus : public tb::models::dbo::BaseObject
{
public:
    /**
     * @brief Default constructor.
    */
    BookStatus() = default;

    /**
     * @brief Performs a persistence mapping operation on the BookStatus instance.
     * @tparam Action Wt::Dbo action type.
     * @param action Database persistence action.
     */
    template<class Action>
    void persist(Action& action)
    {
        tb::models::dbo::BaseObject::persist(action);

        Wt::Dbo::field(action, m_code, "code", 4);
        Wt::Dbo::field(action, m_isEnabled, "is_enabled");

        Wt::Dbo::hasMany(action, m_localizedTexts, Wt::Dbo::RelationType::ManyToOne, "book_status");
    }

    /**
     * @brief Returns the status code.
     * @return Const reference to the status code string.
     */
    const std::string& GetCode() const { return m_code; }

    /**
     * @brief Checks whether the book status is currently enabled.
     * @return True if enabled, false otherwise.
     */
    bool IsActive() const { return m_isEnabled; }

    /**
     * @brief Returns the collection of localized text entries for this book status.
     * @return Collection of weak DBO pointers referencing BookStatusText entities.
     */
    const Wt::Dbo::collection<Wt::Dbo::ptr<tb::models::dbo::BookStatusText>> GetLocalizedTexts() const { return m_localizedTexts; }

    /**
     * @brief Finds and returns the localized text entry matching the specified language code.
     * @param language_code ISO language code to look up.
     * @return Weak DBO pointer referencing the matching BookStatusText entity, or an empty pointer if not found.
     */
    const Wt::Dbo::ptr<tb::models::dbo::BookStatusText> GetLocalizeText(const std::string& language_code) const
    {
        auto it = std::find_if(
            m_localizedTexts.begin(),
            m_localizedTexts.end(),
            [&language_code](const Wt::Dbo::ptr<tb::models::dbo::BookStatusText>& text) {
                return text->GetLanguageIsoCode() == language_code;
            }
        );
        
        return (it != m_localizedTexts.end()) ? *it : Wt::Dbo::ptr<tb::models::dbo::BookStatusText>{};
    }

    /**
     * @brief Sets the status code.
     * @param code Status code string to assign.
     */
    void SetCode(const std::string& code) { m_code = code; }

    /**
     * @brief Enables the book status.
     */
    void Enable() { m_isEnabled = true; }

    /**
     * @brief Disables the book status.
     */
    void Disable() { m_isEnabled = false; }

private:

    std::string m_code;
    bool m_isEnabled;

    Wt::Dbo::collection<Wt::Dbo::ptr<tb::models::dbo::BookStatusText>> m_localizedTexts;

}; // cl BookStatus

class CurrencyText : public tb::models::dbo::BaseObject
{
public:
    /**
     * @brief Default constructor.
    */
    CurrencyText() = default;

    /**
     * @brief Performs a persistence mapping operation on the CurrencyText instance.
     * @tparam Action Wt::Dbo action type.
     * @param action Database persistence action.
     */
    template<class Action>
    void persist(Action& action)
    {
        tb::models::dbo::BaseObject::persist(action);

        Wt::Dbo::field(action, m_languageIsoCode, "language_iso_code");
        Wt::Dbo::field(action, m_label, "label");
        Wt::Dbo::belongsTo(action, m_currency, "currency");
    }

    /**
     * @brief Returns the ISO language code for this localized text.
     * @return Const reference to the ISO language code string.
     */
    inline const std::string& GetLanguageIsoCode() const { return m_languageIsoCode; }

    /**
     * @brief Returns the localized currency label.
     * @return Const reference to the label string.
     */
    inline const std::string& GetLabel() const { return m_label; }

    /**
     * @brief Returns a pointer to the associated currency.
     * @return DBO pointer referencing the Currency entity.
     */
    inline const Wt::Dbo::ptr<tb::models::dbo::Currency> GetCurrency() const { return m_currency; }

    /**
     * @brief Sets the ISO language code for this localized text.
     * @param language_code ISO language code string to assign.
     */
    void SetLanguageIsoCode(const std::string& language_code) { m_languageIsoCode = language_code; }

    /**
     * @brief Sets the localized currency label.
     * @param label Label string to assign.
     */
    void SetLabel(const std::string& label) { m_label = label; }

    /**
     * @brief Sets the associated currency.
     * @param currency DBO pointer referencing the Currency entity to assign.
     */
    void SetCurrency(const Wt::Dbo::ptr<tb::models::dbo::Currency>& currency) { m_currency = currency; }

private:

    Wt::Dbo::ptr<tb::models::dbo::Currency> m_currency;

    std::string m_languageIsoCode;

    std::string m_label;

}; // cl CurrencyText

class Currency : public tb::models::dbo::BaseObject
{
public:
    /**
         * @brief Default constructor.
         */
    Currency() = default;

    /**
     * @brief Performs a persistence mapping operation on the Currency instance.
     * @tparam Action Wt::Dbo action type.
     * @param action Database persistence action.
     */
    template<class Action>
    void persist(Action& action)
    {
        tb::models::dbo::BaseObject::persist(action);

        Wt::Dbo::field(action, m_code, "code");
        Wt::Dbo::field(action, m_symbol, "symbol");
        Wt::Dbo::field(action, m_decimalPlaces, "decimal_places");
        Wt::Dbo::hasMany(action, m_localizedTexts, Wt::Dbo::RelationType::ManyToOne, "currency");
    }

    /**
     * @brief Returns the ISO currency code.
     * @return Const reference to the currency code string.
     */
    inline const std::string& GetCode() const { return m_code; }

    /**
     * @brief Returns the currency symbol.
     * @return Const reference to the currency symbol string.
     */
    inline const std::string& GetSymbol() const { return m_symbol; }

    /**
     * @brief Returns the number of decimal places supported by the currency.
     * @return Number of decimal places.
     */
    inline int GetDecimalPlaces() const { return m_decimalPlaces; }

    /**
     * @brief Returns the collection of localized text entries for this currency.
     * @return Collection of weak DBO pointers referencing CurrencyText entities.
     */
    inline const Wt::Dbo::collection<Wt::Dbo::ptr<tb::models::dbo::CurrencyText>> GetLocalizedTexts() const { return m_localizedTexts; }

    /**
     * @brief Finds and returns the localized text entry matching the specified language code.
     * @param language_code ISO language code to look up.
     * @return Weak DBO pointer referencing the matching CurrencyText entity, or an empty pointer if not found.
     */
    inline const Wt::Dbo::ptr<tb::models::dbo::CurrencyText> GetLocalizedText(const std::string& language_code) const
    {
        auto it = std::find_if(
            m_localizedTexts.begin(),
            m_localizedTexts.end(),
            [&language_code](const Wt::Dbo::ptr<tb::models::dbo::CurrencyText>& text) {
                return text->GetLanguageIsoCode() == language_code;
            }
        );

        return (it != m_localizedTexts.end()) ? *it : Wt::Dbo::ptr<tb::models::dbo::CurrencyText>{};
    }

    /**
     * @brief Sets the ISO currency code.
     * @param code Currency code string to assign.
     */
    void SetCode(const std::string& code) { m_code = code; }

    /**
     * @brief Sets the currency symbol.
     * @param symbol Currency symbol string to assign.
     */
    void SetSymbol(const std::string& symbol) { m_symbol = symbol; }

    /**
     * @brief Sets the number of decimal places supported by the currency.
     * @param decimal_places Number of decimal places to assign.
     */
    void SetDecimalPlaces(int decimal_places) { m_decimalPlaces = decimal_places; }

private:

    std::string m_code;

    std::string m_symbol;

    int m_decimalPlaces;

    Wt::Dbo::collection<Wt::Dbo::ptr<tb::models::dbo::CurrencyText>> m_localizedTexts;

}; // cl Currency

class AccountTypeText : public tb::models::dbo::BaseObject
{
public:
    /**
     * @brief Default constructor.
    */
    AccountTypeText() = default;

    /**
     * @brief Performs a persistence mapping operation on the AccountTypeText instance.
     * @tparam Action Wt::Dbo action type.
     * @param action Database persistence action.
     */
    template<class Action>
    void persist(Action& action)
    {
        tb::models::dbo::BaseObject::persist(action);

        Wt::Dbo::field(action, m_languageIsoCode, "language_iso_code");
        Wt::Dbo::field(action, m_label, "label");
        Wt::Dbo::belongsTo(action, m_accountType, "account_type");
    }

    /**
     * @brief Returns the ISO language code for this localized text.
     * @return Const reference to the ISO language code string.
     */
    inline const std::string& GetLanguageIsoCode() const { return m_languageIsoCode; }

    /**
     * @brief Returns the localized account type label.
     * @return Const reference to the label string.
     */
    inline const std::string& GetLabel() const { return m_label; }

    /**
     * @brief Returns a pointer to the associated account type.
     * @return DBO pointer referencing the AccountType entity.
     */
    inline const Wt::Dbo::ptr<tb::models::dbo::AccountType> GetAccountType() const { return m_accountType; }

    /**
     * @brief Sets the ISO language code for this localized text.
     * @param language_code ISO language code string to assign.
     */
    void SetLanguageIsoCode(const std::string& language_code) { m_languageIsoCode = language_code; }

    /**
     * @brief Sets the localized account type label.
     * @param label Label string to assign.
     */
    void SetLabel(const std::string& label) { m_label = label; }

    /**
     * @brief Sets the associated account type.
     * @param account_type DBO pointer referencing the AccountType entity to assign.
     */
    void SetAccountType(const Wt::Dbo::ptr<tb::models::dbo::AccountType>& account_type) { m_accountType = account_type; }

private:
    Wt::Dbo::ptr<tb::models::dbo::AccountType> m_accountType;

    std::string m_languageIsoCode;

    std::string m_label;
}; // cl AccountTypeText

class AccountType : public tb::models::dbo::BaseObject
{
public:
    /**
     * @brief Default constructor.
    */
    AccountType() = default;

    /**
     * @brief Performs a persistence mapping operation on the AccountType instance.
     * @tparam Action Wt::Dbo action type.
     * @param action Database persistence action.
     */
    template<class Action>
    void persist(Action& action)
    {
        tb::models::dbo::BaseObject::persist(action);

        Wt::Dbo::field(action, m_code, "code");
        Wt::Dbo::hasMany(action, m_localizedTexts, Wt::Dbo::RelationType::ManyToOne, "account_type");
    }

    /**
     * @brief Returns the account type code.
     * @return Const reference to the account type code string.
     */
    inline const std::string& GetCode() const { return m_code; }

    /**
     * @brief Returns the collection of localized text entries for this account type.
     * @return Collection of weak DBO pointers referencing AccountTypeText entities.
     */
    inline const Wt::Dbo::collection<Wt::Dbo::ptr<tb::models::dbo::AccountTypeText>> GetLocalizedTexts() const { return m_localizedTexts; }

    /**
     * @brief Finds and returns the localized text entry matching the specified language code.
     * @param language_code ISO language code to look up.
     * @return Weak DBO pointer referencing the matching AccountTypeText entity, or an empty pointer if not found.
     */
    inline const Wt::Dbo::ptr<tb::models::dbo::AccountTypeText> GetLocalizedText(const std::string& language_code) const
    {
        auto it = std::find_if(
            m_localizedTexts.begin(),
            m_localizedTexts.end(),
            [&language_code](const Wt::Dbo::ptr<tb::models::dbo::AccountTypeText>& text) {
                return text->GetLanguageIsoCode() == language_code;
            }
        );

        return (it != m_localizedTexts.end()) ? *it : Wt::Dbo::ptr<tb::models::dbo::AccountTypeText>{};
    }

    /**
     * @brief Sets the account type code.
     * @param code Account type code string to assign.
     */
    void SetCode(const std::string& code) { m_code = code; }

private:
    std::string m_code;

    Wt::Dbo::collection<Wt::Dbo::ptr<tb::models::dbo::AccountTypeText>> m_localizedTexts;
}; // cl AccountType

class Language : public tb::models::dbo::BaseObject
{
public:
    /**
     * @brief Default constructor.
    */
    Language() = default;

    /**
     * @brief Performs a persistence mapping operation on the Language instance.
     * @tparam Action Wt::Dbo action type.
     * @param action Database persistence action.
     */
    template<class Action>
    void persist(Action& action)
    {
        tb::models::dbo::BaseObject::persist(action);

        Wt::Dbo::field(action, m_code, "code");
        Wt::Dbo::field(action, m_englishLabel, "english_label");
        Wt::Dbo::field(action, m_nativeLabel, "native_label");
    }

    /**
     * @brief Returns the language code.
     * @return Const reference to the language code string.
     */
    inline const std::string& GetCode() const { return m_code; }

    /**
     * @brief Returns the English name of the language.
     * @return Const reference to the English label string.
     */
    inline const std::string& GetEnglishLabel() const { return m_englishLabel; }

    /**
     * @brief Returns the native name of the language.
     * @return Const reference to the native label string.
     */
    inline const std::string& GetNativeLabel() const { return m_nativeLabel; }

    /**
     * @brief Sets the language code.
     * @param code Language code string to assign.
     */
    void SetCode(const std::string& code) { m_code = code; }

    /**
     * @brief Sets the English name of the language.
     * @param label English label string to assign.
     */
    void SetEnglishLabel(const std::string& label) { m_englishLabel = label; }

    /**
     * @brief Sets the native name of the language.
     * @param label Native label string to assign.
     */
    void SetNativeLabel(const std::string& label) { m_nativeLabel = label; }

private:
    std::string m_code;

    std::string m_englishLabel;

    std::string m_nativeLabel;

}; // cl Language

} // tb::models::dbo

#endif