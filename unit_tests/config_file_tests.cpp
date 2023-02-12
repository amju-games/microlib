#include "catch.hpp"
#include "config_file.h"

TEST_CASE("load a text config file", "[config_file]")
{
  text_config_file cf;
  REQUIRE(cf.load("test_config.txt"));
}

TEST_CASE("get string from text config file", "[config_file]")
{
  text_config_file cf;
  REQUIRE(cf.load("test_config.txt"));
  REQUIRE(cf.get_string("hello") == "world");
}

TEST_CASE("get an int from text config file", "[config_file]")
{
  text_config_file cf;
  REQUIRE(cf.load("test_config.txt"));
  REQUIRE(cf.get_int("int_0") == 0);
  REQUIRE(cf.get_int("int_1") == 1);
}

TEST_CASE("get a float from text config file", "[config_file]")
{
  text_config_file cf;
  REQUIRE(cf.load("test_config.txt"));
  REQUIRE(cf.get_float("float_0") == 0.f);
  REQUIRE(cf.get_float("float_1") == 1.f);
}

TEST_CASE("get a vec2 from text config file", "[config_file]")
{
  text_config_file cf;
  REQUIRE(cf.load("test_config.txt"));
  REQUIRE(cf.get_vec2("vec_2") == vec2(2, 3));
}


