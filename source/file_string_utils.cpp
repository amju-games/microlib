// "microlib" minimal C++ game utility library
// (c) Copyright 2017-2022 Juliet Colman

#include "file_string_utils.h"

std::string just_path(const std::string& path_and_filename)
{
  std::string ret = path_and_filename;
  size_t f = ret.find_last_of('/');
  if (f != std::string::npos)
  {
    ret = ret.substr(0, f + 1);
  }
  return ret;
}

std::string just_filename(const std::string& path_and_filename)
{
  std::string ret = path_and_filename;
  size_t f = ret.find_last_of('/');
  if (f != std::string::npos)
  {
    ret = ret.substr(f + 1);
  }
  return ret;
}

std::string just_extension(const std::string& path_and_filename)
{
  size_t f = path_and_filename.find_last_of('.');
  if (f != std::string::npos)
  {
    return path_and_filename.substr(f);
  }
  return "";
}

