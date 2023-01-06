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


TEST_CASE("custom loader", "[resource_manager]")
{
  struct my_custom_loader_for_strings
  {
    bool load(std::shared_ptr<std::string>& string_resource, const std::string& filename) 
    { 
      *string_resource = filename;
      return true;
    }
  };

  resource_manager<std::string, my_custom_loader_for_strings> rm;
  std::shared_ptr<std::string> res = rm.get(RES_NAME);
  REQUIRE(res.get());
  REQUIRE(*res == RES_NAME); 
}

TEST_CASE("load fails", "[resource_manager]")
{
  struct string_failing_loader
  {
    bool load(std::shared_ptr<std::string>&, const std::string&) { return false; }
  };

  resource_manager<std::string, string_failing_loader> rm;
  std::shared_ptr<std::string> res = rm.get(RES_NAME);
  REQUIRE(res == nullptr);
}

