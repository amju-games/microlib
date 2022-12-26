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
  virtual std::string get_string_type_id() const = 0;
};

struct fruit_string_id_getter
{
  std::string operator()(const fruit* f) const { return f->get_string_type_id(); }
};

class apple : public fruit
{
public:
  std::string get_string_type_id() const override { return "apple"; }
};

class orange : public fruit
{
public:
  std::string get_string_type_id() const override { return "orange"; }
};

using fruit_string_dd = double_dispatcher<fruit, std::string, fruit_string_id_getter>;

void handle_apple_orange(apple* a, orange* o)
{
  // Handle collision between an apple and orange
  apple_orange++;
}

void handle_orange_apple(orange* o, apple* a)
{
  // We should not end up here if we register the above function with the DD first.
  assert(false); 
}


TEST_CASE("create, destroy dd", "[double_dispatcher]")
{
  fruit_string_dd fsd;
}

TEST_CASE("add handler and dispatch, fruit string dd", "[double_dispatcher]")
{
  reset();
  REQUIRE(apple_orange == 0);

  fruit_string_dd fsd;
  bool added = fsd.add_handler<apple, orange>(handle_apple_orange);
  REQUIRE(added);

  bool added_again = fsd.add_handler<apple, orange>(handle_apple_orange);
  REQUIRE(added_again); // OK to redefine handler

  // Don't add a handler with reversed types of an existing handler, to avoid possible
  //  inconsistency.
  bool add_with_reversed_types = fsd.add_handler<orange, apple>(handle_orange_apple);
  REQUIRE_FALSE(add_with_reversed_types);

  apple a;
  orange o;
  bool dispatched = fsd.dispatch(&a, &o);
  REQUIRE(dispatched);
  REQUIRE(apple_orange == 1);

  dispatched = fsd.dispatch(&o, &a);
  REQUIRE(dispatched);
  REQUIRE(apple_orange == 2);

  dispatched = fsd.dispatch(&o, &o);
  REQUIRE_FALSE(dispatched);
  REQUIRE(apple_orange == 2);
}

