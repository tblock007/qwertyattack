#include "SongRun.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>

#include "DataKeyNotes.hpp"
#include "JudgementTally.hpp"
#include "Judgements.hpp"
#include "KeyChart.hpp"
#include "KeyPresses.hpp"
#include "TextNoteQueue.hpp"
#include "constants.hpp"

namespace qa {

SongRun::SongRun()
{
   bgTexture_.loadFromFile("resources/bg.png");
   bg_.setTexture(bgTexture_);
   bg_.setPosition(0, 0);
}

void SongRun::run(std::string keyChartFilePath, sf::RenderWindow& window)
{
   // Generate in-game entities
   sf::Texture pulseTexture;
   pulseTexture.loadFromFile(pulseTextureFile);

   DataKeyNotes keynotes;
   TextNoteQueue textnotes;
   Judgements judgements;
   JudgementTally scoreboard;
   KeyChart chart;
   chart.importFile(keyChartFilePath, true, keynotes, textnotes, pulseTexture);

   sf::Music music;
   music.openFromFile("resources/songs/" + chart.getSongFile());

   KeyPresses keys;
   sf::Clock overallClock;

   // Start the game loop.
   music.play();
   while (window.isOpen()) {
      // Handle all events that occurred this frame.
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
               keys.setPressed(static_cast<sf::Int32>(event.key.code) - static_cast<sf::Int32>(sf::Keyboard::A));
            }
         }
      }

      sf::Uint32 usElapsed = static_cast<sf::Uint32>(overallClock.getElapsedTime().asMicroseconds());

      judgements.update(usElapsed);
      keynotes.updateDelimiters(usElapsed);
      keynotes.updatePositions(usElapsed);
      keynotes.updateStates(usElapsed, judgements, scoreboard, keys);
      textnotes.update(usElapsed, judgements, scoreboard, keys);

      // Render the frame.
      window.clear();
      window.draw(bg_);
      window.draw(judgements);
      window.draw(keynotes);
      window.draw(textnotes);
      window.display();
   }
}

}  // namespace qa
