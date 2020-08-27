#include "Timestep.h"

namespace Mouton
{

    Chrono::Chrono()
        : m_Begin(std::chrono::high_resolution_clock::now())
    {
    }

    Timestep::Timestep(float time) : m_Delta(time)
    {
    }

    Timestep Chrono::GetDeltaTime()
    {
        using namespace std::chrono;

        duration<float> delta = high_resolution_clock::now() - m_Begin;
        return Timestep(delta.count());
    }

    void Chrono::Reset()
    {
        m_Begin = std::chrono::high_resolution_clock::now();
    }

    float Timestep::operator+(float x) const
    {
        return m_Delta + x;
    }

    float Timestep::operator-(float x) const
    {
        return m_Delta - x;
    }

    float Timestep::operator*(float x) const
    {
        return m_Delta * x;
    }

} // namespace Mouton
