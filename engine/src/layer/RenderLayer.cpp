#include <engine/layer/RenderLayer.h>

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
    static unsigned int VAO = 0, VBO = 0;
    static unsigned int shaderProgram = 0;

    if (!initialized)
    {
        // clang-format off
        float vertices[] = 
        {   // positions        // colors
             0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
        };
        // clang-format on
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Shader
        const char* vertSrc = R"(
            #version 460 core
            layout(location=0) in vec3 aPos;
            layout(location=1) in vec3 aColor;
            out vec3 vColor;
            void main(){ vColor = aColor; gl_Position = vec4(aPos,1.0); }
        )";
        const char* fragSrc = R"(
            #version 460 core
            in vec3 vColor;
            out vec4 FragColor;
            void main(){ FragColor = vec4(vColor,1.0); }
        )";

        unsigned int vert = glCreateShader(GL_VERTEX_SHADER);
        unsigned int frag = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(vert, 1, &vertSrc, nullptr);
        glCompileShader(vert);
        glShaderSource(frag, 1, &fragSrc, nullptr);
        glCompileShader(frag);

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vert);
        glAttachShader(shaderProgram, frag);
        glLinkProgram(shaderProgram);
        glDeleteShader(vert);
        glDeleteShader(frag);

        initialized = true;
    }

    // 绑定 FBO
    // m_framebuffer->bind();
    // // glEnable(GL_DEPTH_TEST);
    // glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // // 解绑 FBO
    // m_framebuffer->unbind();

    // glDisable(GL_DEPTH_TEST);
    // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT);
    // // 绘制三角形
    // glUseProgram(shaderProgram);
    // glBindVertexArray(VAO);
    // glDrawArrays(GL_TRIANGLES, 0, 3);

    m_framebuffer->bind();
    glEnable(GL_DEPTH_TEST); // FBO 里开启深度
    glClearColor(1.0f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 绘制你的物体
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    m_framebuffer->unbind(); // 解绑 FBO，返回默认帧缓冲
}

} // namespace engine
