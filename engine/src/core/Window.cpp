#include <Engine/Core/Window.h>
#include <Engine/Core/Log.h>
#include <Engine/Event/ApplicationEvent.h>
#include <Engine/Event/KeyEvent.h>
#include <Engine/Event/MouseEvent.h>

#include <glad/gl.h>
#include <glfw/glfw3.h>

#include <stdexcept>

namespace Engine
{

Window::Window(std::string title, int width, int height)
    : m_title(title)
    , m_width(width)
    , m_height(height)
{
    createWindow();
    glfwMakeContextCurrent(m_Window);

    setCallback();

    if (!gladLoadGL(glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glfwSetWindowUserPointer(m_Window, &m_Data);
    // Ensure correct pixel row alignment for texture uploads (e.g. RGB images with 3 bytes per pixel)
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glViewport(0, 0, m_width, m_height);
}

Window::~Window()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(m_Window);
};

void Window::createWindow()
{
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    m_Window = window;
}

void Window::onUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}

void Window::setCallback()
{
    // glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
    //     WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

    //     WindowResizeEvent event(width, height);
    //     data.EventCallback(event);
    // });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        WindowCloseEvent event;
        data.EventCallback(event);
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        LOG_CORE_DEBUG("key {} is action {}", key, action);

        // switch (action)
        // {
        // case GLFW_PRESS: {
        //     KeyPressedEvent event(key, false);
        //     data.EventCallback(event);
        //     break;
        // }
        // case GLFW_RELEASE: {
        //     KeyReleasedEvent event(key);
        //     data.EventCallback(event);
        //     break;
        // }
        // case GLFW_REPEAT: {
        //     KeyPressedEvent event(key, true);
        //     data.EventCallback(event);
        //     break;
        // }
        // }
    });

    // glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
    //     WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

    //     if (action == GLFW_PRESS)
    //     {
    //         MouseButtonPressedEvent event(button);
    //         data.EventCallback(event);
    //     }
    //     else if (action == GLFW_RELEASE)
    //     {
    //         MouseButtonReleasedEvent event(button);
    //         data.EventCallback(event);
    //     }
    // });

    // glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y) {
    //     WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

    //     MouseMovedEvent event((float)x, (float)y);
    //     data.EventCallback(event);
    // });
    // glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
    //     WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

    //     MouseScrolledEvent event((float)xOffset, (float)yOffset);
    //     data.EventCallback(event);
    // });
}

} // namespace Engine
