// "microlib" minimal C++ game utility library
// (c) Copyright 2017-2022 Juliet Colman

#pragma once

#include <array>
#include <vector>
#include "game_object.h"

using collision_pair = std::array<game_object*, 2>;
using collision_vec = std::vector<colllision_pair>;

// Collision manager: policy-based collision strategy and double-dispatcher combo.
// Policy-based design idea is from "Modern C++ Design".

// COLLISION_STRATEGY should provide broad_phase() and narrow_phase() members.
// DOUBLE_DISPATCHER should provide a dispatch() member which calls a handler appropriate to the
//  dynamic types of the two colliding game objects.

template<class DOUBLE_DISPATCHER, class COLLISION_STRATEGY>
class collision_mgr : public DOUBLE_DISPATCHER, public COLLISION_STRATEGY
{
public:
  void check_for_collisions() 
  {
    const auto poss_collisions = broad_phase();
    const auto actual_collisions = narrow_phase(poss_collisions);
    for (const auto& c: actual_collisions)
    {
      dispatch(c[0], c[1]);
    }
  }
};

