#ifndef TB_APP_MODS_SESSION_MODULE
#define TB_APP_MODS_SESSION_MODULE

#include <tb/core/mod/Module.hpp>

#include <atomic>

namespace tb::app::mods
{

class LocalSessionModule : public tb::core::mod::Module
{
public:
    void OnInit() override;

    void OnRender() override;

    void OnUpdate(double deltaTime = .0f) override;

    void OnShutdown() override;

private:
    void RenderSignUpForm();

    void RenderSignInForm();

private:
    struct AuthSession {
        std::string IdentityId;

        std::string Email;

        std::string FirstName;

        std::string LastName;

        std::atomic<bool> IsAuthenticated;
    };

    AuthSession m_sessionData;

    struct UIData {
        bool signUpBtnPressed{ false };
        bool signInBtnPressed{ false };
    };

    UIData m_uiData;
};

} // ns tb::app::mods

#endif