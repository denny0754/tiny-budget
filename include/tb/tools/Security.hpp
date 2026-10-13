#ifndef TB_TOOLS_SECURITY_HPP
#define TB_TOOLS_SECURITY_HPP

#include <string>
#include <utility>

namespace tb::tools
{

class Security
{
public:

	static std::string HashPassword(const std::string& password);

	static bool VerifyPasswordHash(const std::string& password, const std::string& hash);

private:
	static void Initialize();
};

};

#endif