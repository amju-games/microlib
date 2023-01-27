// "microlib" minimal C++ game utility library
// (c) Copyright 2017-2022 Juliet Colman

#include "catch.hpp"
#include "multi_manager.h"

namespace
{
  class juliet_resource
  {
  public:
    bool load(const std::string&)
    {
      m_num_loads++;
      return true;
    }

    int get_num_loads() const { return m_num_loads; }

  private:
    int m_num_loads = 0;
  };

  bool string_loader(std::shared_ptr<std::string> string_res, const std::string& filename)
  {
    *string_res = filename;
    return true;
  }
}

TEST_CASE("create a multi manager, add resource managers", "[multi_manager]")
{
  multi_manager mm;
  mm.add_resource_manager(".txt", std::make_unique<resource_manager<std::string>>(string_loader));
  mm.add_resource_manager(".juliet", std::make_unique<resource_manager<juliet_resource>>());
}

TEST_CASE("get a resource", "[multi_manager]")
{
  multi_manager mm;
  mm.add_resource_manager(".juliet", std::make_unique<resource_manager<juliet_resource>>());
  std::shared_ptr<juliet_resource> res = mm.get<juliet_resource>("something.juliet");
  REQUIRE(res.get());
}


