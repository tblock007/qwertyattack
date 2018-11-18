#include "SongRun.h"


// ********************************************************************************
/// <summary>
/// Example callback for playing music
/// </summary>
/// <param name="m">Mutex associated with the flag variable <c>play</c></param>
/// <param name="cv">Condition variable used to signal this function to start playing music</param>
/// <param name="play">Flag variable used to indicate whether the function should play music</param>
/// <changed>tblock,11/15/2018</changed>
// ********************************************************************************
void SongRun::playMusic(std::mutex& m, std::condition_variable& cv, bool& play) {

	// Load an flac music file
	sf::Music music;
	if (!music.openFromFile("resources/song.flac"))
		return;

	// Play it
	std::unique_lock<std::mutex> ul(m);
	cv.wait(ul, [&]() { return play; }); 
	ul.unlock();

	music.play();

	// Loop while the music is playing
	while (music.getStatus() == sf::Music::Playing)
	{
		// Leave some CPU time for other processes
		sf::sleep(sf::milliseconds(100));

		if (!play) {
			break;
		}
	}

}



// ********************************************************************************
/// <summary>
/// Runs the song
/// </summary>
/// <param name="window">The RenderWindow on which to render graphics</param>
/// <changed>tblock,11/15/2018</changed>
// ********************************************************************************
void SongRun::run(sf::RenderWindow& window) {

	std::condition_variable cv;
	std::mutex m;
	bool play = false;

	//auto fut = std::async(std::launch::async, SongRun::playMusic, std::ref(m), std::ref(cv), std::ref(play));

	

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
	for (int i = 0; i < 26; i++) {
		keynotes.emplace_back(std::make_shared<BasicKeyNote>(i + 'A', 0.0005f, 2000000 + 500000 * (i + 1), pulseTextures));
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

	cv.notify_one();

	// Start the game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		pressed.reset();
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			// Handle key presses
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
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