#pragma once

#include <memory>
#include <string>
#include <unordered_map>

// * default_loader *
// Default behaviour: call load() on a resource. This is for resource types with a load
//  function, no good for e.g. a string.
template<typename T>
struct default_loader
{
  bool load(std::shared_ptr<T>& resource, const std::string& filename)
  {
    return resource->load(filename);
  }
};

// * resource_manager *
// Caches resources of the given type, created and loaded on first call to get.
template<typename T, class LOADER = default_loader<T>> 
class resource_manager
{
public:
  std::shared_ptr<T> get(const std::string& filename)
  {
    auto it = m_map.find(filename);
    if (it == m_map.end()) // [[unlikely]] // only on first call with this filename
    {
      auto p = std::make_shared<T>();
      LOADER loader;
      if (loader.load(p, filename))
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
  map m_map;
};

