// "microlib" minimal C++ game utility library
// (c) Copyright 2017 Jason Colman

#pragma once

#include "game_state.h"
#include "game_object.h"

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

  // Game Objects
  void add_game_object(game_object* object);
  void clear_game_objects(); // erase all
  game_objects* get_game_objects();

  // Functions commonly used by Game States
  void update_game_objects(float dt);

private:
  void update_state(); // go to new state if set

private:
  game_state* m_currentState = nullptr;
  game_state* m_newState = nullptr;

  game_objects m_objects;
};

