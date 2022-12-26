// "microlib" minimal C++ game utility library
// (c) Copyright 2017-2022 Juliet Colman

#pragma once

#include <cassert>
#include <functional>
#include <map>
#include <type_traits> // is_base_of

// Reusable double-dispatcher
// Design idea from "Modern C++ Design".
// BASE_TYPE: base class for the types you want to dispatch on. E.g. game_object.
// TYPE_ID: a type for identifying each subclass of BASE_TYPE. E.g. an int or string.
// TYPE_ID_FUNC: a functor taking a BASE_TYPE*, returning an ID of type TYPE_ID, corresponding 
//  to the dynamic type of the arg.

template<class BASE_TYPE, typename TYPE_ID, class TYPE_ID_FUNC>
class double_dispatcher
{
public:
  // Register a handler for two subtypes of BASE_TYPE. The signature of the handler function is:
  //  void handler(DERIVED_TYPE_1*, DERIVED_TYPE_2*);

  template<class DERIVED_TYPE_1, class DERIVED_TYPE_2>
  bool add_handler(std::function<void(DERIVED_TYPE_1*, DERIVED_TYPE_2*)> specific_handler)
  {
    static_assert(std::is_base_of<BASE_TYPE, DERIVED_TYPE_1>::value);
    static_assert(std::is_base_of<BASE_TYPE, DERIVED_TYPE_2>::value);

    return add_handler(get_static_type_id<DERIVED_TYPE_1>(), get_static_type_id<DERIVED_TYPE_2>(), 
      [=](BASE_TYPE* obj1, BASE_TYPE* obj2)
      {
        DERIVED_TYPE_1* actual_obj1 = dynamic_cast<DERIVED_TYPE_1*>(obj1);
        DERIVED_TYPE_2* actual_obj2 = dynamic_cast<DERIVED_TYPE_2*>(obj2);
        assert(actual_obj1 != nullptr);
        assert(actual_obj2 != nullptr);
        specific_handler(actual_obj1, actual_obj2);
      });
  }

  // Dispatch to a previously registered handler, where the args match the dynamic types
  //  of obj1 and obj2.
  // Return true if dispatch is successful, false if no handler is registered for this pair
  //  of dynamic types.

  bool dispatch(BASE_TYPE* obj1, BASE_TYPE* obj2) const
  {
    return dispatch(obj1, obj2, m_handlers);
  }

private:

  // Get type ID for the given object.
  TYPE_ID get_type_id(const BASE_TYPE* obj) const
  {
    return TYPE_ID_FUNC()(obj);
  }

  // Get type ID for the given type.
  template<class DERIVED_TYPE>
  TYPE_ID get_static_type_id() const
  {
    static_assert(std::is_base_of<BASE_TYPE, DERIVED_TYPE>::value);
    DERIVED_TYPE t;
    return get_type_id(&t);
  }

  using coll_handler = std::function<void(BASE_TYPE*, BASE_TYPE*)>;
  using handler_map = std::map<std::pair<TYPE_ID, TYPE_ID>, coll_handler>;
  handler_map m_handlers;

  bool add_handler(TYPE_ID type1, TYPE_ID type2, coll_handler handler)
  {
    // It's ok for type1 == type2, and it's ok to reset an existing handler to a new function. 
    // But it's not ok to register a handler for (t1, t2) when a handler is already registered for 
    //  (t2, t1).
    if (m_handlers.find(std::make_pair(type2, type1)) != m_handlers.end())
    {
      return false;
    }

    m_handlers[std::make_pair(type1, type2)] = handler;
    return true;
  }

  bool dispatch(BASE_TYPE* obj1, BASE_TYPE* obj2, const handler_map& map) const
  {
    auto pair = std::make_pair(get_type_id(obj1), get_type_id(obj2));
    auto it = map.find(pair);
    if (it != map.end())
    {
      auto f = it->second;
      f(obj1, obj2);
      return true;
    } 
    // Try the other order
    std::swap(pair.first, pair.second);
    it = map.find(pair);
    if (it != map.end())
    {
      auto f = it->second;
      f(obj2, obj1); // reversed order
      return true;
    }
    return false;
  }
};

