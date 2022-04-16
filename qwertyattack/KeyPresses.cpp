#include "KeyPresses.hpp"

#include <SFML/Config.hpp>

#include "constants.hpp"

namespace qa {

KeyPresses::KeyPresses() : pressMask_(0)
{
}

KeyPresses::KeyPresses(sf::Uint32 mask) : pressMask_(mask)
{
}

void KeyPresses::reset()
{
   pressMask_ = 0;
}

bool KeyPresses::isPressed(sf::Int32 i) const
{
   return ((pressMask_ & (1 << i)) != 0);
}

bool KeyPresses::isPressed(char c) const
{
   return isPressed(static_cast<sf::Int32>(c) - static_cast<sf::Int32>('A'));
}

void KeyPresses::setPressed(sf::Int32 i)
{
   pressMask_ = pressMask_ | (1 << i);
}

void KeyPresses::setPressed(char c)
{
   setPressed(static_cast<sf::Int32>(c) - static_cast<sf::Int32>('A'));
}

void KeyPresses::resetPressed(sf::Int32 i)
{
   pressMask_ = pressMask_ & ~(1 << i);
}

void KeyPresses::resetPressed(char c)
{
   resetPressed(static_cast<sf::Int32>(c) - static_cast<sf::Int32>('A'));
}

}  // namespace qa
