#include "DataKeyNotes.hpp"

namespace qa {

void DataKeyNotes::updateDelimiters(sf::Uint32 usElapsed)
{
   while (head_ < keys_.size() && usElapsed > disappearTimes_[head_]) {
      head_++;
   }

   while (tail_ < keys_.size() && usElapsed > appearTimes_[tail_]) {
      tail_++;
   }
}

void DataKeyNotes::updatePositions(sf::Uint32 usElapsed)
{
   for (size_t i = head_; i < tail_; i++) {
      sf::Int64 usDiff = timeDiff(targetHitTimes_[i], usElapsed);
      xs_[i] = usDiff * speeds_[i] + zoneLeftBound;
      sprites_[i].setPosition(xs_[i], ys_[i]);
   }
}

void DataKeyNotes::updateStates(sf::Uint32 usElapsed, JudgementTally& tally, KeyPresses& keys)
{
   for (size_t i = head_; i < tail_; i++) {
      if (usElapsed > missTimes_[i] && states_[i] == KeyNoteState::LIVE) {
         tally.incrementTally(Judgement::MISS);
         states_[i] = KeyNoteState::MISSED;
      }
      else if (keys.isPressed(keys_[i])) {
         sf::Int64 usDiff = timeDiff(targetHitTimes_[i], usElapsed);
         if (usDiff >= minMicrosecondGood && usDiff <= maxMicrosecondGood) {
            hitTimes_[i] = usElapsed;
            states_[i] = KeyNoteState::DEAD;  // TODO: set this to exploding animation

            if (usDiff >= minMicrosecondGreat && usDiff <= maxMicrosecondGreat) {
               tally.incrementTally(Judgement::GREAT);
            }
            else {
               tally.incrementTally(Judgement::GOOD);
            }

            // sprites_[i].setTexture(explodeTexture);
            // sprites_[i].setTextureRect(
            //    sf::IntRect(leftOffset + ((keys_[i] - 'A') * pixelsBetweenSprites), topOffset, width, height));

            keys.resetPressed(keys_[i]);
         }
      }
   }
}
void DataKeyNotes::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   for (size_t i = head_; i < tail_; i++) {
      if (states_[i] != KeyNoteState::DEAD) {
         target.draw(sprites_[i]);
      }
   }
}

}  // namespace qa
