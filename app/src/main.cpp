#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>

const int WINDOW_W = 1280;
const int WINDOW_H = 720;

// const int PIXEL_W = 320;
// const int PIXEL_H = 180;
const int PIXEL_W = 1280;
const int PIXEL_H = 720;

struct Color
{
    unsigned char r, g, b, a;
};

enum Material
{
    MAT_EMPTY = 0,
    MAT_SAND  = 1,
    MAT_WATER = 2,
    MAT_OIL   = 3,
};

std::vector<Color>    g_color(PIXEL_W* PIXEL_H);
std::vector<Material> g_type(PIXEL_W* PIXEL_H);

const char* vertexShaderSrc = R"(
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aUV;
out vec2 vUV;
void main() {
    vUV = aUV;
    gl_Position = vec4(aPos, 0.0, 1.0);
}
)";

const char* fragmentShaderSrc = R"(
#version 330 core
in vec2 vUV;
out vec4 FragColor;
uniform sampler2D uTex;
void main() {
    FragColor = texture(uTex, vUV);
}
)";

GLuint CompileShader(GLenum type, const char* src)
{
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, nullptr);
    glCompileShader(s);

    int ok;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok)
    {
        char log[512];
        glGetShaderInfoLog(s, 512, nullptr, log);
        std::cerr << log << std::endl;
    }
    return s;
}

GLuint CreateProgram()
{
    GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShaderSrc);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glLinkProgram(prog);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return prog;
}

void ClearPixels()
{
    for (int i = 0; i < PIXEL_W * PIXEL_H; i++)
    {
        g_color[i] = {0, 0, 0, 255};
        g_type[i]  = MAT_EMPTY;
    }
}
inline int Idx(int x, int y)
{
    return y * PIXEL_W + x;
}
void SpawnWater(int x, int y)
{
    g_type[Idx(x, y)]  = MAT_WATER;
    g_color[Idx(x, y)] = {50, 100, 220, 200};
}

void SpawnOil(int x, int y)
{
    g_type[Idx(x, y)]  = MAT_OIL;
    g_color[Idx(x, y)] = {120, 80, 30, 200};
}

inline void SwapCell(int x0, int y0, int x1, int y1)
{
    int a = Idx(x0, y0);
    int b = Idx(x1, y1);
    std::swap(g_type[a], g_type[b]);
    std::swap(g_color[a], g_color[b]);
}

inline bool InBounds(int x, int y)
{
    return x >= 0 && x < PIXEL_W && y >= 0 && y < PIXEL_H;
}

inline bool IsEmpty(int x, int y)
{
    return InBounds(x, y) && g_type[Idx(x, y)] == MAT_EMPTY;
}

inline bool CanSwap(int x, int y, int nx, int ny)
{
    int a = g_type[Idx(x, y)];
    int b = g_type[Idx(nx, ny)];

    // 密度规则：沙 > 水 > 油 > 空
    static int density[] = {0, 3, 2, 1};
    return density[a] > density[b];
}

bool TryMove(int x, int y, int nx, int ny)
{
    if (!InBounds(nx, ny))
        return false;
    if (!CanSwap(x, y, nx, ny))
        return false;

    SwapCell(x, y, nx, ny);
    return true;
}
void TryFall(int x, int y, int slope)
{
    if (TryMove(x, y, x, y - 1))
        return;

    int dir = rand() & 1 ? -1 : 1;
    TryMove(x, y, x + dir, y - 1);
}

void SpawnSand(int px, int py)
{
    if (px < 0 || px >= PIXEL_W || py < 0 || py >= PIXEL_H)
        return;

    g_color[py * PIXEL_W + px] = {220, 200, 50, 255};
    g_type[py * PIXEL_W + px]  = MAT_SAND;
}
inline void MoveSand(int x0, int y0, int x1, int y1)
{
    int a = y0 * PIXEL_W + x0;
    int b = y1 * PIXEL_W + x1;
    std::swap(g_type[a], g_type[b]);
    std::swap(g_color[a], g_color[b]);
}

void UpdateSandAt(int x, int y)
{
    int i = y * PIXEL_W + x;
    if (g_type[i] != 1)
        return;

    int down = (y - 1) * PIXEL_W + x;

    // 1. 正下
    if (g_type[down] == 0)
    {
        std::swap(g_type[i], g_type[down]);
        std::swap(g_color[i], g_color[down]);
        return;
    }

    bool canLeft  = (x > 0) && (g_type[(y - 1) * PIXEL_W + (x - 1)] == 0);
    bool canRight = (x < PIXEL_W - 1) && (g_type[(y - 1) * PIXEL_W + (x + 1)] == 0);

    // 2. 左右滑
    if (canLeft && canRight)
    {
        if (rand() & 1)
            MoveSand(x, y, x - 1, y - 1);
        else
            MoveSand(x, y, x + 1, y - 1);
    }
    else if (canLeft)
    {
        MoveSand(x, y, x - 1, y - 1);
    }
    else if (canRight)
    {
        MoveSand(x, y, x + 1, y - 1);
    }
}

