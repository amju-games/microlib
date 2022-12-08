// "microlib" minimal C++ game utility library
// (c) Copyright 2017 Jason Colman

#pragma once

#include <functional>
#include <map>
#include <string>

// Creates objects of type T or subclass-of-T.
// Each class must be registered with the Factory, by calling
// Add. The function that is registered should return a new object.
// This Factory design comes from "Modern C++ Design", but MSVC
// can't compile the Loki library, so this is a simplified version.
// Class S is the type used to identify the subclass of T you want.
template <class T, class S = std::string>
class factory 
{
public:
  // Function which creates a new T.
  using factory_function = std::function<T*()>;

  // Called once for each subtype of T. Registers a function
  // which creates an object of that type.
  bool add(const S& name, factory_function f)
  {
    m_map[name] = f;
    return true;
  }

  // Create an object of type T. The subtype of
  // the object depends on the string. This should match the ID
  // of a subtype which is registered.
  // Override this to create objects which aren't registered.
  T* create(const S& name)
  {
    auto it = m_map.find(name);
    if (it == m_map.end())
    {
      return nullptr;
    }

    factory_function f = it->second;
    if (f)
    {
      return f();
    }

    return nullptr;
  }

protected:
  std::map<S, factory_function> m_map;
};

