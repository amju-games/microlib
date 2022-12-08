// "microlib" minimal C++ game utility library
// (c) Copyright 2017 Jason Colman

#include "catch.hpp"
#include "message_queue.h"

namespace
{
int s_counter = 0;

void reset_counter()
{
  s_counter = 0;
}

} // anon namespace

TEST_CASE("update, not time to execute yet", "[message_queue]")
{
  reset_counter();
  message_queue mq;
  message msg([]() { s_counter++; }, 1.f);
  mq.add(msg);

  REQUIRE(s_counter == 0); 
  
  mq.update(0.1f);

  REQUIRE(s_counter == 0); 
}

TEST_CASE("update, is time to execute", "[message_queue]")
{
  reset_counter();
  message_queue mq;
  message msg([]() { s_counter++; }, 1.f);
  mq.add(msg);

  REQUIRE(s_counter == 0); 

  // Time has to be exceeded
  mq.update(1.f);
  REQUIRE(s_counter == 0); 
  mq.update(.01f);
  REQUIRE(s_counter == 1); 

  // Only executed once
  mq.update(1.f);
  REQUIRE(s_counter == 1); 
}


