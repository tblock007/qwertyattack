#include "DataKeyNotes.hpp"

namespace qa {

// ********************************************************************************
/// <summary>
/// Updates the range of relevant KeyNotes.
/// </summary>
/// <changed>tblock,04/11/2022</changed>
// ********************************************************************************
void DataKeyNotes::updateDelimiters(sf::Uint32 usElapsed)
{
   // if a KeyNote has disappeared, there is no need to keep it in the range
   while (head_ < keys_.size() && usElapsed > disappearTimes_[head_]) {
      head_++;
   }
   // once a KeyNote is set to appear, it needs to be in range;
   // this is valid because KeyNotes should be sorted in order of appearTime
   while (tail_ < keys_.size() && usElapsed > appearTimes_[tail_]) {
      tail_++;
   }
}

// ********************************************************************************
/// <summary>
/// Updates the position of each KeyNote in the relevant range.
/// </summary>
/// <changed>tblock,04/11/2022</changed>
// ********************************************************************************
void DataKeyNotes::updatePositions(sf::Uint32 usElapsed)
{
   for (size_t i = head_; i < tail_; i++) {
      sf::Int64 usDiff = timeDiff(targetHitTimes_[i], usElapsed);
      xs_[i] = usDiff * speeds_[i] + zoneLeftBound;
      sprites_[i].setPosition(xs_[i], ys_[i]);
   }
}

// ********************************************************************************
/// <summary>
/// Updates the state of each KeyNote within the relevant range based on the
/// keys pressed, and updates the judgement tally.
/// </summary>
/// <changed>tblock,04/11/2022</changed>
// ********************************************************************************
void DataKeyNotes::updateStates(sf::Uint32 usElapsed, Judgements& judgements, JudgementTally& tally, KeyPresses& keys)
{
   for (size_t i = head_; i < tail_; i++) {
      if (usElapsed > missTimes_[i] && states_[i] == KeyNoteState::LIVE) {
         tally.incrementTally(Judgement::MISS);
         states_[i] = KeyNoteState::MISSED;
      }
      else if (keys.isPressed(keys_[i])) {
         sf::Int64 usDiff = timeDiff(targetHitTimes_[i], usElapsed);
         if (usDiff >= minMicrosecondGood && usDiff <= maxMicrosecondGood) {
            states_[i] = KeyNoteState::DEAD;  // TODO: set this to exploding animation

            if (usDiff >= minMicrosecondGreat && usDiff <= maxMicrosecondGreat) {
               judgements.addJudgement(Judgement::GREAT, ys_[i], usElapsed);
               tally.incrementTally(Judgement::GREAT);
            }
            else {
               judgements.addJudgement(Judgement::GOOD, ys_[i], usElapsed);
               tally.incrementTally(Judgement::GOOD);
            }
            keys.resetPressed(keys_[i]);
         }
      }
   }
}

// ********************************************************************************
/// <summary>
/// Draws each KeyNote within the relevant range to the target.
/// </summary>
/// <changed>tblock,04/11/2022</changed>
// ********************************************************************************
void DataKeyNotes::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   for (size_t i = head_; i < tail_; i++) {
      if (states_[i] != KeyNoteState::DEAD) {
         target.draw(sprites_[i]);
      }
   }
}

}  // namespace qa
