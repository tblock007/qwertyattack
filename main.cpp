#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <unordered_map>
#include "SongRun.hpp"

int main(int argc, char* argv[])
{
   using namespace qa;

   // Request a 24-bits depth buffer when creating the window
   sf::ContextSettings contextSettings;
   contextSettings.depthBits = 24;

   // Create the main window
   // Create the window of the application
   sf::RenderWindow window(sf::VideoMode(1280, 720, 32), "QWERTY Attack Prototype",
                           sf::Style::Titlebar | sf::Style::Close);
   window.setVerticalSyncEnabled(false);

   // Make it the active window for OpenGL calls
   window.setActive();

   SongRun run;
   if (argc == 1) {
      run.run2("resources/keycharts/megustastu.kc", window);
   }
   else {
      std::string chart = "resources/keycharts/";
      chart += argv[1];
      run.run2(chart, window);
   }
   return EXIT_SUCCESS;
}
