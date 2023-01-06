// "microlib" minimal C++ game utility library
// (c) Copyright 2017-2022 Juliet Colman

#include "catch.hpp"
#include "resource_manager.h"

class my_resource
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

namespace
{
  const std::string RES_NAME = "arbitrary_name";
}

TEST_CASE("create a resource manager, get a resource", "[resource_manager]")
{
  resource_manager<my_resource> rm;

  auto p1 = rm.get(RES_NAME);
  REQUIRE(p1.get());
  REQUIRE(p1->get_num_loads() == 1); // loaded once
}

TEST_CASE("get same resource twice, only loaded once", "[resource_manager]")
{
  resource_manager<my_resource> rm;

  auto p1 = rm.get(RES_NAME);
  REQUIRE(p1->get_num_loads() == 1);
  
  auto p2 = rm.get(RES_NAME);
  REQUIRE(p2.get());
  REQUIRE(p2->get_num_loads() == 1);

  REQUIRE(p1.get() == p2.get());
}

TEST_CASE("reload resource", "[resource_manager]")
{
  resource_manager<my_resource> rm;

  auto p1 = rm.get(RES_NAME);
  REQUIRE(p1->get_num_loads() == 1);

  rm.reload();

  REQUIRE(p1->get_num_loads() == 2);
}

TEST_CASE("clear data", "[resource_manager]")
{
  resource_manager<my_resource> rm;

  auto p1 = rm.get(RES_NAME);
  REQUIRE(p1->get_num_loads() == 1);

  rm.clear();

  auto p2 = rm.get(RES_NAME);
  REQUIRE(p2->get_num_loads() == 1);

  REQUIRE(p1.get() != p2.get());
}


