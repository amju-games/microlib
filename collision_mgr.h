// "microlib" minimal C++ game utility library
// (c) Copyright 2017-2022 Juliet Colman

#pragma once

#include <array>
#include <vector>
#include "game_object.h"

using collision_pair = std::array<game_object*, 2>;
using collision_vec = std::vector<collision_pair>;

// Collision manager: policy-based collision strategy and double-dispatcher combo.
// Policy-based design idea is from "Modern C++ Design".

// BROAD_PHASE and NARROW_PHASE collision strategies  should provide broad_phase() 
//  and narrow_phase() members respectively.
// DOUBLE_DISPATCHER should provide a dispatch() member which calls a handler appropriate to the
//  dynamic types of the two colliding game objects.

template<class DOUBLE_DISPATCHER, class BROAD_PHASE, class NARROW_PHASE>
class collision_mgr : public DOUBLE_DISPATCHER, public BROAD_PHASE, public NARROW_PHASE
{
public:
  void check_for_collisions() 
  {
    const auto poss_collisions = BROAD_PHASE::broad_phase();
    const auto actual_collisions = NARROW_PHASE::narrow_phase(poss_collisions);
    for (const auto& c: actual_collisions)
    {
      DOUBLE_DISPATCHER::dispatch(c[0], c[1]);
    }
  }
};


