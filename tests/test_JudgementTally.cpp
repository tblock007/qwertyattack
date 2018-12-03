#include "../JudgementTally.hpp"
#include "catch.hpp"

namespace qa {

TEST_CASE("JudgementTally Initialization", "[judgementtally]")
{
   JudgementTally eut;
   auto [greats, goods, misses] = eut.getTallies();

   REQUIRE(greats == 0);
   REQUIRE(goods == 0);
   REQUIRE(misses == 0);
}

TEST_CASE("JudgementTally Increment and Reset", "[judgementtally]")
{
   JudgementTally eut;
   auto [greats, goods, misses] = eut.getTallies();

   eut.incrementTally(Judgement::GREAT);
   eut.incrementTally(Judgement::GOOD);
   eut.incrementTally(Judgement::MISS);

   std::tie(greats, goods, misses) = eut.getTallies();

   REQUIRE(greats == 1);
   REQUIRE(goods == 1);
   REQUIRE(misses == 1);

   eut.incrementTally(Judgement::GREAT);
   eut.incrementTally(Judgement::GREAT);
   eut.incrementTally(Judgement::GREAT);
   eut.incrementTally(Judgement::GREAT);
   eut.incrementTally(Judgement::GOOD);

   std::tie(greats, goods, misses) = eut.getTallies();

   REQUIRE(greats == 5);
   REQUIRE(goods == 2);
   REQUIRE(misses == 1);

   eut.incrementTally(Judgement::MISS);
   eut.incrementTally(Judgement::MISS);
   eut.incrementTally(Judgement::MISS);

   std::tie(greats, goods, misses) = eut.getTallies();

   REQUIRE(greats == 5);
   REQUIRE(goods == 2);
   REQUIRE(misses == 4);

   eut.reset();

   std::tie(greats, goods, misses) = eut.getTallies();

   REQUIRE(greats == 0);
   REQUIRE(goods == 0);
   REQUIRE(misses == 0);
}

}  // namespace qa
