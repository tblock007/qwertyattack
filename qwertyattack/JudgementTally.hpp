#pragma once
#include <SFML/System.hpp>
#include "common.hpp"

namespace qa {
// --------------------------------------------------------------------------------
/// <summary>
/// Represents counts for all judgements received in a SongRun
/// </summary>
// --------------------------------------------------------------------------------
class JudgementTally {
  public:
   JudgementTally();

   std::tuple<sf::Int32, sf::Int32, sf::Int32> getTallies() const;

   void incrementTally(Judgement judgement);

   void reset();

  private:
   sf::Int32 greats_;
   sf::Int32 goods_;
   sf::Int32 misses_;
};
}  // namespace qa
