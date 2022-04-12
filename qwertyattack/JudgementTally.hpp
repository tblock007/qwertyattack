#pragma once
#include <SFML/System.hpp>
#include "common.hpp"

namespace qa {
// --------------------------------------------------------------------------------
/// <summary>
/// Represents counts for all judgements received in a SongRun
/// </summary>
// --------------------------------------------------------------------------------
struct TallyCounts {
   sf::Int32 greats;
   sf::Int32 goods;
   sf::Int32 misses;
};


// --------------------------------------------------------------------------------
/// <summary>
/// Represents counts for all judgements received in a SongRun
/// </summary>
// --------------------------------------------------------------------------------
class JudgementTally {
  public:
   JudgementTally();

   [[nodiscard]] TallyCounts getTallies() const;

   void incrementTally(Judgement judgement);

   void reset();

  private:
   TallyCounts counts_;
};
}  // namespace qa
