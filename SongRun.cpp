#include "SongRun.h"




// ********************************************************************************
/// <summary>
/// Runs the song
/// </summary>
/// <param name="window">The RenderWindow on which to render graphics</param>
/// <changed>tblock,11/15/2018</changed>
// ********************************************************************************
void SongRun::run(sf::RenderWindow& window) {
	
	sf::Music music;
	music.openFromFile("resources/bpm_115_5.flac");
	float bpm = 115.5;
	float defaultSpeed = 0.0005f;
	sf::Int64 microsecondOffset = 1840000;
	sf::Int64 microsecondsPerBeat = static_cast<sf::Int64>(60000000.0f / bpm);
	std::srand(std::time(nullptr));

	// load the textures into memory
	std::unordered_map<std::string, sf::Texture> pulseTextures; // potential optimization here - use a faster data structure
	for (char c = 'A'; c <= 'Z'; c++) {
		pulseTextures[std::string(1, c)].loadFromFile("resources/keynotes/" + std::string(1, c) + "_keynote_pulse.png");
	}

	std::unordered_map<std::string, sf::Texture> explodeTextures;
	for (char c = 'A'; c <= 'Z'; c++) {
		explodeTextures[std::string(1, c)].loadFromFile("resources/keynotes/" + std::string(1, c) + "_keynote_explode.png");
	}

	// load the keynotes -  for now we will generate
	std::vector<std::shared_ptr<KeyNote>> keynotes;
	for (int i = 0; i < 100; i++) {
		keynotes.emplace_back(std::make_shared<BasicKeyNote>((std::rand() % 26) + 'A', defaultSpeed, microsecondOffset + (microsecondsPerBeat / 2) * (i + 1), pulseTextures));
	}
	
	sf::Texture bgTexture;
	bgTexture.loadFromFile("resources/bg.png");
	sf::Sprite bg;
	bg.setTexture(bgTexture);
	bg.setPosition(0, 0);

	std::bitset<26> pressed;
	sf::Clock frameClock;
	sf::Clock overallClock;
	int frameCounter = 0;
	
	// play music and start the game loop
	music.play();
	while (window.isOpen())
	{
		// handle all events that occurred this frame
		sf::Event event;
		pressed.reset();
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					music.stop();
					window.close();
				}

				if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z) {
					pressed.set(event.key.code);
				}
			}
		}

		auto dt = frameClock.restart().asMicroseconds();
		float fps = 1000000.0f / dt;
		std::cout << "FPS: " << std::to_string(fps) << std::endl;

		window.clear();
		window.draw(bg);
		keynotes.erase(std::remove_if(keynotes.begin(), keynotes.end(), [](std::shared_ptr<KeyNote> const& kn) { return (kn->getState() == KeyNote::State::DEAD); }), keynotes.end());
		for (auto kn : keynotes) {
			
			kn->sendKey(pressed, overallClock.getElapsedTime().asMicroseconds(), explodeTextures);
			kn->updateFrame(overallClock.getElapsedTime().asMicroseconds());
			window.draw(*kn);
		}

		window.display();
		frameCounter++;

	}
}