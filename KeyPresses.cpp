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
/// Indicates that the key was pressed in this KeyPresses
/// </summary>
/// <param name="i">The index being set</param>
/// <changed>tblock,2/20/2019</changed>
// ********************************************************************************
void KeyPresses::setPressed(sf::Uint32 i)
{
   pressMask_ = pressMask_ | (1 << i);
}

}  // namespace qa
