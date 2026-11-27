#include <tb/tools/Security.hpp>

#include <array>
#include <iostream>
#include <vector>

#include <sodium.h>

namespace tb::tools
{

void Security::Initialize()
{
    static bool initialized = false;
    if (!initialized)
    {
        if (sodium_init() < 0)
        {
            throw std::runtime_error("Fatal: Failed to initialize libsodium environment.");
        }
        initialized = true;
    }
}

std::string Security::HashPassword(const std::string& password)
{
    Initialize();


}

bool Security::VerifyPasswordHash(const std::string& password, const std::string& storedHash)
{
    Initialize();

    if (storedHash.empty())
    {
        return false;
    }

    return (crypto_pwhash_str_verify(
        storedHash.c_str(),
        password.c_str(),
        password.length()
    ) == 0);
}

} // namespace tb::tools