// "microlib" minimal C++ game utility library
// (c) Copyright 2017-2022 Juliet Colman

#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

// * resource_manager *
// Caches resources of the given type, created and loaded on first call to get.
template<typename T> 
class resource_manager
{
public:
  // Loader func: the default version calls load() on the given resource.
  // For resource types with no load function (e.g. strings), you can specify a 
  //  custom loader when creating the resource manager.
  using loader_func = std::function<bool(std::shared_ptr<T>, const std::string&)>;

  resource_manager(loader_func loader = default_loader) : m_loader(loader) {}

  std::shared_ptr<T> get(const std::string& filename) const
  {
    auto it = m_map.find(filename);
    if (it == m_map.end()) // [[unlikely]] // only on first call with this filename
    {
      auto p = std::make_shared<T>();
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

  void reload()
  {
    for (auto& pair : m_map)
    {
      pair.second->load(pair.first);
    }
  }

  void clear()
  {
    m_map.clear();
  }

private:
  using map = std::unordered_map<std::string, std::shared_ptr<T>>;
  mutable map m_map;

  loader_func m_loader;

  static bool default_loader(std::shared_ptr<T> res, const std::string& filename)
  {
    return res->load(filename); 
  }
};

