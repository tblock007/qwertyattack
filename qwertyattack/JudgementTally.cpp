#include "JudgementTally.hpp"

#include <SFML/Config.hpp>

namespace qa {

JudgementTally::JudgementTally()
{
   reset();
}

TallyCounts JudgementTally::getTallies() const
{
   return counts_;
}

void JudgementTally::incrementTally(Judgement judgement)
{
   if (judgement == Judgement::GREAT) {
      counts_.greats++;
   }
   else if (judgement == Judgement::GOOD) {
      counts_.goods++;
   }
   else if (judgement == Judgement::MISS) {
      counts_.misses++;
   }
}

void JudgementTally::reset()
{
   counts_.greats = 0;
   counts_.goods = 0;
   counts_.misses = 0;
}

}  // namespace qa
