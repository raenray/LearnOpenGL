#pragma once

#include <memory>

namespace Engine
{

class Window;
class Event;
class Application final
{
public:
    Application();
    ~Application();

    void run();

    void onEvent(Event& e);

private:
    std::unique_ptr<Window> m_window{};
    bool m_running{true};
};

} // namespace Engine
