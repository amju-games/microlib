// "microlib" minimal C++ game utility library
// (c) Copyright 2017-2022 Juliet Colman

#pragma once

//#include <format> // C++20, not supported yet!? :(
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

struct vec2;
std::string to_string(const vec2& v);

inline std::string concat(const vec2& v) { return to_string(v); }

inline std::string concat(float f) 
{ 
  //return std::format("{:.2f}", f);  // not supported?
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(2) << f;
  return oss.str();
}

inline std::string concat(int i) { return std::to_string(i); }

inline std::string concat(const char* c) { return std::string(c); }

inline std::string concat(const std::string& s) { return s; }

template<typename T, typename ...Tail>
std::string concat(T t, Tail... tail) { return concat(t) + concat(tail...); }

using strings = std::vector<std::string>;

// Split string s into multiple strings. Split char is not included in
//  the results. If yes_trim, remove whitespace from beginning and end
//  of result strings.
strings split(const std::string& s, char split_char, bool yes_trim = true);

// Remove whitespace from beginning and end of s
std::string trim(const std::string& s);

std::string replace(
  const std::string& in_this_string, 
  const std::string& replace_this, 
  const std::string& with_this);

bool contains(const std::string& container, const std::string& search_for_this);

int to_int(const std::string& s);

float to_float(const std::string& s);


