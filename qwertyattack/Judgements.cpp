#include <iostream>
#include "Judgements.hpp"

namespace qa {
// ********************************************************************************
/// <summary>
/// Constructs the Judgements object while loading the texture for the judgements.
/// </summary>
/// <changed>tblock,04/14/2022</changed>
// ********************************************************************************
Judgements::Judgements()
{
   great_texture_.loadFromFile(judgementGreatTextureFile);
   good_texture_.loadFromFile(judgementGoodTextureFile);
}

// ********************************************************************************
/// <summary>
/// Adds a judgement to be displayed.
/// </summary>
/// <param name="judgement">The judgement (GREAT or GOOD)</param>
/// <param name="y">The y-position of the KeyNote that was hit</param>
/// <param name="usElapsed">The time at which the judgement occurred</param>
/// <changed>tblock,04/14/2022</changed>
// ********************************************************************************
void Judgements::addJudgement(Judgement judgement, float y, sf::Uint32 usElapsed)
{
   JudgementProperties &properties = judgements_.emplace_back();
   properties.initial_x = zoneLeftBound;
   properties.initial_y = y - judgementOffsetFromTrack;
   properties.startTime = usElapsed;
   switch (judgement) {
      case Judgement::GREAT:
         properties.sprite.setTexture(great_texture_);
         break;
      case Judgement::GOOD:
         properties.sprite.setTexture(good_texture_);
         break;
      default:
          // error
         break;
   }

   properties.sprite.setPosition(properties.initial_x, properties.initial_y);
}

// ********************************************************************************
/// <summary>
/// Updates all judgements, adjusting position and removing expired judgements.
/// </summary>
/// <param name="usElapsed">The time at which the update is occurring</param>
/// <changed>tblock,04/14/2022</changed>
// ********************************************************************************
void Judgements::update(sf::Uint32 usElapsed)
{
   while (!judgements_.empty() && judgements_.front().startTime + judgementDisplayDuration < usElapsed) {
      judgements_.pop_front();
   }
   for (auto &&judgement : judgements_) {
      float new_y = judgement.initial_y - (judgementFloatSpeed * (usElapsed - judgement.startTime));
      judgement.sprite.setPosition(judgement.initial_x, new_y);
   }
}

// ********************************************************************************
/// <summary>
/// Draws all judgements to the screen
/// </summary>
/// <param name="target">The target on which the judgements should be drawn</param>
/// <param name="states">Indicates global states applied to drawn objects</param>
/// <changed>tblock,04/14/2022</changed>
// ********************************************************************************
void Judgements::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   for (auto &&judgement : judgements_) {
      target.draw(judgement.sprite);
   }
}

}  // namespace qa
