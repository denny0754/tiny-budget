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

    // Buffer required by libsodium for stored password strings
    char hashedPasswordBuf[crypto_pwhash_STRBYTES];

    if (crypto_pwhash_str(
        hashedPasswordBuf,
        password.c_str(),
        password.length(),
        crypto_pwhash_OPSLIMIT_MODERATE,
        crypto_pwhash_MEMLIMIT_MODERATE
    ) != 0)
    {
        throw std::runtime_error("Fatal: Out of memory or system error while hashing password.");
    }

    return std::string(hashedPasswordBuf);
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