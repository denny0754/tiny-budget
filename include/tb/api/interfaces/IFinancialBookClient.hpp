#ifndef TB_API_INTERFACES_IFINANCIAL_BOOK_CLIENT_HPP
#define TB_API_INTERFACES_IFINANCIAL_BOOK_CLIENT_HPP

#include <tb/models/dto/FinancialBook.hpp>
#include <tb/models/dto/Common.hpp>

namespace tb::api
{

class IFinancialBookClient
{
public:
	virtual ~IFinancialBookClient() = default;

	virtual void CreateFinancialBook(
		const tb::models::dto::CreateFinancialBookRequest& data,
		tb::models::dto::APICallback<tb::models::dto::CreateFinancialBookResponse> callback
	) = 0;
}; // cl IFinancialBookClient

} // ns tb::api

#endif