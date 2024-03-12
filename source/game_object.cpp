// "microlib" minimal C++ game utility library
// (c) Copyright 2017-2022 Juliet Colman

#include "game_object.h"

game_object::game_object()
{
  static int unique_id = 0;
  set_id(unique_id++);
}

void game_object::update(float dt)
{
  if (is_updatable())
  {
    // Update position and velocity
    vec2 old = m_vel;
    m_vel += m_acc * dt;
    vec2 tr = (old + m_vel) * (dt * 0.5f); 
    m_pos += tr;
  }
}

void game_object::set_size(const vec2& size)
{
  m_size = size;
}

void game_object::set_pos(const vec2& v)
{
  m_pos = v;
}

void game_object::set_vel(const vec2& v)
{
  m_vel = v;
}

void game_object::set_acc(const vec2& v)
{
  m_acc = v;
}

const vec2& game_object::get_size() const
{
  return m_size;
}

const vec2& game_object::get_pos() const
{
  return m_pos;
}

const vec2& game_object::get_vel() const
{
  return m_vel;
}

const vec2& game_object::get_acc() const
{
  return m_acc;
}

