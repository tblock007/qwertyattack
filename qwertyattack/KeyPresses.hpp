#pragma once
#include <SFML/Config.hpp>

#include "constants.hpp"

namespace qa {
// --------------------------------------------------------------------------------
/// <summary>
/// A bitmask that represents whether the corresponding key was pressed in this frame.
/// 'A' is mapped to the LSB, and 'Z' is mapped to the 25th bit.
/// </summary>
// --------------------------------------------------------------------------------
class KeyPresses {
  public:
   // ********************************************************************************
   /// <summary>
   /// Constructs a new instance of a KeyPresses, with no keys pressed.
   /// </summary>
   // ********************************************************************************
   KeyPresses();

   // ********************************************************************************
   /// <summary>
   /// Constructs a new instance of a KeyPresses, with the specified input mask.
   /// </summary>
   /// <param name="mask">The input mask.</param>
   // ********************************************************************************
   explicit KeyPresses(sf::Uint32 mask);

   // ********************************************************************************
   /// <summary>
   /// Resets the KeyPresses mask to indicate that no keys were pressed.
   /// </summary>
   // ********************************************************************************
   void reset();

   // ********************************************************************************
   /// <summary>
   /// Queries whether a character was pressed, as indicated by this KeyPresses instance
   /// </summary>
   /// <param name="i">The index being queried.</param>
   /// <returns>true if the key was pressed; false otherwise.</returns>
   // ********************************************************************************
   [[nodiscard]] bool isPressed(sf::Int32 i) const;

   // ********************************************************************************
   /// <summary>
   /// Queries whether a character was pressed, as indicated by this KeyPresses instance
   /// </summary>
   /// <param name="c">The character being queried.</param>
   /// <returns>true if the key was pressed, false otherwise.</returns>
   // ********************************************************************************
   [[nodiscard]] bool isPressed(char c) const;

   // ********************************************************************************
   /// <summary>
   /// Indicates that the key was pressed in this KeyPresses.
   /// </summary>
   /// <param name="i">The index being set.</param>
   // ********************************************************************************
   void setPressed(sf::Int32 i);

   // ********************************************************************************
   /// <summary>
   /// Indicates that the key was pressed in this KeyPresses.
   /// </summary>
   /// <param name="c">The character being set.</param>
   // ********************************************************************************
   void setPressed(char c);

   // ********************************************************************************
   /// <summary>
   /// Removes the pressed status of the key.  Used to acknowledge pressed status so that
   /// only one KeyNote is destroyed for any given key press.
   /// </summary>
   /// <param name="i">The index being reset.</param>
   // ********************************************************************************
   void resetPressed(sf::Int32 i);

   // ********************************************************************************
   /// <summary>
   /// Removes the pressed status of the key.  Used to acknowledge pressed status so that
   /// only one KeyNote is destroyed for any given key press.
   /// </summary>
   /// <param name="c">The character being reset.</param>
   // ********************************************************************************
   void resetPressed(char c);

  private:
   sf::Uint32 pressMask_;
};
}  // namespace qa
