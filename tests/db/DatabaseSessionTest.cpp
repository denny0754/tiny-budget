#include <gtest/gtest.h>

#include "core/db/GenericSession.hpp"

#include "core/db/SecuritySession.hpp"
#include "core/db/UserSession.hpp"

#include "core/models/dbo/Security.hpp"
#include "core/models/dbo/User.hpp"

TEST(database, security_session_init)
{
    auto session = std::make_unique<tb::db::SecuritySession>();
    session->Open(":memory:");
    EXPECT_NE(session->Session(), nullptr);
    EXPECT_EQ(session->Session()->tableName<tb::dbo::Identity>(), "identity");
    EXPECT_EQ(session->Session()->tableName<tb::dbo::PasswordCredential>(), "password_credential");
}

TEST(database, user_session_init)
{
    auto session = std::make_unique<tb::db::UserSession>();
    session->Open(":memory:");
    EXPECT_NE(session->Session(), nullptr);
    EXPECT_EQ(session->Session()->tableName<tb::dbo::Book>(), "book");
    EXPECT_EQ(session->Session()->tableName<tb::dbo::Account>(), "account");
    EXPECT_EQ(session->Session()->tableName<tb::dbo::Partner>(), "partner");
    EXPECT_EQ(session->Session()->tableName<tb::dbo::Transaction>(), "transaction");
    EXPECT_EQ(session->Session()->tableName<tb::dbo::TransactionItem>(), "transaction_item");
    EXPECT_EQ(session->Session()->tableName<tb::dbo::Product>(), "product");
    EXPECT_EQ(session->Session()->tableName<tb::dbo::BookStatus>(), "book_status");
    EXPECT_EQ(session->Session()->tableName<tb::dbo::BookStatusText>(), "book_status_text");
    EXPECT_EQ(session->Session()->tableName<tb::dbo::Currency>(), "currency");
    EXPECT_EQ(session->Session()->tableName<tb::dbo::CurrencyText>(), "currency_text");
    EXPECT_EQ(session->Session()->tableName<tb::dbo::AccountType>(), "account_type");
    EXPECT_EQ(session->Session()->tableName<tb::dbo::AccountTypeText>(), "account_type_text");
    EXPECT_EQ(session->Session()->tableName<tb::dbo::Language>(), "language");
}
