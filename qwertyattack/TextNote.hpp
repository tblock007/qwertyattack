#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "Judgements.hpp"
#include "JudgementTally.hpp"
#include "KeyPresses.hpp"

namespace qa {
// --------------------------------------------------------------------------------
/// <summary>
/// Represents a TextNote, a gameplay element in which the user needs to type a
/// string without timing constraints.
/// </summary>
// --------------------------------------------------------------------------------
class TextNote : public sf::Drawable {
  public:
   // ********************************************************************************
   /// <summary>
   /// Possible states for a TextNote.
   /// </summary>
   // ********************************************************************************
   enum class TextNoteState { INACTIVE, ACTIVE, EXPIRED };

   // ********************************************************************************
   /// <summary>
   /// Constructs a TextNote with the given target text.
   /// </summary>
   /// <param name="text">The text that the user must type for this TextNote.</param>
   /// <param name="start_time">The start of the time window for this TextNote.</param>
   /// <param name="end_time">The end of the time window for this TextNote.</param>
   // ********************************************************************************
   TextNote(std::string const& text, sf::Uint32 start_time, sf::Uint32 end_time);

   // ********************************************************************************
   /// <summary>
   /// Updates the TextNote, checking for expiry and for any progress made by the user.
   /// </summary>
   /// <param name="usElapsed">The time at which the update is occurring.</param>
   /// <param name="judgements">The object to which to add Judgements to be drawn.</param>
   /// <param name="tally">The tally of Judgements.</param>
   /// <param name="keys">The keys that have been pressed by the user.</param>
   // ********************************************************************************
   void update(sf::Uint32 usElapsed, Judgements& judgements, JudgementTally& tally, KeyPresses& keys);

   // ********************************************************************************
   /// <summary>
   /// Draws the TextNote to the screen.
   /// </summary>
   /// <param name="target">The target on which the TextNote should be drawn.</param>
   /// <param name="states">Indicates global states applied to drawn objects.</param>
   // ********************************************************************************
   void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   // ********************************************************************************
   /// <summary>
   /// Returns whether the TextNote is active.
   /// </summary>
   /// <returns>true iff the TextNote is still active.</returns>
   // ********************************************************************************
   bool isActive() const;

   // ********************************************************************************
   /// <summary>
   /// Returns whether the TextNote is expired.
   /// </summary>
   /// <returns>true iff the TextNote is still expired.</returns>
   // ********************************************************************************
   bool isExpired() const;

  private:
   // The time window in which the user must type the target text.
   sf::Uint32 start_time_;
   sf::Uint32 end_time_;

   // Display elements.
   sf::RectangleShape back_bar_;
   sf::RectangleShape remaining_bar_;
   sf::Font font_;
   sf::Text text_;
   sf::Text next_text_;

   // The index of the next character to be typed.
   sf::Int32 next_;

   // Indicates that stage of the TextNote's lifecycle.
   TextNoteState state_;
};
}  // namespace qa
