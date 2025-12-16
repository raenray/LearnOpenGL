#pragma once

#include <memory>

namespace engine
{

class Window;

class Application
{
public:
    Application();
    ~Application();
    void run();

private:
    std::unique_ptr<Window> m_window;
};

} // namespace engine
