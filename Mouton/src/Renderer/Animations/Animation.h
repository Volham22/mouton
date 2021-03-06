#ifndef ANIMATION_H
#define ANIMATION_H

#include "MoutonPch.h"

#include <chrono>

namespace Mouton {

    class Animation
    {
      public:
        Animation();
        Animation(const std::string& name, double duration,
                  double tickPerSecond);
        void Play();
        double Update();
        void Stop();

        const std::string& GetName() const { return m_Name; };
        double GetDuration() const { return m_Duration; };
        double GetTickPerSecond() const { return m_TickPerSecond; };

      private:
        std::string m_Name;
        double m_Duration, m_TickPerSecond;
        double m_Tick;
        std::chrono::high_resolution_clock::time_point m_Begin;
        bool m_Playing;
    };

} // namespace Mouton

#endif