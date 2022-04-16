#pragma once

#include <SFML/Config.hpp>
#include <algorithm>
#include <cctype>
#include <string>

namespace qa {

// ********************************************************************************
/// <summary>
/// Modifies a string by trimming whitespace from the left.
/// </summary>
/// <param name="s">The string to be modified.</param>
// ********************************************************************************
static inline void ltrim(std::string& s)
{
   s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) { return !std::isspace(c); }));
}

// ********************************************************************************
/// <summary>
/// Modifies a string by trimming whitespace from the right.
/// </summary>
/// <param name="s">The string to be modified.</param>
// ********************************************************************************
static inline void rtrim(std::string& s)
{
   s.erase(std::find_if(s.rbegin(), s.rend(), [](int c) { return !std::isspace(c); }).base(), s.end());
}

// ********************************************************************************
/// <summary>
/// Modifies a string by trimming whitespace from both sides.
/// </summary>
/// <param name="s">The string to be modified.</param>
// ********************************************************************************
static inline void trim(std::string& s)
{
   ltrim(s);
   rtrim(s);
}

// ********************************************************************************
/// <summary>
/// Performs signed subtraction (a - b) between two unsigned numbers.
/// </summary>
/// <param name="a">The value from which `b` is subtracted.</param>
/// <param name="b">The value to subtract from `a`.</param>
/// <returns>A signed value representing the result of the subtraction.</returns>
// ********************************************************************************
static inline sf::Int64 timeDiff(sf::Uint32 a, sf::Uint32 b)
{
   return static_cast<sf::Int64>(a) - static_cast<sf::Int64>(b);
}

}  // namespace qa
