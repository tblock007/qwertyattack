#pragma once
#include "common.hpp"

namespace qa {
// --------------------------------------------------------------------------------
/// <summary>
/// A bitmask that represents whether the corresponding key was pressed in this frame.
/// 'a' is mapped to the LSB, and 'z' is mapped to the 25th bit
/// </summary>
// --------------------------------------------------------------------------------
class KeyPresses {
  public:
   KeyPresses();
   explicit KeyPresses(sf::Int32 mask);

   void reset();
   [[nodiscard]] bool isPressed(sf::Uint32 i) const;
   void setPressed(sf::Uint32 i);

  private:
   sf::Int32 pressMask_;
};
}  // namespace qa
