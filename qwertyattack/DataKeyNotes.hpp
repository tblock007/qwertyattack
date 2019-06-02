#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "common.hpp"
#include "JudgementTally.hpp"
#include "KeyPresses.hpp"

namespace qa {
// --------------------------------------------------------------------------------
/// <summary>
/// Aggregates all data needed to represent a KeyNote in structure-of-arrays style
/// </summary>
// --------------------------------------------------------------------------------
class DataKeyNotes : public sf::Drawable {
  public:
   void updateDelimiters(sf::Uint32 usElapsed);
   void updatePositions(sf::Uint32 usElapsed, JudgementTally& tally);
   void updateStates(sf::Uint32 usElapsed, JudgementTally& tally, KeyPresses& keys);
   void draw(sf::RenderTarget &target, sf::RenderStates states) const;
   

  private:

	  friend class KeyChart;

   size_t head_ = 0;
   size_t tail_ = 0;
   std::vector<float> xs_;
   std::vector<float> ys_;
   std::vector<float> speeds_;
   std::vector<sf::Uint32> hitTimes_;
   std::vector<sf::Uint32> targetHitTimes_;
   std::vector<sf::Uint32> appearTimes_;
   std::vector<sf::Uint32> disappearTimes_;
   std::vector<sf::Uint32> missTimes_;

   std::vector<KeyNoteState> states_;
   std::vector<char> keys_;

   std::vector<sf::Sprite> sprites_;

};
}  // namespace qa
