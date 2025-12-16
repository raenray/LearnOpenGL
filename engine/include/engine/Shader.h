#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

namespace engine
{

class Shader
{
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void bind() const;
    void unbind() const;

    // Uniform 设置
    void setInt(const std::string& name, int value);
    void setIntArray(const std::string& name, int* values, uint32_t count);
    void setFloat(const std::string& name, float value);
    void setVec2(const std::string& name, const glm::vec2& v);
    void setVec3(const std::string& name, const glm::vec3& v);
    void setVec4(const std::string& name, const glm::vec4& v);
    void setMat4(const std::string& name, const glm::mat4& m);

private:
    unsigned int compileShader(unsigned int type, const std::string& source);
    unsigned int createProgram(const std::string& vertexSrc, const std::string& fragmentSrc);

    std::string loadFile(const std::string& path);
    int getUniformLocation(const std::string& name);

private:
    unsigned int m_program{0};
    std::unordered_map<std::string, int> m_uniformCache;
};

} // namespace engine
