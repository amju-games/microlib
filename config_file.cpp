#define CONFIG_FILE_DEBUG

#ifdef CONFIG_FILE_DEBUG
#include <cassert>
#include <iostream>
#endif

#include "config_file.h"
#include "file.h"
#include "string_utils.h"

bool text_config_file::load(const std::string& filename)
{
  m_map.clear(); // for reload

  text_file f;
  if (!f.open_for_reading(filename))
  {
    return false;
  }

  std::string line;
  int line_num = 0;
  while (f.read_string(line))
  {
    line_num++;
    if (line.empty() || line [0] == '#')
    {
      continue;
    }

#ifdef CONFIG_FILE_DEBUG
std::cout << "Line " << line_num << ": " << line << "\n";
#endif

    strings stripped_comment = split(line, '#');

    strings s = split(stripped_comment[0], '=');
    if (s.size() != 2)
    {
      std::cout << "Bad line " << line_num << " in \"" << filename << "\"\n";
      return false;
    }
    m_map[s[0]] = s[1];
  }

  m_filename = filename;
  return true;
}

std::string text_config_file::get_string(const std::string& key) 
{
#ifdef CONFIG_FILE_DEBUG
  if (m_map.find(key) == m_map.end())
  {
    std::cout << "Config file \"" << m_filename << "\" is missing value for \"" << key << "\"\n";
    // Config files are set during development, they should not have missing
    //  values.
    abort();
  }
#endif
  return m_map[key];
}

float text_config_file::get_float(const std::string& key)
{
  return to_float(get_string(key));
}

int text_config_file::get_int(const std::string& key)
{
  return to_int(get_string(key));
}

f_colour text_config_file::get_f_colour(const std::string& key) 
{
  std::string s = get_string(key);
  s = replace(s, "(", "");
  s = replace(s, ")", "");
  strings strs = split(s, ',');
  return f_colour(to_float(strs[0]), to_float(strs[1]), to_float(strs[2]));
}

vec2 text_config_file::get_vec2(const std::string& key) 
{
  std::string s = get_string(key);
  s = replace(s, "(", "");
  s = replace(s, ")", "");
  strings strs = split(s, ',');
  return vec2(to_float(strs[0]), to_float(strs[1]));
}



