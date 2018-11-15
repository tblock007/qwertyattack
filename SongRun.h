#include <bitset>
#include <future>
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "KeyNote.h"

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
private:
	void playMusic(std::mutex& m, std::condition_variable& cv, bool& play);
};