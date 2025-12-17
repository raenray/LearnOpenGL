#include <engine/Application.h>
#include <engine/Window.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <engine/Shader.h>
#include <engine/VertexArray.h>
#include <engine/VertexBuffer.h>
#include <engine/IndexBuffer.h>
#include <engine/Texture.h>
#include <engine/Renderer.h>
#include <engine/Renderer2D.h>
#include <engine/Camera2D.h>
#include <engine/Sprite.h>
#include <engine/TextureAtlas.h>

#include <iostream>

namespace engine
{

Application::Application()
{
    m_window = std::make_unique<Window>(800, 800, "LearnOpenGL Engine");
}

Application::~Application() = default;

void Application::run()
{
    glDisable(GL_BLEND);
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Texture> texture1;
    std::unique_ptr<Texture> texture2;
    try
    {
        shader = std::make_unique<Shader>(ENGINE_ASSET_DIR "shaders/renderer2d.vert", ENGINE_ASSET_DIR "shaders/renderer2d.frag");
        texture1 = std::make_unique<Texture>(ENGINE_ASSET_DIR "textures/test1.png");
        texture2 = std::make_unique<Texture>(ENGINE_ASSET_DIR "textures/test2.png");
    }
    catch (std::exception& e)
    {
        std::cout << "" << e.what() << std::endl;
        return;
    }

    // Texture atlasTex(ENGINE_ASSET_DIR"textures/atlas.png");
    Texture atlasTex(ENGINE_ASSET_DIR "textures/test2.png");
    TextureAtlas atlas(&atlasTex, 288, 176);

    Sprite player{
        atlas.texture(),
        atlas.uvMin(0, 0),
        atlas.uvMax(0, 0, 16, 16),
    };

    Sprite enemy{
        atlas.texture(),
        atlas.uvMin(32, 0),
        atlas.uvMax(32, 0, 16, 16),
    };

    engine::Renderer2D renderer2d(*shader.get());
    renderer2d.init();

    engine::Camera2D camera(-1.0f, 1.0f, -1.0f, 1.0f);

    float lastTime = 0.0f;
    while (!m_window->shouldClose())
    {
        float time = (float)glfwGetTime();
        float deltaTime = time - lastTime;
        lastTime = time;
        glClear(GL_COLOR_BUFFER_BIT);

        shader->bind();
        texture1->bind(0);

        renderer2d.begin(camera);
        // renderer2d.drawQuad({-0.5f, -0.5f}, {0.4f, 0.4f}, {1, 0, 0, 1});
        // renderer2d.drawQuad({-0.5f, -0.5f}, {0.4f, 0.4f});
        // renderer2d.drawQuad({0.5f, 0.5f}, {0.3f, 0.3f}, {0, 1, 0, 1}, texture1.get());
        // renderer2d.drawQuad({0.5f, -0.5f}, {0.3f, 0.3f}, {0, 1, 0, 1}, texture2.get());
        // renderer2d.drawQuad({0.5f, 0.5f}, {0.3f, 0.3f}, {1, 1, 1, 1}, texture1.get());
        // renderer2d.drawQuad({0.5f, -0.5f}, {0.3f, 0.3f}, {1, 1, 1, 1}, texture2.get());

        renderer2d.drawSprite({-0.5f, 0.0f}, {0.5f, 0.5f}, player, {1, 0, 0, 1});
        renderer2d.drawSprite({0.0f, -0.0f}, {0.5f, 0.5f}, enemy, {0, 0, 1, 1});

        renderer2d.end();
        renderer2d.flush();

        m_window->swapBuffers();
        m_window->pollEvents();
    }

    renderer2d.shutdown();
}

} // namespace engine
