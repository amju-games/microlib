// "microlib" minimal C++ game utility library
// (c) Copyright 2017 Jason Colman

#pragma once

class game_state
{
public:
  virtual ~game_state() = default;

  virtual void update(float dt) = 0;
  virtual void draw() = 0;
 
  virtual void on_active() {}
  virtual void on_deactive() {}
};

