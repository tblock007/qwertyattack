#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <bitset>
#include <iostream>
#include <vector>
#include "BasicKeyNote.hpp"
#include "JudgementTally.hpp"
#include "KeyChart.hpp"
#include "common.hpp"

// --------------------------------------------------------------------------------
/// <summary>
/// Represents one play of a song
///
/// (NOTE: This class is still under heavy development)
/// </summary>
// --------------------------------------------------------------------------------
class SongRun {
  public:
   void run(std::string keyChartFilePath, sf::RenderWindow& window);
};