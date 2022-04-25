#include "TextNote.hpp"

#include <SFML/Graphics.hpp>
#include <string>
#include <utility>
#include <cctype>

#include "JudgementTally.hpp"
#include "KeyPresses.hpp"
#include "TextNote.hpp"
#include "constants.hpp"

namespace qa {

TextNote::TextNote(std::string const& text, sf::Uint32 start_time, sf::Uint32 end_time)
    : start_time_(start_time),
      end_time_(end_time),
      back_bar_({textNoteWidth, textNoteHeight}),
      remaining_bar_({textNoteWidth, textNoteHeight}),
      next_(0),
      is_active_(true)
{
   back_bar_.setPosition({textNoteLeftBound, textNoteTopBound});
   back_bar_.setFillColor(sf::Color(200, 200, 200));

   remaining_bar_.setPosition({textNoteLeftBound, textNoteTopBound});
   remaining_bar_.setFillColor(sf::Color(0, 200, 255));

   font_.loadFromFile("resources/sansation.ttf");
   text_.setString(text);
   text_.setFont(font_);
   text_.setFillColor(sf::Color::Black);
   text_.setPosition(textNoteLeftBound + textNoteLeftPadding, textNoteTopBound + textNoteTopPadding);
   text_.setCharacterSize(textNoteCharacterSize);
   if (!text.empty()) {
      next_text_.setString(text[next_]);
      next_text_.setFont(font_);
      next_text_.setStyle(sf::Text::Underlined);
      next_text_.setFillColor(sf::Color::Red);
      next_text_.setPosition(text_.findCharacterPos(next_));
      next_text_.setCharacterSize(textNoteCharacterSize);
   }
}

void TextNote::update(sf::Uint32 usElapsed, Judgements& judgements, JudgementTally& tally, KeyPresses& keys)
{
   sf::String const& s = text_.getString();
   if (char c = s[next_]; keys.isPressed(c)) {
      next_++;
      while (std::isspace(s[next_])) {
         next_++;
      }

      if (next_ >= s.getSize()) {
         judgements.addJudgement(JudgementTally::Judgement::GREAT, textNoteTopBound, usElapsed);
         tally.incrementTally(JudgementTally::Judgement::GREAT);
         is_active_ = false;
      }
      else {
         next_text_.setString(s[next_]);
         next_text_.setPosition(text_.findCharacterPos(next_));
      }

      keys.resetPressed(c);
   }
   
   if (usElapsed < end_time_) {
      float fraction = static_cast<float>(end_time_ - usElapsed) / static_cast<float>(end_time_ - start_time_);
      remaining_bar_.setScale(fraction, 1.0f);
   }
   else {
      judgements.addJudgement(JudgementTally::Judgement::MISS, textNoteTopBound, usElapsed);
      tally.incrementTally(JudgementTally::Judgement::MISS);
      is_active_ = false;
   }
}

void TextNote::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   target.draw(back_bar_, states);
   target.draw(remaining_bar_, states);
   target.draw(text_, states);
   target.draw(next_text_, states);
}

bool TextNote::isActive() const
{
   return is_active_;
}

}  // namespace qa
