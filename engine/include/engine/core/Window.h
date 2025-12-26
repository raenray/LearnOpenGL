#pragma once

#include <Engine/Event/Event.h>

#include <string>
#include <functional>

struct GLFWwindow;

namespace Engine
{

class Window final
{
public:
    Window(std::string title, int width, int height);
    ~Window();

    bool shouldClose() const;
    void onUpdate();

    int getWidth() const noexcept { return m_width; }
    int getHeight() const noexcept { return m_height; }

    const GLFWwindow* getHandle() const noexcept { return m_Window; }

private:
    void createWindow();
    void setCallback();

private:
    std::string m_title;
    int         m_width{};
    int         m_height{};

    struct WindowData
    {
        std::string                 title;
        int                         width;
        int                         height;
        std::function<void(Event&)> EventCallback;
    };

    WindowData  m_Data;
    GLFWwindow* m_Window{};
};

} // namespace Engine
