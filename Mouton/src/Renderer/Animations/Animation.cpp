#include "Animation.h"


namespace Mouton
{

    Animation::Animation()
        : m_Name(), m_Duration(0.0), m_TickPerSecond(25.0), m_BeginTime()
    {
    }

    Animation::Animation(const std::string& name, double duration, double tickPerSecond)
        : m_Name(name), m_Duration(duration), m_TickPerSecond(tickPerSecond != 0.0 ? tickPerSecond : 25.0),
          m_BeginTime()
    {
    }

    void Animation::Play()
    {
        m_BeginTime = std::chrono::high_resolution_clock::now();
    }

    void Animation::Stop()
    {

    }

    void Animation::Update()
    {
        std::chrono::duration<double> elasped = m_BeginTime - std::chrono::high_resolution_clock::now();

        if(elasped.count() < m_Duration)
        {
            double progression = elasped.count() / m_Duration;

            
        }
    }

} // namespace Mouton
