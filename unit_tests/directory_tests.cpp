#include "catch.hpp"
#include "directory.h"

TEST_CASE("make dir", "[directory]")
{
  REQUIRE(make_dir("test/dir/1"));
}

