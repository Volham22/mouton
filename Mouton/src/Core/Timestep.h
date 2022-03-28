#ifndef TIMESTEP_H
#define TIMESTEP_H

#include "MoutonPch.h"

#include <chrono>

namespace Mouton {
    struct Timestep {
        Timestep(float time = 0.0f);

        float GetSeconds() const { return m_Delta; };
        float GetMilliseconds() const { return m_Delta * 1000.0f; };

        float operator+(float x) const;
        float operator-(float x) const;
        float operator*(float x) const;

      private:
        float m_Delta;
    };

    class Chrono
    {
      public:
        Chrono();
        Timestep GetDeltaTime();
        void Reset();

      private:
        std::chrono::high_resolution_clock::time_point m_Begin;
    };
} // namespace Mouton

#endif