void UpdateSand(int x, int y)
{
    TryFall(x, y, 1);
}

void UpdateWater(int x, int y)
{
    // 1. 下
    if (TryMove(x, y, x, y - 1))
        return;

    // 2. 斜下
    int dir = rand() & 1 ? -1 : 1;
    if (TryMove(x, y, x + dir, y - 1))
        return;
    if (TryMove(x, y, x - dir, y - 1))
        return;

    // 3. 横向流动
    if (TryMove(x, y, x + dir, y))
        return;
    if (TryMove(x, y, x - dir, y))
        return;
}

void UpdateOil(int x, int y)
{
    // 油更“懒”，先横向
    int dir = rand() & 1 ? -1 : 1;

    if (TryMove(x, y, x, y - 1))
        return;
    if (TryMove(x, y, x + dir, y - 1))
        return;
    if (TryMove(x, y, x - dir, y - 1))
        return;

    if (TryMove(x, y, x + dir, y))
        return;
    if (TryMove(x, y, x - dir, y))
        return;
}

void UpdateCell(int x, int y)
{
    switch (g_type[Idx(x, y)])
    {
    case MAT_SAND:
        UpdateSand(x, y);
        break;
    case MAT_WATER:
        UpdateWater(x, y);
        break;
    case MAT_OIL:
        UpdateOil(x, y);
        break;
    default:
        break;
    }
}

void UpdatePixels()
{
    for (int y = 1; y < PIXEL_H; ++y)
    {
        bool leftFirst = rand() & 1;

        if (leftFirst)
        {
            for (int x = 0; x < PIXEL_W; ++x)
                UpdateCell(x, y);
        }
        else
        {
            for (int x = PIXEL_W - 1; x >= 0; --x)
                UpdateCell(x, y);
        }
    }
}

int main()
{
    printf("%d\n", 320 * 180);
    printf("%d\n", 640 * 360);
    printf("%d\n", 1280 * 720);
    printf("%d\n", 1920 * 1080);
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_W, WINDOW_H, "Pixel Sandbox", nullptr, nullptr);
    if (!window)
        return -1;
    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress))
        return -1;

    //
    ClearPixels();

    //
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, PIXEL_W, PIXEL_H, 0, GL_RGBA, GL_UNSIGNED_BYTE, g_color.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // clang-format off
    float quad[] = {
        -1,  1, 0, 1, 
        -1, -1, 0, 0, 
         1, -1, 1, 0, 
        -1,  1, 0, 1, 
         1, -1, 1, 0, 
         1,  1, 1, 1
    };
    // clang-format on

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    GLuint program = CreateProgram();
    glUseProgram(program);
    glUniform1i(glGetUniformLocation(program, "uTex"), 0);

    // PIXEL_W
    // PIXEL_H
    int pixel_w = PIXEL_W / 4;
    int pixel_h = PIXEL_H / 4;

    for (int i = pixel_w / 4; i < pixel_w + pixel_w; ++i)
    {
        int j = pixel_h / 4;
        for (int j = pixel_h / 4; j < pixel_h + pixel_h; ++j)
        {
            // SpawnSand(i, j);
            SpawnWater(i, j);
        }
    }

    pixel_w += pixel_w;
    pixel_h += pixel_h;
    for (int i = pixel_w / 4; i < pixel_w + pixel_w; ++i)
    {
        int j = pixel_h / 4;
        for (int j = pixel_h / 4; j < pixel_h + pixel_h; ++j)
        {
            // SpawnWater(i, j);
            SpawnSand(i, j);
        }
    }

    const double targetFrameTime = 1.0 / 60.0;

    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        //
        double currentTime = glfwGetTime();
        double delta       = currentTime - lastTime;

        if (delta < targetFrameTime)
        {
            std::this_thread::sleep_for(std::chrono::duration<double>(targetFrameTime - delta));
            continue;
        }

        lastTime = currentTime;

        //
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            double mx, my;
            glfwGetCursorPos(window, &mx, &my);
            int px = int(mx / WINDOW_W * PIXEL_W);
            int py = int((WINDOW_H - my) / WINDOW_H * PIXEL_H);
            SpawnSand(px, py);
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
            double mx, my;
            glfwGetCursorPos(window, &mx, &my);
            int px = int(mx / WINDOW_W * PIXEL_W);
            int py = int((WINDOW_H - my) / WINDOW_H * PIXEL_H);
            SpawnWater(px, py);
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
        {
            double mx, my;
            glfwGetCursorPos(window, &mx, &my);
            int px = int(mx / WINDOW_W * PIXEL_W);
            int py = int((WINDOW_H - my) / WINDOW_H * PIXEL_H);
            SpawnOil(px, py);
        }

        UpdatePixels();

        glBindTexture(GL_TEXTURE_2D, tex);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, PIXEL_W, PIXEL_H, GL_RGBA, GL_UNSIGNED_BYTE, g_color.data());

        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
