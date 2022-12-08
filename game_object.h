// "microlib" minimal C++ game utility library
// (c) Copyright 2017 Jason Colman

#pragma once

#include <vector>
#include "vec2.h"
#include "aabb.h"

class game_object
{
public:
  game_object() = default;
  virtual ~game_object() = default; 

  virtual void update(float dt);

  void set_pos(const vec2&);
  void set_vel(const vec2&);
  void set_acc(const vec2&);

  const vec2& get_pos() const;
  const vec2& get_vel() const;
  const vec2& get_acc() const;

  // game_objects have a bounding box
  const aabb& get_aabb() const { return m_aabb; } 

protected:
  int m_id = -1;
  vec2 m_pos;
  vec2 m_vel;
  vec2 m_acc;
  aabb m_aabb;
};

typedef game_object* p_game_object;
  
typedef std::vector<p_game_object> game_objects;


