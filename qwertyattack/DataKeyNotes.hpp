#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "JudgementTally.hpp"
#include "Judgements.hpp"
#include "KeyPresses.hpp"

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
   // ********************************************************************************
   /// <summary>
   /// Possible states for a KeyNote.
   /// </summary>
   // ********************************************************************************
   enum class State { LIVE, DEAD, DISAPPEARING, MISSED, SEQUENCE_IN_PROGRESS };

   // ********************************************************************************
   /// <summary>
   /// Updates the range of relevant KeyNotes.
   /// </summary>
   /// <param name="usElapsed">The time at which this update is occurring.</param>
   // ********************************************************************************
   void updateDelimiters(sf::Uint32 usElapsed);

   // ********************************************************************************
   /// <summary>
   /// Updates the position of each KeyNote in the relevant range.
   /// </summary>
   /// <param name="usElapsed">The time at which this update is occurring.</param>
   // ********************************************************************************
   void updatePositions(sf::Uint32 usElapsed);

   // ********************************************************************************
   /// <summary>
   /// Updates the state of each KeyNote within the relevant range based on the
   /// keys pressed, and updates the judgement tally.
   /// </summary>
   /// <param name="usElapsed">The time at which this update is occurring.</param>
   /// <param name="judgements">The object to which to add Judgements to be drawn.</param>
   /// <param name="tally">The tally of Judgements.</param>
   /// <param name="keys">The keys that have been pressed by the user.</param>
   // ********************************************************************************
   void updateStates(sf::Uint32 usElapsed, Judgements& judgements, JudgementTally& tally, KeyPresses& keys);

   // ********************************************************************************
   /// <summary>
   /// Draws each KeyNote within the relevant range to the target.
   /// </summary>
   /// <param name="target">The target on which the judgements should be drawn.</param>
   /// <param name="states">Indicates global states applied to drawn objects.</param>
   // ********************************************************************************
   void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  private:
   // Allows the KeyChart object to initialize the data.
   friend class KeyChart;

   // The head and tail indices of the relevant range of the KeyNotes (i.e., the KeyNotes
   // close enough to being displayed are [head, tail)). The main game loop only needs to
   // render and process this range.
   size_t head_ = 0;
   size_t tail_ = 0;

   // The positions and speeds of each KeyNote.
   std::vector<float> xs_;
   std::vector<float> ys_;
   std::vector<float> speeds_;

   // The times when each KeyNote is supposed to be hit.
   std::vector<sf::Uint32> usHitTarget_;

   // The times when each KeyNote will "appear" (although they may be rendered off-screen).
   std::vector<sf::Uint32> usAppearance_;

   // The times when each KeyNote will disappear (assuming it is missed).
   std::vector<sf::Uint32> usDisappearance_;

   // The times beyond which each KeyNote is considered to be "missed".
   // This could be computed from the timing window and the targetHitTime, but is
   // denormalized and stored here to save computation in the main loop.
   std::vector<sf::Uint32> usMiss_;

   // The state of each KeyNote
   std::vector<State> states_;

   // The character that the KeyNote wants the user to press.
   std::vector<char> keys_;

   // The sprites that are drawn to represent the KeyNote.
   std::vector<sf::Sprite> sprites_;
};
}  // namespace qa
