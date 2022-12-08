// "microlib" minimal C++ game utility library
// (c) Copyright 2017 Jason Colman

#pragma once

#include <functional>
#include <set>

// * message *
// Wraps a function and a timestamp in the future. When the timestamp 
//  is reached, we execute the function.
struct message 
{
  message() = default;
  message(std::function<void()> f, float t) : m_time(t), m_func(f) {}

  // Timestamp: the time at which this message should be executed. 
  float m_time = 0;

  void execute() 
  {
    m_func();
  }

  std::function<void()> m_func;
};

inline bool operator<(const message& m1, const message& m2)
{
  return (m1.m_time < m2.m_time);
}

// Priority queue of messages. 
// messages are executed when the current time reaches the
//  timestamp for a message, allowing for timed messages.
class message_queue 
{
public:
  // Call from main thread once per frame
  void update(float dt);

  // Can be called from main thread or other threads
  void add(const message&); 

protected:
  // Priority queue of messages
  std::set<message> m_q;
  
  // Current time
  float m_time = 0;
};


