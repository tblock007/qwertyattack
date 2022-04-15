#pragma once
#include <SFML/System.hpp>
#include <deque>
#include "SFML/Graphics.hpp"
#include "common.hpp"

namespace qa {
// --------------------------------------------------------------------------------
/// <summary>
/// Container of judgements to be displayed on the screen.
/// </summary>
// --------------------------------------------------------------------------------
class Judgements : public sf::Drawable {
  public:
   Judgements();
   void addJudgement(Judgement judgement, float y, sf::Uint32 usElapsed);
   void update(sf::Uint32 usElapsed);
   void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  private:
   // Captures all relevant information about a judgement
   struct JudgementProperties {
      float initial_x;
      float initial_y;
      sf::Uint32 startTime;
      sf::Sprite sprite;
   };

   std::deque<JudgementProperties> judgements_;
   sf::Texture great_texture_;
   sf::Texture good_texture_;
};
}  // namespace qa
