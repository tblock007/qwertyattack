#pragma once
#include <vector>
#include "JudgementTally.hpp"
#include "KeyPresses.hpp"
#include "SFML/Graphics.hpp"
#include "common.hpp"

namespace qa {
// --------------------------------------------------------------------------------
/// <summary>
/// Aggregates all data needed to represent a KeyNote in structure-of-arrays style.
///
/// Holds KeyNote properties such as position, speed, event times, and sprites.
/// Provides functions to update these properties, and to render them to a
/// RenderTarget.
/// </summary>
// --------------------------------------------------------------------------------
class DataKeyNotes : public sf::Drawable {
  public:
   void updateDelimiters(sf::Uint32 usElapsed);
   void updatePositions(sf::Uint32 usElapsed);
   void updateStates(sf::Uint32 usElapsed, JudgementTally& tally, KeyPresses& keys);
   void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  private:
   friend class KeyChart;

   // the head and tail indices (inclusive) of the relevant range of the KeyNotes (i.e.,
   // those close enough to being displayed); the main game loop only needs to render and
   // process this range
   size_t head_ = 0;
   size_t tail_ = 0;

   // the position and speed of each KeyNote
   std::vector<float> xs_;
   std::vector<float> ys_;
   std::vector<float> speeds_;

   // the times when each KeyNote is supposed to be hit
   std::vector<sf::Uint32> targetHitTimes_;

   // the times when each KeyNote will "appear" (although they may be rendered off-screen)
   std::vector<sf::Uint32> appearTimes_;

   // the times when each KeyNote will disappear (assuming it is missed)
   std::vector<sf::Uint32> disappearTimes_;

   // the times beyond which each KeyNote is considered to be "missed"
   // this can be computed from the timing window and the targetHitTime, but is
   // denormalized and stored here to save computation in the main loop
   std::vector<sf::Uint32> missTimes_;

   // the state of each KeyNote
   std::vector<KeyNoteState> states_;

   // the character that the KeyNote wants the user to press
   std::vector<char> keys_;

   // the sprites that are drawn to represent the KeyNote
   std::vector<sf::Sprite> sprites_;
};
}  // namespace qa
