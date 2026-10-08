#ifndef TB_APP_MODULES_SESSION_INITIALIZER_HPP
#define TB_APP_MODULES_SESSION_INITIALIZER_HPP

#include <tb/core/mod/Module.hpp>
#include <tb/app/api/APIProvider.hpp>

namespace tb::app::mods
{

enum class SessionMode {
    SelectMode, // Choose Local vs Remote
    SignIn,     // Email & Password form
    SignUp      // Email, Password, First & Last Name form
};

class SessionInitializer : public tb::core::mod::Module
{
public:
    void OnInit() override;

    void OnRender() override;

    void OnUpdate(double deltaTime = .0f) override;

    void OnShutdown() override;

private:
    SessionMode m_mode = SessionMode::SelectMode;
    int m_sessionTypeInt = 0; // 0 = Local, 1 = Remote
    bool m_isSignUpMode = false;

    char m_emailBuf[128] = "";
    char m_passwordBuf[128] = "";
    char m_firstNameBuf[64] = "";
    char m_lastNameBuf[64] = "";

    std::shared_ptr<tb::app::api::ApiProvider> m_apiProvider;
};

} // ns tb::app::mods

#endif