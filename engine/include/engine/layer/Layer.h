#pragma once

#include <string>

namespace engine
{

class Layer
{
public:
    explicit Layer(const std::string& name = "Layer")
        : m_name(name)
    {
    }

    virtual ~Layer() = default;

    virtual void onAttach() {}
    virtual void onDetach() {}

    virtual void onUpdate(float dt) {}
    virtual void onRender() {}
    virtual void onImGuiRender() {}

    const std::string& getName() const { return m_name; }

protected:
    std::string m_name;
};

} // namespace engine
