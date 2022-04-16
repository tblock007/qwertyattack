#include "DataKeyNotes.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

#include "JudgementTally.hpp"
#include "Judgements.hpp"
#include "KeyPresses.hpp"

namespace qa {

void DataKeyNotes::updateDelimiters(sf::Uint32 usElapsed)
{
   // If a KeyNote has disappeared, there is no need to keep it in the range.
   while (head_ < keys_.size() && usElapsed > usDisappearance_[head_]) {
      head_++;
   }
   // Once a KeyNote is set to appear, it needs to be in range.
   // This is valid because KeyNotes should be sorted in order of appearTime.
   while (tail_ < keys_.size() && usElapsed > usAppearance_[tail_]) {
      tail_++;
   }
}

void DataKeyNotes::updatePositions(sf::Uint32 usElapsed)
{
   for (size_t i = head_; i < tail_; i++) {
      sf::Int64 usDiff = timeDiff(usHitTarget_[i], usElapsed);
      xs_[i] = usDiff * speeds_[i] + zoneLeftBound;
      sprites_[i].setPosition(xs_[i], ys_[i]);
   }
}

void DataKeyNotes::updateStates(sf::Uint32 usElapsed, Judgements& judgements, JudgementTally& tally, KeyPresses& keys)
{
   for (size_t i = head_; i < tail_; i++) {
      if (usElapsed > usMiss_[i] && states_[i] == State::LIVE) {
         tally.incrementTally(JudgementTally::Judgement::MISS);
         states_[i] = State::MISSED;
      }
      else if (keys.isPressed(keys_[i])) {
         sf::Int64 usDiff = timeDiff(usHitTarget_[i], usElapsed);
         if (usDiff >= minMicrosecondGood && usDiff <= maxMicrosecondGood) {
            states_[i] = State::DEAD;

            if (usDiff >= minMicrosecondGreat && usDiff <= maxMicrosecondGreat) {
               judgements.addJudgement(JudgementTally::Judgement::GREAT, ys_[i], usElapsed);
               tally.incrementTally(JudgementTally::Judgement::GREAT);
            }
            else {
               judgements.addJudgement(JudgementTally::Judgement::GOOD, ys_[i], usElapsed);
               tally.incrementTally(JudgementTally::Judgement::GOOD);
            }
            keys.resetPressed(keys_[i]);
         }
      }
   }
}

void DataKeyNotes::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   for (size_t i = head_; i < tail_; i++) {
      if (states_[i] != State::DEAD) {
         target.draw(sprites_[i]);
      }
   }
}

}  // namespace qa
