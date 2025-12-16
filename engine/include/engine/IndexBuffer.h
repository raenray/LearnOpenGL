#pragma once

namespace engine
{

class IndexBuffer
{
public:
    IndexBuffer(const unsigned int* indices, unsigned int count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    unsigned int count() const { return m_count; }

private:
    unsigned int m_id{};
    unsigned int m_count{};
};

} // namespace engine
