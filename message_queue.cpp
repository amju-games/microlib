// "microlib" minimal C++ game utility library
// (c) Copyright 2017 Jason Colman

#include "message_queue.h"

void message_queue::update(float dt)
{
  // Update current time
  m_time += dt;

  // Execute all messages whose timestamps have expired
  while (!m_q.empty())
  {
    message m =  *(m_q.begin());

    if (m.m_time < m_time)
    {
      m_q.erase(m_q.begin());
      m.execute();
    }
    else
    {
      break;
    }
  }
}

void message_queue::add(const message& m)
{
  m_q.insert(m);
}

