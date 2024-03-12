// "microlib" minimal C++ game utility library
// (c) Copyright 2017-2022 Juliet Colman

#pragma once

#define RES_MANAGER_DEBUG

#ifdef RES_MANAGER_DEBUG
#include <iostream>
#endif

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include "directory.h"

// Interface for reload function
class resource_manager_base
{
public:
  virtual ~resource_manager_base() = default;
  virtual void reload() = 0;
};

// * resource_manager *
// Caches resources of the given type, created and loaded on first call to get.
template<typename T> 
class resource_manager : public resource_manager_base
{
public:
  // Loader func: the default version calls load() on the given resource.
  // The first param is the resource.
  // The second param is the filename, and the data directory is prepended.
  // For resource types with no load function (e.g. strings), you can specify a 
  //  custom loader when creating the resource manager.
  using loader_func = std::function<bool(std::shared_ptr<T>, const std::string&)>;

  // Creator func: set a custom func to create a new subclass-of-T. 
  // Default creator creates a new T.
  using creator_func = std::function<std::shared_ptr<T>()>;

  resource_manager(loader_func loader = default_loader, creator_func creator = default_creator) 
    : m_loader(loader), m_creator(creator) {}

  std::shared_ptr<T> get(const std::string& filename) const
  {
    auto it = m_map.find(filename);
    if (it == m_map.end()) // [[unlikely]] // only on first call with this filename
    {
      auto p = m_creator();
      if (m_loader(p, filename))
      {
        m_map[filename] = p;
        return p;
      } 
      else
      {
        return nullptr; // return optional?
      }
    }
    else
    {
      return it->second;
    }
  }

  void reload() override
  {
    for (auto [filename, p] : m_map)
    {
#ifdef RES_MANAGER_DEBUG
std::cout << "  Reloading " << filename << "\n";
#endif
      m_loader(p, filename); // this should succeed, if it did in get() 
    }
  }

  void clear()
  {
    m_map.clear();
  }

private:
  using map = std::unordered_map<std::string, std::shared_ptr<T>>;
  mutable map m_map; // so get() can be const

  loader_func m_loader;
  creator_func m_creator;

public:
  static bool default_loader(std::shared_ptr<T> res, const std::string& filename)
  {
    return res->load(get_data_dir() + filename); 
  }

  static std::shared_ptr<T> default_creator()
  {
    return std::make_shared<T>();
  }

};

