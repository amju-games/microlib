// "microlib" minimal C++ game utility library
// (c) Copyright 2017 Jason Colman

#pragma once

#include "vec2.h"

struct aabb
{
  vec2 m_min, m_max;

  // Translate box
  aabb& operator+=(const vec2& tr)
  {
    m_min += tr;
    m_max += tr;
    return *this;
  }
};

