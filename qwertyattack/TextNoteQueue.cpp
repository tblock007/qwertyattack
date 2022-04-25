#include "TextNoteQueue.hpp"

#include <SFML/Graphics.hpp>
#include <deque>

#include "TextNote.hpp"

namespace qa {

void TextNoteQueue::addTextNote(std::string const& text, sf::Uint32 start_time, sf::Uint32 end_time)
{
   notes_.emplace_back(text, start_time, end_time);
}

void TextNoteQueue::update(sf::Uint32 usElapsed, Judgements& judgements, JudgementTally& tally, KeyPresses& keys)
{
   if (!notes_.empty()) {
      notes_.front().update(usElapsed, judgements, tally, keys);
      if (notes_.front().isExpired()) {
         notes_.pop_front();
      }
   }
}

void TextNoteQueue::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
   if (!notes_.empty() && notes_.front().isActive()) {
      target.draw(notes_.front());
   }
}

}  // namespace qa
