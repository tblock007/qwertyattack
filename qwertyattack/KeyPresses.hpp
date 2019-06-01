#pragma once
#include "common.hpp"

namespace qa {
// --------------------------------------------------------------------------------
/// <summary>
/// A bitmask that represents whether the corresponding key was pressed in this frame.
/// 'A' is mapped to the LSB, and 'Z' is mapped to the 25th bit
/// </summary>
// --------------------------------------------------------------------------------
class KeyPresses {
  public:
   KeyPresses();
   explicit KeyPresses(sf::Int32 mask);

   void reset();
   [[nodiscard]] bool isPressed(sf::Uint32 i) const;
   [[nodiscard]] bool isPressed(char c) const;

   void setPressed(sf::Uint32 i);
   void setPressed(char c);
   void resetPressed(sf::Uint32 i);
   void resetPressed(char c);

  private:
   sf::Int32 pressMask_;
};
}  // namespace qa
