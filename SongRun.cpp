#include "SongRun.h"




// ********************************************************************************
/// <summary>
/// Runs the song
/// </summary>
/// <param name="keyChartFilePath">The path to the file that contains KeyChart information</param>
/// <param name="window">The RenderWindow on which to render graphics</param>
/// <changed>tblock,11/20/2018</changed>
// ********************************************************************************
void SongRun::run(std::string keyChartFilePath, sf::RenderWindow& window) {

	// set up debug displays
	sf::Font fpsFont;
	fpsFont.loadFromFile("resources/sansation.ttf");
	sf::Text fpsText;
	fpsText.setFont(fpsFont);
	fpsText.setString("FPS: ?");
	fpsText.setFillColor(sf::Color::Black);
	fpsText.setCharacterSize(20);
	fpsText.setPosition(5.0f, 5.0f);

	sf::Text scoreboardText;
	scoreboardText.setFont(fpsFont);
	scoreboardText.setString("Scoreboard: ");
	scoreboardText.setFillColor(sf::Color::Black);
	scoreboardText.setCharacterSize(20);
	scoreboardText.setPosition(5.0f, 600.0f);
	
	sf::Texture bgTexture;
	bgTexture.loadFromFile("resources/bg.png");
	sf::Sprite bg;
	bg.setTexture(bgTexture);
	bg.setPosition(0, 0);

	// generate in-game entities
	JudgementTally scoreboard;

	KeyChart chart;
	chart.importFile(keyChartFilePath);

	sf::Music music;
	music.openFromFile("resources/songs/" + chart.getSongFile());
	
	std::vector<std::shared_ptr<KeyNote>> keynotes;

	std::bitset<26> pressed;
	sf::Clock frameClock;
	sf::Clock overallClock;
	int frameCounter = 0;
	
	// start the game loop
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

		// handle timing
		auto dt = frameClock.restart().asMicroseconds();
		float fps = 1000000.0f / dt;
		if (frameCounter % 60 == 0) {
			fpsText.setString("FPS: " + std::to_string(fps) + "; Active KeyNotes: " + std::to_string(keynotes.size()));
		}		
		
		// get the KeyNotes to be added to the collection of active KeyNotes
		sf::Int64 overallTime = overallClock.getElapsedTime().asMicroseconds();
		std::optional<std::shared_ptr<KeyNote>> toBeAdded;
		while (toBeAdded = chart.getKeyNote(overallTime)) {
			keynotes.push_back(toBeAdded.value());
		}

		// remove any inactive KeyNotes from our data structure
		keynotes.erase(std::remove_if(keynotes.begin(), keynotes.end(), [](std::shared_ptr<KeyNote> const& kn) { return (kn->getState() == KeyNoteState::DEAD); }), keynotes.end());

		// send the keys pressed to all KeyNotes to see if any hits or misses occur
		for (auto kn : keynotes) {
			auto judgement = kn->sendKey(pressed, overallTime);
			if (judgement) {
				scoreboard.incrementTally(judgement.value());
			}
			judgement = kn->updateFrame(overallTime); // note that this call returns a MISS judgement if the update causes a KeyNote to scroll off the screen
			if (judgement) {
				scoreboard.incrementTally(judgement.value());
			}
		}
		auto[greats, goods, misses] = scoreboard.getTallies();
		scoreboardText.setString("Scoreboard\nGREAT: " + std::to_string(greats) + "\nGOOD: " + std::to_string(goods) + "\nMISSES: " + std::to_string(misses));

		// render the frame
		window.clear();
		window.draw(bg);
		window.draw(fpsText);

		for (auto kn : keynotes) {			
			window.draw(*kn);
		}

		window.draw(scoreboardText);

		window.display();

		frameCounter++;
	}
}