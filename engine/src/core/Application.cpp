#include <Engine/Core/Application.h>

#include <Engine/Event/Event.h>
#include <Engine/Event/ApplicationEvent.h>
#include <Engine/Core/Window.h>

#include <Engine/Core/Log.h>

namespace Engine
{

Application::Application()
{
    try
    {
        auto window = std::make_unique<Window>("LearnOpenGL", 800, 600);
        m_window    = std::move(window);
    }
    catch (const std::runtime_error& e)
    {
        LOG_ERROR("{}", e.what());
        throw e;
    }
}

Application::~Application() {}

void Application::run()
{
    while (1)
    {
        m_window->onUpdate();
    }
}

void Application::onEvent(Event& e)
{
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<WindowCloseEvent>([this](){
        m_running = false;
        return true;
    });
    // dispatcher.dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(Application::OnWindowResize));
}
} // namespace Engine
