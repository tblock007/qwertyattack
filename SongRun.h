#pragma once
#include <bitset>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "common.h"
#include "BasicKeyNote.h"
#include "JudgementTally.h"
#include "KeyChart.h"

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