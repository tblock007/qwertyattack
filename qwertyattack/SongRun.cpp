#include "SongRun.hpp"

namespace qa {

SongRun::SongRun()
{
   // set up debug displays
   fpsFont_.loadFromFile("resources/sansation.ttf");
   fpsText_.setFont(fpsFont_);
   fpsText_.setString("FPS: ?");
   fpsText_.setFillColor(sf::Color::Black);
   fpsText_.setCharacterSize(20);
   fpsText_.setPosition(5.0f, 5.0f);

   scoreboardText_.setFont(fpsFont_);
   scoreboardText_.setString("Scoreboard: ");
   scoreboardText_.setFillColor(sf::Color::Black);
   scoreboardText_.setCharacterSize(20);
   scoreboardText_.setPosition(5.0f, 600.0f);

   bgTexture_.loadFromFile("resources/bg.png");
   bg_.setTexture(bgTexture_);
   bg_.setPosition(0, 0);
}


// rename
void SongRun::run(std::string keyChartFilePath, sf::RenderWindow& window)
{
   // generate in-game entities
   sf::Texture pulseTexture;
   pulseTexture.loadFromFile(pulseTextureFile);

   DataKeyNotes data;
   JudgementTally scoreboard;
   KeyChart chart;
   chart.importFile(keyChartFilePath, true, data, pulseTexture);

   sf::Music music;
   music.openFromFile("resources/songs/" + chart.getSongFile());

   KeyPresses keys;
   sf::Clock overallClock;

   // DEBUG
   int frameCounter = 0;
   sf::Clock frameClock;

   // start the game loop
   music.play();
   while (window.isOpen()) {
      // handle all events that occurred this frame
      sf::Event event;
      keys.reset();
      while (window.pollEvent(event)) {
         if (event.type == sf::Event::Closed) {
            window.close();
         }

         if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
               music.stop();
               window.close();
            }

            if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z) {
               keys.setPressed(static_cast<sf::Uint32>(event.key.code));
            }
         }
      }

      // DEBUG
      auto dt = frameClock.restart().asMicroseconds();
      float fps = 1000000.0f / dt;


      sf::Uint32 usElapsed = static_cast<sf::Uint32>(overallClock.getElapsedTime().asMicroseconds());

      data.updateDelimiters(usElapsed);
      data.updatePositions(usElapsed, scoreboard);
      data.updateStates(usElapsed, scoreboard, keys);

      auto [greats, goods, misses] = scoreboard.getTallies();
      scoreboardText_.setString("Scoreboard\nGREAT: " + std::to_string(greats) + "\nGOOD: " + std::to_string(goods)
                               + "\nMISSES: " + std::to_string(misses));

      // render the frame
      window.clear();
      window.draw(bg_);
      window.draw(data);
      window.draw(scoreboardText_);
      window.display();

      // DEBUG
      frameCounter++;
   }
}

}  // namespace qa
