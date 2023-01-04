// "microlib" minimal C++ game utility library
// (c) Copyright 2017-2022 Juliet Colman

#include <memory>
#include "catch.hpp"
#include "string_utils.h"
#include "vec2.h"

TEST_CASE("concat float trims to 2 dp", "[string_utils]")
{
  REQUIRE(concat(1.234f) == "1.23");
  REQUIRE(concat(1.34567f) == "1.35");
}

TEST_CASE("stringify vec2", "[string_utils]")
{
  REQUIRE(to_string(vec2(1.234f, 5.678f)) == "(1.23, 5.68)");
}

TEST_CASE("concat 1 string element returns the element", "[string_utils]")
{
  REQUIRE(concat(std::string("apple")) == std::string("apple"));
}

TEST_CASE("concat 1 char* element returns the stringified element", "[string_utils]")
{
  REQUIRE(concat("apple") == std::string("apple"));
}

TEST_CASE("concat 1 int element returns stringified element", "[string_utils]")
{
  REQUIRE(concat(1) == std::string("1"));
}

TEST_CASE("concat 2 int elements returns concatenated stringified elements", "[string_utils]")
{
  REQUIRE(concat(1, 2) == std::string("12"));
}

TEST_CASE("concat 2 string elements returns concatenated elements", "[string_utils]")
{
  REQUIRE(concat(std::string("apple"), std::string("pear")) == std::string("applepear"));
}

TEST_CASE("concat mixture of types returns concatenated stringified objects", "[string_utils]")
{
  REQUIRE(concat(1, 3, "apple", "pear", 5.6789f) == std::string("13applepear5.68"));
}

