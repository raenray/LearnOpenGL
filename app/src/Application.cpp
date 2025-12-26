#include <print>
#include <Engine/Core/Application.h>
#include <Engine/Core/Log.h>

int main()
{
    spdlog::set_level(spdlog::level::trace);
    std::unique_ptr<Engine::Core::Application> app;
    try
    {
        app = std::make_unique<Engine::Core::Application>();
        app->run();
    }
    catch (const std::runtime_error& e)
    {
        LOG_ERROR("{}", e.what());
    }

}