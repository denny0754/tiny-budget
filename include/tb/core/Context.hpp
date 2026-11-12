/*
================================================================================
 CHANGE LOG
================================================================================
 Date       | Author        | Task ID       | Description
------------+---------------+---------------+-----------------------------------
 2026-11-10 | Diego Vaccher | UI-0000006-M  | Visualize Active Books on Side Menu
================================================================================
*/

#ifndef TB_CORE_CONTEXT_HPP
#define TB_CORE_CONTEXT_HPP

#include <tb/models/bdo/Book.hpp>

#include <string>
#include <vector>

namespace tb::core
{

struct SessionContext
{
	std::string IdentityId;

	std::vector<tb::models::bdo::Book> ActiveBooks;
}; // cl SessionContext

} // ns tb::core

#endif