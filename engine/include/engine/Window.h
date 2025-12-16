#pragma once

#include <string>

struct GLFWwindow;

namespace engine
{

class Window
{
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    void pollEvents() const;
    void swapBuffers() const;

    bool shouldClose() const;
    GLFWwindow* nativeHandle() const { return m_window; }

private:
    void initGLFW();
    void createWindow();
    void initGlad();
    void setupCallbacks();

private:
    int m_width{};
    int m_height{};
    std::string m_title;

    GLFWwindow* m_window{nullptr};
};

} // namespace engine
