// "microlib" minimal C++ game utility library
// (c) Copyright 2017-2022 Juliet Colman

#pragma once

#include "action.h"

class game_state
{
public:
  virtual ~game_state() = default;

  virtual void update(float dt) = 0;
  virtual void draw() = 0;
 
  virtual void on_active() {}
  virtual void on_deactive() {}

  // TODO Deprecated
  virtual void on_input(int input) {}

  virtual void on_dir_button_action(const dir_button_action&) {}
  virtual void on_joystick_action(const joystick_action&) {}

};

