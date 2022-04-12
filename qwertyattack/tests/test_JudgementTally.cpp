#include "../JudgementTally.hpp"
#include "catch.hpp"

namespace qa {

TEST_CASE("JudgementTally Initialization", "[judgementtally]")
{
   JudgementTally eut;
   auto const [greats, goods, misses] = eut.getTallies();

   REQUIRE(greats == 0);
   REQUIRE(goods == 0);
   REQUIRE(misses == 0);
}

TEST_CASE("JudgementTally Increment and Reset", "[judgementtally]")
{
   JudgementTally eut;

   eut.incrementTally(Judgement::GREAT);
   eut.incrementTally(Judgement::GREAT);
   eut.incrementTally(Judgement::GREAT);
   eut.incrementTally(Judgement::GREAT);
   eut.incrementTally(Judgement::GREAT);
   eut.incrementTally(Judgement::GOOD);
   eut.incrementTally(Judgement::GOOD);
   eut.incrementTally(Judgement::MISS);
      
   auto const [greats, goods, misses] = eut.getTallies();

   REQUIRE(greats == 5);
   REQUIRE(goods == 2);
   REQUIRE(misses == 1);

   eut.reset();

   auto const [reset_greats, reset_goods, reset_misses] = eut.getTallies();

   REQUIRE(reset_greats == 0);
   REQUIRE(reset_goods == 0);
   REQUIRE(reset_misses == 0);
}

}  // namespace qa
