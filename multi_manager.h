// "microlib" minimal C++ game utility library
// (c) Copyright 2017-2022 Juliet Colman

#pragma once

#include <any>
#include <string>
#include <unordered_map>
#include "resource_manager.h"
#include "file_string_utils.h"

// Container of single-resource managers, so there is one store of all resources.
class multi_manager
{
public:
  template<typename T>
  void add_resource_manager(const std::string& extension, const resource_manager<T>& rm)
  {
    m_map[extension] = std::make_any<resource_manager<T>>(rm);
  }

  template<typename T>
  std::shared_ptr<T> get(const std::string& filename)
  {
    std::string extension = just_extension(filename);
    auto it = m_map.find(extension);
    if (it == m_map.end())
    {
      return nullptr;
    }
    else
    {
      const resource_manager<T>& rm = std::any_cast<resource_manager<T>>(it->second);
      return rm.get(filename);
    }
  }

private:
  // Map file extension (e.g. ".png") to a resource_manager<T>
  std::unordered_map<std::string, std::any> m_map;
};

