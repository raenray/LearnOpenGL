#include <engine/Shader.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

#include <glad/gl.h>

namespace engine
{

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexSrc = loadFile(vertexPath);
    std::string fragmentSrc = loadFile(fragmentPath);
    m_program = createProgram(vertexSrc, fragmentSrc);
}

Shader::~Shader()
{
    if (m_program)
    {
        glDeleteProgram(m_program);
    }
}

void Shader::bind() const
{
    glUseProgram(m_program);
}

void Shader::unbind() const
{
    glUseProgram(0);
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int success{};
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char info[1024];
        glGetShaderInfoLog(id, 1024, nullptr, info);
        std::string typeStr = (type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT";
        std::cerr << "[Shader Compile Error][" << typeStr << "]\n" << info << std::endl;
        glDeleteShader(id);
        throw std::runtime_error("Shader compilation failed");
    }

    return id;
}

unsigned int Shader::createProgram(const std::string& vertexSrc, const std::string& fragmentSrc)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexSrc);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    int success{};
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char info[1024];
        glGetProgramInfoLog(program, 1024, nullptr, info);
        std::cerr << "[Shader Link Error]\n" << info << std::endl;
        glDeleteProgram(program);
        throw std::runtime_error("Shader linking failed");
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

std::string Shader::loadFile(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open shader file: " + path);
    }

    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

int Shader::getUniformLocation(const std::string& name)
{
    if (m_uniformCache.contains(name))
    {
        return m_uniformCache[name];
    }

    int location = glGetUniformLocation(m_program, name.c_str());
    if (location == -1)
    {
        std::cerr << "[Warning] Uniform not found: " << name << std::endl;
    }

    m_uniformCache[name] = location;
    return location;
}

void Shader::setInt(const std::string& name, int value)
{
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setIntArray(const std::string& name, int* values, uint32_t count)
{
    glUniform1iv(getUniformLocation(name), count, values);
}

void Shader::setFloat(const std::string& name, float value)
{
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setVec2(const std::string& name, const glm::vec2& v)
{
    glUniform2f(getUniformLocation(name), v.x, v.y);
}

void Shader::setVec3(const std::string& name, const glm::vec3& v)
{
    glUniform3f(getUniformLocation(name), v.x, v.y, v.z);
}

void Shader::setVec4(const std::string& name, const glm::vec4& v)
{
    glUniform4f(getUniformLocation(name), v.x, v.y, v.z, v.w);
}

void Shader::setMat4(const std::string& name, const glm::mat4& m)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &m[0][0]);
}

} // namespace engine
