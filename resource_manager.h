#pragma once

#include <memory>
#include <unordered_map>

template<typename T> 
class resource_manager
{
public:
  std::shared_ptr<T> get(const std::string& filename)
  {
    auto it = m_map.find(filename);
    if (it == m_map.end()) // [[unlikely]] // only on first call with this filename
    {
      auto p = std::make_shared<T>();
      if (p->load(filename))
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

