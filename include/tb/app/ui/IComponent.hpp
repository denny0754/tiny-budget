#ifndef TB_APP_UI_ICOMPONENT_HPP
#define TB_APP_UI_ICOMPONENT_HPP

#include <tb/app/ServiceRegistry.hpp>

#include <string>

namespace tb::app::ui
{

// Forward declaration of UIController to make it friend to IComponent
class Controller;

class IComponent
{
public:
	virtual ~IComponent() = default;

	virtual void OnInit() = 0;

	virtual void OnRender() = 0;

	virtual void OnUpdate(double deltaTime = .0f) = 0;

	virtual void OnShutdown() = 0;

	virtual std::string GetComponentId() const = 0;

	const bool ShouldClose() const { return m_isClosed; }

private:
	friend class Controller;

	void BindServiceRegistry(std::shared_ptr<tb::app::ServiceRegistry> reg)
	{
		m_serviceReg = reg;
	}

	std::shared_ptr<tb::app::ServiceRegistry> m_serviceReg;

	bool m_isClosed{ false };

protected:
	const std::shared_ptr<tb::app::ServiceRegistry>& GetServiceRegistry() const
	{
		return m_serviceReg;
	}

	void Close() { m_isClosed = true; }
};

} // ns tb::app::ui

#endif