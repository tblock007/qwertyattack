#include "JudgementTally.hpp"

namespace qa {
// ********************************************************************************
/// <summary>
/// Constructs a new instance of a JudgementTally, with all counts initialized to zero
/// </summary>
/// <changed>tblock,11/19/2018</changed>
// ********************************************************************************
JudgementTally::JudgementTally()
{
   reset();
}

// ********************************************************************************
/// <summary>
/// Returns the tallies that have been counted thus far
/// </summary>
/// <returns>The number of GREATs, the number of GOODs, the number of MISSes</returns>
/// <changed>tblock,11/19/2018</changed>
// ********************************************************************************
TallyCounts JudgementTally::getTallies() const
{
   return counts_;
}

// ********************************************************************************
/// <summary>
/// Increments the appropriate tally given an input judgement
/// </summary>
/// <param name="judgement">The received judgement whose count is to be incremented</param>
/// <changed>tblock,11/19/2018</changed>
// ********************************************************************************
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

// ********************************************************************************
/// <summary>
/// Resets the counts of this JudgementTally to zero.
/// </summary>
/// <changed>tblock,12/3/2018</changed>
// ********************************************************************************
void JudgementTally::reset()
{
   counts_.greats = 0;
   counts_.goods = 0;
   counts_.misses = 0;
}

}  // namespace qa
