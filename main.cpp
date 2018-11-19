#include <iostream>
#include <unordered_map>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "SongRun.h"

 


int main() {


	// Request a 24-bits depth buffer when creating the window
	sf::ContextSettings contextSettings;
	contextSettings.depthBits = 24;

	// Create the main window
	// Create the window of the application
	sf::RenderWindow window(sf::VideoMode(1280, 720, 32), "QWERTY Attack Prototype",
		sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);

    // Make it the active window for OpenGL calls
    window.setActive();

	SongRun run;
	run.run("resources/keycharts/alphabet.kc", window);

    return EXIT_SUCCESS;
}