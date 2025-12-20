#include <engine/layer/RenderLayer.h>
#include <engine/VertexArray.h>
#include <engine/VertexBuffer.h>
#include <engine/VertexBufferLayout.h>
#include <engine/Shader.h>

#include <glad/gl.h>

namespace engine
{

RenderLayer::RenderLayer()
    : Layer("RenderLayer")
{
}

void RenderLayer::onAttach()
{
    m_framebuffer = std::make_shared<Framebuffer>(1280, 720);
}

void RenderLayer::onDetach() {}

void RenderLayer::onUpdate(float) {}

void RenderLayer::onRender()
{
    // ===== 最小测试三角形 =====
    static bool initialized = false;
    static VertexArray vao;
    static Shader shader(ENGINE_ASSET_DIR"shaders/basic.vert", ENGINE_ASSET_DIR"shaders/basic.frag");

    // clang-format off
    static float vertices[] = 
    {   // positions        // colors
         0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    // clang-format on

    static VertexBuffer vbo(vertices, sizeof(vertices));
    static VertexBufferLayout vbl;

    if (!initialized)
    {
        vbl.push<float>(3);
        vbl.push<float>(3);

        vao.addBuffer(vbo, vbl);

        initialized = true;
    }

    // m_framebuffer->bind();
    // glEnable(GL_DEPTH_TEST);
    // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // m_framebuffer->unbind();

    // glDisable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // 绘制三角形
    shader.bind();
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);

}

} // namespace engine
