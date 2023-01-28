// "microlib" minimal C++ game utility library
// (c) Copyright 2017-2022 Juliet Colman

#pragma once

#include <utility>

enum class dir_button_name
{
  up, down, left, right
};

enum class button_value
{
  up, down
};

using dir_button_action = std::pair<dir_button_name, button_value>;

// (x, y) values, both are in range -1 .. 1
using joystick_action = std::pair<float, float>;

