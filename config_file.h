#pragma once

#include <string>
#include <unordered_map>
#include "vec2.h"

class config_file
{
public:
  virtual ~config_file() = default;
  virtual bool load(const std::string& filename) = 0;

  virtual std::string get_string(const std::string& key) = 0;
  virtual int get_int(const std::string& key) = 0;
  virtual float get_float(const std::string& key) = 0;
  virtual vec2 get_vec2(const std::string& key) = 0;
};

class text_config_file : public config_file
{
public:
  bool load(const std::string& filename) override;

  std::string get_string(const std::string& key) override;
  int get_int(const std::string& key) override; 
  float get_float(const std::string& key) override; 
  vec2 get_vec2(const std::string& key) override;

private:
  std::string m_filename;
  std::unordered_map<std::string, std::string> m_map;
};

