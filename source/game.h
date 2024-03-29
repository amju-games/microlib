// "microlib" minimal C++ game utility library
// (c) Copyright 2017-2022 Juliet Colman

#pragma once

#include <chrono>
#include <memory>
#include <vector>
#include "action.h"
#include "game_state.h"
#include "game_object.h"

using p_game_object = std::shared_ptr<game_object>;
using game_objects = std::vector<p_game_object>;

class game 
{
public:
  void update(float dt);
  void draw();

  // Execute one game loop, use if Run() not suitable for platform
  void run_one_loop(float dt);

  // Game States
  game_state* get_game_state(); 
  void set_game_state(game_state* gs);

  template <class GS> 
  void set_game_state(std::unique_ptr<GS>& gs)
  {
    set_game_state(gs.get());
  }

  // Game Objects
  void add_game_object(p_game_object object);
  void remove_game_object(int id);
  void clear_game_objects(); // erase all

  p_game_object& get_game_object(int id);
  game_objects* get_game_objects();

  // Functions commonly used by Game States
  void update_game_objects(float dt);

  // Input: (pass through to current game state)
  void on_dir_button_action(const dir_button_action&);

  void on_joystick_action(const joystick_action&);

  void on_keyboard_action(const keyboard_action&);

  void on_game_controller_button_action(const game_controller_button_action&);

  using duration = std::chrono::duration<float, std::milli>;
  const duration& get_draw_time() const { return  m_draw_time; }
  const duration& get_update_time() const { return m_update_time; }

private:
  void update_state(); // go to new state if set

private:
  game_state* m_currentState = nullptr;
  game_state* m_newState = nullptr;

  game_objects m_objects;

  duration m_draw_time;
  duration m_update_time;
};

