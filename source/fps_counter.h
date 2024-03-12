// "microlib" minimal C++ game utility library
// (c) Copyright 2017-2022 Juliet Colman

#pragma once

class fps_counter
{
public:
  void update(float dt)
  {
    m_frame_count++;
    m_elapsed_time += dt;
    if (m_elapsed_time > 1.0f)
    {
      m_fps = m_frame_count;
      m_frame_count = 0;
      m_elapsed_time -= 1.0f;
    }
  }

  int get_fps() const
  {
    return m_fps;
  }
  
private:
  float m_elapsed_time = 0;
  int m_frame_count = 0;
  int m_fps = 0;
};


