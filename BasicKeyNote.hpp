#pragma once
#include <SFML/Graphics.hpp>
#include <bitset>
#include <memory>
#include "KeyNote.hpp"
#include "common.hpp"

namespace qa {
// --------------------------------------------------------------------------------
/// <summary>
/// Represents a basic KeyNote, which only requires a single keypress from the player
///
/// Implements the Drawable interface, allowing it to be drawn on a RenderTarget
/// </summary>
// --------------------------------------------------------------------------------
class BasicKeyNote : public KeyNote {
  public:
   BasicKeyNote(char c, float speed, sf::Int64 targetHitTime, std::shared_ptr<sf::Texture> pulseTexture,
                std::shared_ptr<sf::Texture> disappearTexture, std::shared_ptr<sf::Texture> explodeGreatTexture,
                std::shared_ptr<sf::Texture> explodeGoodTexture);

   KeyNoteState getState() const override;

   std::optional<Judgement> sendKey(std::bitset<NUM_KEYS> pressed, sf::Int64 timeElapsed) override;

   std::optional<Judgement> updateFrame(sf::Int64 timeElapsed) override;

   void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  private:
   KeyNoteState state_;
   char key_;

   float speed_;
   float y_;

   sf::Sprite image_;
   sf::Int64 hitTime_;
   sf::Int64 targetHitTime_;

   std::shared_ptr<sf::Texture> pulseTexture_;
   std::shared_ptr<sf::Texture> disappearTexture_;
   std::shared_ptr<sf::Texture> explodeTexture_;
   std::shared_ptr<sf::Texture> explodeGreatTexture_;
   std::shared_ptr<sf::Texture> explodeGoodTexture_;
};
}  // namespace qa