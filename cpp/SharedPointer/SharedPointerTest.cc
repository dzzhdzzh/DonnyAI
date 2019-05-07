#include "SharedPointer/SharedPointer.hh"

#include <vector>

#include "3rdParty/Catch.hh"

using Data = std::vector<int>;

TEST_CASE("Test SharedPointer default constructor")
{
  Utility::SharedPointer<Data> sp;
  REQUIRE(sp.use_count() == 0U);
  REQUIRE_THROWS(*sp);
  REQUIRE_THROWS(sp->size());
}

TEST_CASE("Test SharedPointer copy constructor")
{
  auto sp1 = Utility::make_shared<Data>(std::initializer_list<int>{1, 2, 3});
  REQUIRE(sp1.use_count() == 1U);
  REQUIRE((*sp1)[0] == 1);
  REQUIRE(sp1->size() == 3U);

  {
    auto sp2 = sp1;
    REQUIRE(sp1.use_count() == 2U);
    REQUIRE(sp2.use_count() == 2U);
    REQUIRE((*sp2)[0] == 1);
    REQUIRE(sp2->size() == 3U);
  }

  REQUIRE(sp1.use_count() == 1U);
}

TEST_CASE("Test SharedPointer copy assignment")
{
  auto sp1 = Utility::make_shared<Data>(std::initializer_list<int>{1, 2, 3});
  REQUIRE(sp1.use_count() == 1);
  REQUIRE((*sp1)[0] == 1);
  REQUIRE(sp1->size() == 3U);

  {
    Utility::SharedPointer<Data> sp2;
    sp2 = sp1;
    REQUIRE(sp1.use_count() == 2U);
    REQUIRE(sp2.use_count() == 2U);
    REQUIRE((*sp2)[0] == 1);
    REQUIRE(sp2->size() == 3U);
  }

  REQUIRE(sp1.use_count() == 1U);
}

TEST_CASE("Test SharedPointer move constructor")
{
  auto sp1 = Utility::make_shared<Data>(std::initializer_list<int>{1, 2, 3});
  REQUIRE(sp1.use_count() == 1U);
  REQUIRE((*sp1)[0] == 1);
  REQUIRE(sp1->size() == 3U);

  auto sp2 = move(sp1);
  REQUIRE(sp2.use_count() == 1U);
  REQUIRE((*sp2)[0] == 1);
  REQUIRE(sp2->size() == 3U);
}

TEST_CASE("Test SharedPointer move assignment")
{
  auto sp1 = Utility::make_shared<Data>(std::initializer_list<int>{1, 2, 3});
  REQUIRE(sp1.use_count() == 1);
  REQUIRE((*sp1)[0] == 1);
  REQUIRE(sp1->size() == 3U);

  Utility::SharedPointer<Data> sp2;
  sp2 = std::move(sp1);
  REQUIRE(sp2.use_count() == 1U);
  REQUIRE((*sp2)[0] == 1);
  REQUIRE(sp2->size() == 3U);
}
