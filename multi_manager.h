// "microlib" minimal C++ game utility library
// (c) Copyright 2017-2022 Juliet Colman

#pragma once

#include <iostream>

#include <string>
#include <unordered_map>
#include "resource_manager.h"
#include "file_string_utils.h"

// Container of single-resource managers, so there is one store of all resources.
class multi_manager
{
public:
  void add_resource_manager(const std::string& extension, std::unique_ptr<resource_manager_base>&& rm)
  {
    m_map.insert(std::make_pair(extension, std::move(rm)));
  }

  template<typename T>
  std::shared_ptr<T> get(const std::string& filename)
  {
    std::string extension = just_extension(filename);
    auto it = m_map.find(extension);
    if (it == m_map.end())
    {
std::cout << "No resource manager for " << extension << " found!\n";
      return nullptr;
    }
    else
    {
      auto* manager = it->second.get(); 
      const resource_manager<T>* rm = dynamic_cast<resource_manager<T>*>(manager);

      if (!rm)
      {
std::cout << "There is a resource manager for " << extension << " but the expected type is not " << typeid(T).name() << "\n";
        return nullptr;
      }

      return rm->get(filename);
    }
  }

  void reload()
  {
    for (auto& p : m_map)
    {
std::cout << "Reloading data for " << p.first << " files\n";
      auto& rm = p.second;
      rm->reload(); 
    }
  }

private:
  // Map file extension (e.g. ".png") to a resource_manager<T>
  std::unordered_map<std::string, std::unique_ptr<resource_manager_base>> m_map;
};

