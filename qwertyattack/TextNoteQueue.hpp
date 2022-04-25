#pragma once
#include <SFML/Graphics.hpp>
#include <deque>

#include "TextNote.hpp"

namespace qa {
// --------------------------------------------------------------------------------
/// <summary>
/// Container of TextNotes arranged in order of appearance.
/// </summary>
// --------------------------------------------------------------------------------
class TextNoteQueue : public sf::Drawable {
  public:
   // ********************************************************************************
   /// <summary>
   /// Adds a TextNote to the TextNoteQueue.
   /// </summary>
   /// <param name="text">The text of the TextNote to be added.</param>
   /// <param name="start_time">The start time of the TextNote to be added.</param>
   /// <param name="end_time">The end time of the TextNote to be added.</param>
   // ********************************************************************************
   void addTextNote(std::string const& text, sf::Uint32 start_time, sf::Uint32 end_time);

   // ********************************************************************************
   /// <summary>
   /// Updates the TextNoteQueue.
   /// </summary>
   /// <param name="usElapsed">The time at which the update is occurring.</param>
   /// <param name="judgements">The object to which to add Judgements to be drawn.</param>
   /// <param name="tally">The tally of Judgements.</param>
   /// <param name="keys">The keys that have been pressed by the user.</param>
   // ********************************************************************************
   void update(sf::Uint32 usElapsed, Judgements& judgements, JudgementTally& tally, KeyPresses& keys);

   // ********************************************************************************
   /// <summary>
   /// Draws the first TextNote to the screen if it is active.
   /// </summary>
   /// <param name="target">The target on which the TextNote should be drawn.</param>
   /// <param name="states">Indicates global states applied to drawn objects.</param>
   // ********************************************************************************
   void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  private:
   std::deque<TextNote> notes_;
};
}  // namespace qa
