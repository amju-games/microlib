// "microlib" minimal C++ game utility library
// (c) Copyright 2017 Jason Colman

#pragma once

class timer
{
public:
  // * update *
  // Call this once per frame
  void update();

  float get_dt() const;
  float get_elapsed() const;
};

