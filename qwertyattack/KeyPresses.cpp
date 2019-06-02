#include "KeyPresses.hpp"

namespace qa {

// ********************************************************************************
/// <summary>
/// Constructs a new instance of a KeyPresses, with no keys pressed
/// </summary>
/// <changed>tblock,2/20/2019</changed>
// ********************************************************************************
KeyPresses::KeyPresses() : pressMask_(0)
{
}

// ********************************************************************************
/// <summary>
/// Constructs a new instance of a KeyPresses, with the specified input mask
/// </summary>
/// <param name="mask">The input mask</param>
/// <changed>tblock,2/20/2019</changed>
// ********************************************************************************
KeyPresses::KeyPresses(sf::Int32 mask) : pressMask_(mask)
{
}

// ********************************************************************************
/// <summary>
/// Resets the KeyPresses mask to indicate that no keys were pressed
/// </summary>
/// <changed>tblock,2/20/2019</changed>
// ********************************************************************************
void KeyPresses::reset()
{
   pressMask_ = 0;
}

// ********************************************************************************
/// <summary>
/// Queries whether a character was pressed, as indicated by this KeyPresses instance
/// </summary>
/// <param name="i">The index being queried</param>
/// <returns>true if the key was pressed; false otherwise</returns>
/// <changed>tblock,2/20/2019</changed>
// ********************************************************************************
bool KeyPresses::isPressed(sf::Uint32 i) const
{
   return ((pressMask_ & (1 << i)) != 0);
}

// ********************************************************************************
/// <summary>
/// Queries whether a character was pressed, as indicated by this KeyPresses instance
/// </summary>
/// <param name="c">The character being queried</param>
/// <returns>true if the key was pressed, false otherwise</returns>
/// <changed>tblock,6/1/2019</changed>
// ********************************************************************************
bool KeyPresses::isPressed(char c) const
{
   return isPressed(static_cast<sf::Uint32>(c) - static_cast<sf::Uint32>('A'));
}

// ********************************************************************************
/// <summary>
/// Indicates that the key was pressed in this KeyPresses
/// </summary>
/// <param name="i">The index being set</param>
/// <changed>tblock,2/20/2019</changed>
// ********************************************************************************
void KeyPresses::setPressed(sf::Uint32 i)
{
   pressMask_ = pressMask_ | (1 << i);
}

// ********************************************************************************
/// <summary>
/// Indicates that the key was pressed in this KeyPresses
/// </summary>
/// <param name="c">The character being set</param>
/// <changed>tblock,6/1/2019</changed>
// ********************************************************************************
void KeyPresses::setPressed(char c)
{
   setPressed(static_cast<sf::Uint32>(c) - static_cast<sf::Uint32>('A'));
}

// ********************************************************************************
/// <summary>
/// Removes the pressed status of the key.  Used to acknowledge pressed status so that
/// only one KeyNote is destroyed for any given key press.
/// </summary>
/// <param name="i">The index being reset</param>
/// <changed>tblock,6/1/2019</changed>
// ********************************************************************************
void KeyPresses::resetPressed(sf::Uint32 i)
{
   pressMask_ = pressMask_ & ~(1 << i);
}

// ********************************************************************************
/// <summary>
/// Removes the pressed status of the key.  Used to acknowledge pressed status so that
/// only one KeyNote is destroyed for any given key press.
/// </summary>
/// <param name="c">The character being reset</param>
/// <changed>tblock,6/1/2019</changed>
// ********************************************************************************
void KeyPresses::resetPressed(char c)
{
   resetPressed(static_cast<sf::Uint32>(c) - static_cast<sf::Uint32>('A'));
}

}  // namespace qa
