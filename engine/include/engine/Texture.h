#pragma once

#include <string>

namespace engine
{

class Texture
{
public:
    explicit Texture(const std::string& path);
    Texture(uint32_t width, uint32_t height, const void* data);
    ~Texture();

    void bind(unsigned int slot = 0) const;
    void unbind() const;

    int getID() const { return m_id; }
    int width() const { return m_width; }
    int height() const { return m_height; }

    bool operator==(const Texture& other)
    {
        return other.m_id == m_id;
    }

    bool operator!=(const Texture& other)
    {
        return other.m_id != m_id;
    }

private:
    unsigned int m_id{};
    int m_width{};
    int m_height{};
    int m_channels{};
};

} // namespace engine
