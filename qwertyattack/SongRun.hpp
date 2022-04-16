#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace qa {
// --------------------------------------------------------------------------------
/// <summary>
/// Represents one play of a song
///
/// (NOTE: This class is still under heavy development)
/// </summary>
// --------------------------------------------------------------------------------
class SongRun {
  public:
   // ********************************************************************************
   /// <summary>
   /// Constructs a new instance of a KeyPresses, loading in graphics resources.
   /// </summary>
   // ********************************************************************************
   SongRun();

   // ********************************************************************************
   /// <summary>
   /// Runs the song, allowing the user to play.
   /// </summary>
   /// <param name="keyChartFilePath">The path to the .kc file containing the KeyChart.</param>
   /// <param name="window">The window in which to run the game.</param>
   // ********************************************************************************
   void run(std::string keyChartFilePath, sf::RenderWindow &window);

  private:
   sf::Texture bgTexture_;
   sf::Sprite bg_;
};

}  // namespace qa
