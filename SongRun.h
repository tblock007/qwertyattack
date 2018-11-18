#pragma once
#include <bitset>
#include <future>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "BasicKeyNote.h"
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
	void run(sf::RenderWindow& window);
};