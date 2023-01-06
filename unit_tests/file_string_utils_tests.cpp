// "microlib" minimal C++ game utility library
// (c) Copyright 2017-2022 Juliet Colman

#include "catch.hpp"
#include "file_string_utils.h"

namespace
{
  const std::string PATH = "/my.path/to/";
  const std::string FILENAME = "file";
  const std::string EXT = ".ext";
  const std::string PATH_TO_FILE = PATH + FILENAME + EXT;
}

TEST_CASE("just_path", "[file_string_utils]")
{
  REQUIRE(just_path(PATH_TO_FILE) == "/my.path/to/");
}

TEST_CASE("just_path with no path", "[file_string_utils]")
{
  REQUIRE(just_path(FILENAME) == FILENAME);
}

TEST_CASE("just_filename", "[file_string_utils]")
{
  REQUIRE(just_filename(PATH_TO_FILE) == "file.ext");
}

TEST_CASE("just_filename with no filename", "[file_string_utils]")
{
  REQUIRE(just_filename(PATH) == "");
}

TEST_CASE("just_extension", "[file_string_utils]")
{
  REQUIRE(just_extension(PATH_TO_FILE) == EXT);
}

TEST_CASE("just_extension with no extension", "[file_string_utils]")
{
  REQUIRE(just_extension(FILENAME) == "");
}

