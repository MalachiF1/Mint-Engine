#pragma once

namespace mint
{

    class Timestep
    {
      public:
        Timestep(float time = 0.0f) : m_time(time) {}

        operator float() const { return m_time; }

        inline float getSeconds() const { return m_time; }
        inline float getMilliSeconds() const { return m_time * 1000; }

      private:
        float m_time;
    };

} // namespace mint
