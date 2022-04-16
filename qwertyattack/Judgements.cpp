#include "Judgements.hpp"

#include <SFML/Graphics.hpp>
#include <deque>

#include "JudgementTally.hpp"
#include "common.hpp"

namespace qa {

Judgements::Judgements()
{
   great_texture_.loadFromFile(judgementGreatTextureFile);
   good_texture_.loadFromFile(judgementGoodTextureFile);
}

void Judgements::addJudgement(JudgementTally::Judgement judgement, float y, sf::Uint32 usElapsed)
{
   JudgementProperties &properties = judgements_.emplace_back();
   properties.initial_x = zoneLeftBound;
   properties.initial_y = y - judgementOffsetFromTrack;
   properties.usStart = usElapsed;
   switch (judgement) {
      case JudgementTally::Judgement::GREAT:
         properties.sprite.setTexture(great_texture_);
         break;
      case JudgementTally::Judgement::GOOD:
         properties.sprite.setTexture(good_texture_);
         break;
      default:
         // TODO: handle error
         break;
   }
   properties.sprite.setPosition(properties.initial_x, properties.initial_y);
}

void Judgements::update(sf::Uint32 usElapsed)
{
   while (!judgements_.empty() && judgements_.front().usStart + judgementDisplayDuration < usElapsed) {
      judgements_.pop_front();
   }
   for (auto &&judgement : judgements_) {
      float new_y = judgement.initial_y - (judgementFloatSpeed * (usElapsed - judgement.usStart));
      judgement.sprite.setPosition(judgement.initial_x, new_y);
   }
}

void Judgements::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
   for (auto &&judgement : judgements_) {
      target.draw(judgement.sprite);
   }
}

}  // namespace qa
