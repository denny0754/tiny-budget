#include <gtest/gtest.h>

#include "core/db/GenericSession.hpp"

#include "core/db/SecuritySession.hpp"
#include "core/db/UserSession.hpp"

#include "core/models/dbo/Security.hpp"
#include "core/models/dbo/User.hpp"

TEST(database, security_session_init)
{
    auto session = std::make_unique<tb::core::db::SecuritySession>();
    session->Open(":memory:");
    EXPECT_NE(session->Session(), nullptr);
    EXPECT_EQ(session->Session()->tableName<tb::models::dbo::Identity>(), "identity");
    EXPECT_EQ(session->Session()->tableName<tb::models::dbo::PasswordCredential>(), "password_credential");
}

TEST(database, user_session_init)
{
    auto session = std::make_unique<tb::core::db::UserSession>();
    session->Open(":memory:");
    EXPECT_NE(session->Session(), nullptr);
    EXPECT_EQ(session->Session()->tableName<tb::models::dbo::Book>(), "book");
    EXPECT_EQ(session->Session()->tableName<tb::models::dbo::Account>(), "account");
    EXPECT_EQ(session->Session()->tableName<tb::models::dbo::Partner>(), "partner");
    EXPECT_EQ(session->Session()->tableName<tb::models::dbo::Transaction>(), "transaction");
    EXPECT_EQ(session->Session()->tableName<tb::models::dbo::TransactionItem>(), "transaction_item");
    EXPECT_EQ(session->Session()->tableName<tb::models::dbo::Product>(), "product");
    EXPECT_EQ(session->Session()->tableName<tb::models::dbo::BookStatus>(), "book_status");
    EXPECT_EQ(session->Session()->tableName<tb::models::dbo::BookStatusText>(), "book_status_text");
    EXPECT_EQ(session->Session()->tableName<tb::models::dbo::Currency>(), "currency");
    EXPECT_EQ(session->Session()->tableName<tb::models::dbo::CurrencyText>(), "currency_text");
    EXPECT_EQ(session->Session()->tableName<tb::models::dbo::AccountType>(), "account_type");
    EXPECT_EQ(session->Session()->tableName<tb::models::dbo::AccountTypeText>(), "account_type_text");
    EXPECT_EQ(session->Session()->tableName<tb::models::dbo::Language>(), "language");
}
