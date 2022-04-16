#pragma once
#include <SFML/Config.hpp>

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
   // ********************************************************************************
   /// <summary>
   /// Possible judgements, representing the accuracy of the user when hitting a
   /// KeyNote.
   /// </summary>
   // ********************************************************************************
   enum class Judgement { GREAT, GOOD, MISS };

   // ********************************************************************************
   /// <summary>
   /// Constructs a new instance of a JudgementTally, with all counts initialized to zero
   /// </summary>
   // ********************************************************************************
   JudgementTally();

   // ********************************************************************************
   /// <summary>
   /// Returns the tallies that have been counted thus far.
   /// </summary>
   /// <returns>The number of GREATs, the number of GOODs, the number of MISSes.</returns>
   // ********************************************************************************
   [[nodiscard]] TallyCounts getTallies() const;

   // ********************************************************************************
   /// <summary>
   /// Increments the appropriate tally given an input judgement.
   /// </summary>
   /// <param name="judgement">The received judgement whose count is to be incremented.</param>
   // ********************************************************************************
   void incrementTally(Judgement judgement);

   // ********************************************************************************
   /// <summary>
   /// Resets the counts of this JudgementTally to zero.
   /// </summary>
   // ********************************************************************************
   void reset();

  private:
   // The accumulated judgement counts.
   TallyCounts counts_;
};
}  // namespace qa
