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

  // Input handlers: return true if event is consumed
  virtual bool on_dir_button_action(const dir_button_action&) { return false; }
  virtual bool on_joystick_action(const joystick_action&) { return false; }
  virtual bool on_keyboard_action(const keyboard_action&) { return false; }
  virtual bool on_game_controller_button_action(const game_controller_button_action&) { return false; }
};

