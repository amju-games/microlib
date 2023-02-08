// "microlib" minimal C++ game utility library
// (c) Copyright 2017-2022 Juliet Colman

#include <memory>
#include "catch.hpp"
#include "double_dispatcher.h"

namespace
{
int apple_orange = 0;

void reset()
{
  apple_orange = 0;
}

} // anon namespace

class fruit
{
public:
  virtual ~fruit() = default;
};

class apple : public fruit
{
public:
};

class orange : public fruit
{
public:
};

using fruit_dd = double_dispatcher<fruit>;

void handle_apple_orange(apple*, orange*)
{
  // Handle collision between an apple and orange
  apple_orange++;
}

void handle_orange_apple(orange*, apple*)
{
  // We should not end up here if we register the above function with the DD first.
  assert(false); 
}


TEST_CASE("create, destroy dd", "[double_dispatcher]")
{
  fruit_dd fsd;
}

TEST_CASE("add handler and dispatch, fruit string dd", "[double_dispatcher]")
{
  reset();
  REQUIRE(apple_orange == 0);

  fruit_dd fdd;
  bool added = fdd.add_handler<apple, orange>(handle_apple_orange);
  REQUIRE(added);

  bool added_again = fdd.add_handler<apple, orange>(handle_apple_orange);
  REQUIRE(added_again); // OK to redefine handler

  // Don't add a handler with reversed types of an existing handler, to avoid possible
  //  inconsistency.
  bool add_with_reversed_types = fdd.add_handler<orange, apple>(handle_orange_apple);
  REQUIRE_FALSE(add_with_reversed_types);

  apple a;
  orange o;
  bool dispatched = fdd.dispatch(&a, &o);
  REQUIRE(dispatched);
  REQUIRE(apple_orange == 1);

  dispatched = fdd.dispatch(&o, &a);
  REQUIRE(dispatched);
  REQUIRE(apple_orange == 2);

  dispatched = fdd.dispatch(&o, &o);
  REQUIRE_FALSE(dispatched);
  REQUIRE(apple_orange == 2);
}

TEST_CASE("has_handler false case", "[double_dispatcher]")
{
  fruit_dd fdd;
  apple a;
  orange o;
  REQUIRE_FALSE(fdd.has_handler(&a, &o));
  REQUIRE_FALSE(fdd.has_handler(&o, &a));
}

TEST_CASE("has_handler true case", "[double_dispatcher]")
{
  fruit_dd fdd;
  apple a;
  orange o;
  fdd.add_handler<apple, orange>(handle_apple_orange);
  REQUIRE(fdd.has_handler(&a, &o));
  REQUIRE(fdd.has_handler(&o, &a));
}

