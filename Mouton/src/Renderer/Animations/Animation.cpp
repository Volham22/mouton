#include "Animation.h"


namespace Mouton
{

    Animation::Animation()
        : m_Name(), m_Duration(0.0), m_TickPerSecond(25.0), m_Tick(0.0), m_Begin(), m_Playing(false)
    {
    }

    Animation::Animation(const std::string& name, double duration, double tickPerSecond)
        : m_Name(name), m_Duration(duration), m_TickPerSecond(tickPerSecond != 0.0 ? tickPerSecond : 25.0),
          m_Tick(0.0), m_Begin(), m_Playing(false)
    {
    }

    void Animation::Play()
    {
        m_Playing = true;
        m_Begin = std::chrono::high_resolution_clock::now();
        m_Tick = 0.0;
    }

    void Animation::Stop()
    {
        m_Playing = false;
    }

    double Animation::Update()
    {
        using namespace std::chrono;

        auto elapsed = duration<double>(duration_cast<milliseconds>(high_resolution_clock::now() - m_Begin));
        m_Tick = elapsed.count() * m_TickPerSecond;

        MTN_TRACE(m_Tick);

        if(m_Tick < m_Duration)
            return m_Tick;
        else
        {
            m_Playing = false;
            return -1.0;
        }
    }

} // namespace Mouton
