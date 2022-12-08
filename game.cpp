// "microlib" minimal C++ game utility library
// (c) Copyright 2017 Jason Colman

#include "game.h"
#include "message_queue.h"

//#define STATE_DEBUG

void game::update(float dt)
{
  update_state();

//  TheTimer::Instance()->Update();
//  TheEventPoller::Instance()->Update();
//  TheMessageQueue::Instance()->Update();

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
  game_objects objs(m_objects); 
  // Yikes, but updating might remove or add objects

  for (game_object* go : objs)
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

void game::add_game_object(game_object* object)
{
  m_objects.push_back(object);
}

void game::clear_game_objects()
{
  m_objects.clear();
}

game_objects* game::get_game_objects()
{
  return &m_objects;
}
