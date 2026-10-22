#ifndef TB_APP_UI_FINANCIAL_BOOK_SETUP_HPP
#define TB_APP_UI_FINANCIAL_BOOK_SETUP_HPP

#include <tb/app/ui/LocalComponent.hpp>

namespace tb::app::ui
{

class FinancialBookSetup : public tb::app::ui::LocalComponent
{
public:
	void OnInit() override;

	void OnRender() override;

	void OnUpdate(double deltaTime = .0f) override;

	void OnShutdown() override;

	std::string GetComponentId() const { return "FinancialBookSetup"; }

private:
	char m_nameBuffer[128] = "";
	char m_descBuffer[256] = "";
	int m_selectedCurrencyIdx = 0; // Default: 0 (EUR)
	bool m_createDefaultAccounts = true;
	std::string m_errorMessage;
};

} // ns tb::app::ui

#endif