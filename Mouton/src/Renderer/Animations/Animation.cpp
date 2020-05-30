#include "Animation.h"


namespace Mouton
{

    Animation::Animation()
        : m_Name(), m_Duration(0.0), m_TickPerSecond(25.0), m_BeginTime(), m_Playing(false)
    {
    }

    Animation::Animation(const std::string& name, double duration, double tickPerSecond)
        : m_Name(name), m_Duration(duration), m_TickPerSecond(tickPerSecond != 0.0 ? tickPerSecond : 25.0),
          m_BeginTime(), m_Playing(false)
    {
    }

    void Animation::Play()
    {
        m_Playing = true;
        m_BeginTime = std::chrono::high_resolution_clock::now();
    }

    void Animation::Stop()
    {
        m_Playing = false;
    }

    double Animation::Update()
    {
        std::chrono::duration<double> elasped = std::chrono::high_resolution_clock::now() - m_BeginTime;

        if(elasped.count() < m_Duration)
            return elasped.count();
        else
            return -1.0;
    }

} // namespace Mouton
