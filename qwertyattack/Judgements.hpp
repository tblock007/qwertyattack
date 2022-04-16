#pragma once
#include <SFML/Graphics.hpp>
#include <deque>

#include "JudgementTally.hpp"

namespace qa {
// --------------------------------------------------------------------------------
/// <summary>
/// Container of judgements to be displayed on the screen.
/// </summary>
// --------------------------------------------------------------------------------
class Judgements : public sf::Drawable {
  public:
   // ********************************************************************************
   /// <summary>
   /// Constructs the Judgements object while loading the texture for the judgements.
   /// </summary>
   // ********************************************************************************
   Judgements();

   // ********************************************************************************
   /// <summary>
   /// Adds a judgement to be displayed.
   /// </summary>
   /// <param name="judgement">The judgement (GREAT or GOOD).</param>
   /// <param name="y">The y-position of the KeyNote that was hit.</param>
   /// <param name="usElapsed">The time at which the judgement occurred.</param>
   // ********************************************************************************
   void addJudgement(JudgementTally::Judgement judgement, float y, sf::Uint32 usElapsed);

   // ********************************************************************************
   /// <summary>
   /// Updates all judgements, adjusting position and removing expired judgements.
   /// </summary>
   /// <param name="usElapsed">The time at which the update is occurring.</param>
   // ********************************************************************************
   void update(sf::Uint32 usElapsed);

   // ********************************************************************************
   /// <summary>
   /// Draws all judgements to the screen.
   /// </summary>
   /// <param name="target">The target on which the judgements should be drawn.</param>
   /// <param name="states">Indicates global states applied to drawn objects.</param>
   // ********************************************************************************
   void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  private:
   // Captures all relevant information about a judgement
   struct JudgementProperties {
      float initial_x;
      float initial_y;
      sf::Uint32 usStart;
      sf::Sprite sprite;
   };

   // Holds the judgements being displayed.
   std::deque<JudgementProperties> judgements_;

   // Preloaded textures for displaying the judgements.
   sf::Texture great_texture_;
   sf::Texture good_texture_;
};
}  // namespace qa
