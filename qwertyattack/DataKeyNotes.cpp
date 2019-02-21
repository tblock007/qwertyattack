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

void DataKeyNotes::updatePositions(sf::Uint32 usElapsed, JudgementTally& tally)
{
   for (size_t i = head_; i < tail_; i++) {
      xs_[i] = (targetHitTimes_[i] - usElapsed) * speeds_[i] + zoneLeftBound;
      sprites_[i].setPosition(xs_[i], ys_[i]);
   }
}

void DataKeyNotes::updateStates(sf::Uint32 usElapsed, KeyPresses keys, JudgementTally& tally)
{
   for (size_t i = head_; i < tail_; i++) {
      if (keys.isPressed(static_cast<sf::Uint32>(keys_[i] - 'A'))) {
         sf::Uint32 usDiff = usElapsed - targetHitTimes_[i];
         if (usDiff >= minMicrosecondGood && usDiff <= maxMicrosecondGood) {

            hitTimes_[i] = usElapsed;

            if (usDiff >= minMicrosecondGreat && usDiff <= maxMicrosecondGreat) {
               tally.incrementTally(Judgement::GREAT);
            }
            else {
               tally.incrementTally(Judgement::GOOD);
            }

            // sprites_[i].setTexture(explodeTexture);
			// sprites_[i].setTextureRect(
            //    sf::IntRect(leftOffset + ((keys_[i] - 'A') * pixelsBetweenSprites), topOffset, width, height));
         }
      }
   }
}
void DataKeyNotes::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
   for (size_t i = head_; i < tail_; i++) {
      target.draw(sprites_[i]);
   }
}

}  // namespace qa
