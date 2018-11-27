#include "BasicKeyNote.hpp"

namespace qa {
// ********************************************************************************
/// <summary>
/// Constructor for BasicKeyNote
/// </summary>
/// <param name="c">The character</param>
/// <param name="speed">The speed at which the BasicKeyNote will travel (pixels/microsecond)</param>
/// <param name="targetHitTime">The time at which the corresponding key should be pressed</param>
/// <param name="pulseTexture">A pointer to the texture to be used for the "pulse" animation</param>
/// <param name="disappearTexture">A pointer to the texture to be used for the "disappear" animation</param>
/// <param name="explodeGreatTexture">A pointer to the texture to be used for the "explode" animation when hit with
/// GREAT timing</param> <param name="explodeGoodTexture">A pointer to the texture to be used for the "explode"
/// animation when hit with GOOD timing</param> <changed>tblock,11/17/2018</changed>
// ********************************************************************************
BasicKeyNote::BasicKeyNote(char c, float speed, sf::Int64 targetHitTime, std::shared_ptr<sf::Texture> pulseTexture,
                           std::shared_ptr<sf::Texture> disappearTexture,
                           std::shared_ptr<sf::Texture> explodeGreatTexture,
                           std::shared_ptr<sf::Texture> explodeGoodTexture)
    : state_(KeyNoteState::SCROLLING),
      key_(c),
      speed_(speed),
      targetHitTime_(targetHitTime),
      pulseTexture_(pulseTexture),
      disappearTexture_(disappearTexture),
      explodeGreatTexture_(explodeGreatTexture),
      explodeGoodTexture_(explodeGoodTexture)
{
   switch (c) {
      case 'Q':
      case 'W':
      case 'E':
      case 'R':
      case 'T':
      case 'Y':
      case 'U':
      case 'I':
      case 'O':
      case 'P':
         y_ = trackOffset + (0 * trackDistance);
         break;

      case 'A':
      case 'S':
      case 'D':
      case 'F':
      case 'G':
      case 'H':
      case 'J':
      case 'K':
      case 'L':
         y_ = trackOffset + (1 * trackDistance);
         break;

      case 'Z':
      case 'X':
      case 'C':
      case 'V':
      case 'B':
      case 'N':
      case 'M':
         y_ = trackOffset + (2 * trackDistance);
         break;
   }

   image_.setTexture(*pulseTexture_);
   image_.setTextureRect(sf::IntRect(leftOffset + ((key_ - 'A') * pixelsBetweenSprites), topOffset, width, height));
}

// ********************************************************************************
/// <summary>
/// Gets the state of the BasicKeyNote
/// </summary>
/// <returns>The state of the KeyNote</returns>
/// <changed>tblock,11/15/2018</changed>
// ********************************************************************************
KeyNoteState BasicKeyNote::getState() const
{
   return state_;
}

// ********************************************************************************
/// <summary>
/// Handles a key press from the user
/// </summary>
/// <param name="pressed">A bitmask indicating which keys were pressed</param>
/// <param name="timeElapsed">A (relative) time in microseconds that indicates when the key was pressed</param>
/// <returns>A GREAT or GOOD judgement if the note was hit, otherwise an empty optional</returns>
/// <changed>tblock,11/20/2018</changed>
// ********************************************************************************
std::optional<Judgement> BasicKeyNote::sendKey(std::bitset<NUM_KEYS> pressed, sf::Int64 timeElapsed)
{
   std::optional<Judgement> judgement;
   if (state_ == KeyNoteState::SCROLLING) {
      if (pressed.test(key_ - 'A')) {
         // compute frame differential from ideal
         sf::Int32 diffFrame = static_cast<sf::Int32>((timeElapsed - targetHitTime_) / diffMicrosecondInterval);
         if (diffFrame >= (-1 * diffFrameGood + 1) && diffFrame <= diffFrameGood + 1) {
            state_ = KeyNoteState::DISAPPEARING;
            hitTime_ = timeElapsed;
            image_.setPosition(zoneLeftBound, y_);
            image_.setTexture(*disappearTexture_);
            image_.setTextureRect(
                sf::IntRect(leftOffset + ((key_ - 'A') * pixelsBetweenSprites), topOffset, width, height));

            if (diffFrame >= (-1 * diffFrameGreat + 1) && diffFrame <= diffFrameGreat + 1) {
               judgement = Judgement::GREAT;
               explodeTexture_ = explodeGreatTexture_;
            }
            else {
               judgement = Judgement::GOOD;
               explodeTexture_ = explodeGoodTexture_;
            }
         }
      }
   }
   return judgement;
}

// ********************************************************************************
/// <summary>
/// Updates the image of the BasicKeyNote to the appropriate frame of its animation.  This function handles both
/// scrolling and hit animations.
/// </summary>
/// <param name="timeElapsed">A (relative) time in microseconds indicating time elapsed since some reference; used to
/// compute frame of the hit animation, or proper position during scrolling</param> <returns>A MISS judgement if the
/// note was missed, otherwise an empty optional</returns> <changed>tblock,11/20/2018</changed>
// ********************************************************************************
std::optional<Judgement> BasicKeyNote::updateFrame(sf::Int64 timeElapsed)
{
   std::optional<Judgement> result;
   if (state_ == KeyNoteState::SCROLLING) {
      if (image_.getPosition().x < deathBound) {
         state_ = KeyNoteState::DEAD;
         result = Judgement::MISS;
      }
      else {
         image_.setPosition((targetHitTime_ - timeElapsed) * speed_ + zoneLeftBound, y_);
         sf::Int32 frame = (static_cast<sf::Int32>(timeElapsed / microsecondsPerFrame)) % pulseFrames;
         image_.setTextureRect(sf::IntRect(leftOffset + ((key_ - 'A') * pixelsBetweenSprites),
                                           topOffset + frame * pixelsBetweenSprites, width, height));
      }
   }
   else if (state_ == KeyNoteState::DISAPPEARING) {
      sf::Int32 frame = (static_cast<sf::Int32>((timeElapsed - hitTime_) / microsecondsPerFrame));
      if (frame >= disappearFrames) {
         state_ = KeyNoteState::EXPLODING;
         image_.setTexture(*explodeTexture_);
         image_.setTextureRect(
             sf::IntRect(leftOffset + ((key_ - 'A') * pixelsBetweenSprites), topOffset, width, height));
      }
      else {
         image_.setTextureRect(sf::IntRect(leftOffset + ((key_ - 'A') * pixelsBetweenSprites),
                                           topOffset + frame * pixelsBetweenSprites, width, height));
      }
   }
   else if (state_ == KeyNoteState::EXPLODING) {
      sf::Int32 frame = (static_cast<sf::Int32>((timeElapsed - hitTime_) / microsecondsPerFrame)) - disappearFrames;
      if (frame >= explodeFrames) {
         state_ = KeyNoteState::DEAD;
      }
      else {
         image_.setTextureRect(sf::IntRect(leftOffset, topOffset + frame * pixelsBetweenSprites, width, height));
      }
   }
   return result;
}

// ********************************************************************************
/// <summary>
/// Draws the BasicKeyNote on a RenderTarget (Drawable interface requirement)
/// </summary>
/// <param name="target">The RenderTarget on which to draw the BasicKeyNote</param>
/// <param name="states">The RenderStates which control the render</param>
/// <changed>tblock,11/15/2018</changed>
// ********************************************************************************
void BasicKeyNote::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
   target.draw(image_);
}

}  // namespace qa