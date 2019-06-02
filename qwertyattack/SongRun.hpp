#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <bitset>
#include <iostream>
#include <vector>
#include "DataKeyNotes.hpp"
#include "JudgementTally.hpp"
#include "KeyChart.hpp"
#include "KeyPresses.hpp"
#include "common.hpp"

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
   SongRun();
   void run(std::string keyChartFilePath, sf::RenderWindow &window);

   private:
   sf::Font fpsFont_;
   sf::Text fpsText_;
   sf::Text scoreboardText_;
   sf::Texture bgTexture_;
   sf::Sprite bg_;
};

}  // namespace qa
