// "microlib" minimal C++ game utility library
// (c) Copyright 2017-2022 Juliet Colman

#define STATE_DEBUG

#ifdef STATE_DEBUG
#include <iostream>
#endif
#include "game.h"
#include "message_queue.h"

void game::on_keyboard_action(const keyboard_action& ka)
{
  get_game_state()->on_keyboard_action(ka);
}

void game::on_game_controller_button_action(const game_controller_button_action& gcba)
{
  get_game_state()->on_game_controller_button_action(gcba);
}

void game::on_dir_button_action(const dir_button_action& dba)
{
  get_game_state()->on_dir_button_action(dba);
}

void game::on_joystick_action(const joystick_action& ja)
{
  get_game_state()->on_joystick_action(ja);
}

void game::update(float dt)
{
  update_state();

  get_game_state()->update(dt);
}

void game::draw()
{
  get_game_state()->draw();
}

void game::run_one_loop(float dt)
{
  update(dt);
  draw();
}

void game::update_game_objects(float dt)
{
  // Make copy of game object container: updating might remove or add objects
  game_objects objs(m_objects); 

  for (p_game_object& go : objs)
  {
    go->update(dt);
  }
}

game_state* game::get_game_state()
{
  assert(m_currentState);
  return m_currentState;
}

void game::set_game_state(game_state* gs)
{
#ifdef STATE_DEBUG
std::cout << "game::SetCurrentState: new state is " << typeid(*gs).name() << "\n";
#endif

  m_newState = gs;
}

void game::update_state()
{
  if (!m_newState)
  {
    return;
  }

  if (m_currentState == m_newState)
  {
    m_newState = nullptr;
    return;
  }

  if (m_currentState)
  {
#ifdef STATE_DEBUG
std::cout << "game::UpdateState: deactivating state: " << typeid(*m_currentState).name() << "\n";
#endif

    // Deactivating state will no longer get events

    m_currentState->on_deactive();
  }
  else
  {
#ifdef STATE_DEBUG
std::cout << "game::UpdateState: no current state to deactivate.\n";
#endif
  }

  m_currentState = m_newState;
  assert(m_currentState);
  m_newState = nullptr;

#ifdef STATE_DEBUG
std::cout << "game::UpdateState: activating new state: " << typeid(*m_currentState).name() << "\n";
#endif

  // This next line may set m_newState, so zero it before - not after - this call!
  m_currentState->on_active();
}

void game::add_game_object(p_game_object object)
{
  m_objects.push_back(object);
}

void game::remove_game_object(int id)
{
  m_objects.erase(
    std::find_if(m_objects.begin(), m_objects.end(), 
      [=](p_game_object& go) { return go->get_id() == id; } ), 
    m_objects.end());
}

void game::clear_game_objects()
{
  m_objects.clear();
}

game_objects* game::get_game_objects()
{
  return &m_objects;
}
