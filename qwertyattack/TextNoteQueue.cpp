#include "TextNoteQueue.hpp"

#include <SFML/Graphics.hpp>
#include <deque>

#include "TextNote.hpp"

namespace qa {

void TextNoteQueue::addTextNote(std::string const& text, sf::Uint32 startTime, sf::Uint32 endTime)
{
   notes_.emplace_back(text, startTime, endTime);
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
