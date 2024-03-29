// "microlib" minimal C++ game utility library
// (c) Copyright 2017-2022 Juliet Colman

#include <stdlib.h> // atoi()
#include "string_utils.h"
#include "vec2.h"

strings split(const std::string& cs, char c)
{
  strings r;
  std::string s(cs);
  while (true)
  {
    size_t i = s.find(c);
    if (i == std::string::npos)
    {
      // No split character found, so push back the entire string and finish.
      if (!s.empty())
      {
        // Don't push empty string.. right?
        r.push_back(s);
      }
      break;
    }   
    else
    {
      // Found the special character.
      // Push back whatever is before the character, then work on the remainder
      // of the string.
#ifdef SPLIT_DEBUG
      std::cout << "Split: string: " << s.substr(0, i).c_str() << " rem: " << s.substr(i + 1).c_str() << "\n";
#endif
      std::string sub = s.substr(0, i);
      sub = trim(sub);
      if (!sub.empty())
      {
        r.push_back(sub);
      }
      s = s.substr(i + 1);
      s = trim(s);
    }
  }
  return r;
}

std::string trim(const std::string& s)
{
  std::string result(s);

  while (!result.empty() && isspace(result[0]))
  {
    result = result.substr(1);
  }

  while (!result.empty() && isspace(result[result.size() - 1]))
  {
    result = result.substr(0, result.size() - 1);
  }

  return result;
}

std::string replace(
  const std::string& s,
  const std::string& from,
  const std::string& to)
{
  if (from.empty())
  {
    // Trying to replace occurrences of "" with anything isn't really allowed
    return s;
  }

  std::string str(s);

  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != std::string::npos)
  {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
  }
  return str;
}

bool contains(const std::string& container, const std::string& search_for_this)
{
  if (search_for_this.empty())
  {
    return false;
  }
  auto f = container.find(search_for_this);
  return (f != std::string::npos);
}

int to_int(const std::string& s)
{
  return atoi(s.c_str());
}

float to_float(const std::string& s)
{
  return static_cast<float>(atof(s.c_str()));
}

std::string to_string(const vec2& v)
{
  return concat("(", v.x, ", ", v.y, ")");
}

std::string float_to_string(float f, int dp)
{
  std::stringstream ss;
  ss << std::fixed;
  ss << std::setprecision(dp);
  ss << f;
  return ss.str();
}


