#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "SongRun.hpp"
#include "common.hpp"

int main(int argc, char* argv[])
{
   using namespace qa;

   // Request a 24-bits depth buffer when creating the window.
   sf::ContextSettings contextSettings;
   contextSettings.depthBits = 24;

   // Create the main window, and the window of the application.
   // NOTE: for NVIDIA graphics cards, turn off Threaded Optimization to get rid of stutter
   // https://stackoverflow.com/questions/36959508/nvidia-graphics-driver-causing-noticeable-frame-stuttering
   sf::RenderWindow window(sf::VideoMode(1280, 720, 32), "QWERTY Attack Prototype",
                           sf::Style::Titlebar | sf::Style::Close);
   window.setVerticalSyncEnabled(false);
   window.setFramerateLimit(frameLimit);

   // Make it the active window for OpenGL calls.
   window.setActive();

   SongRun run;
   if (argc == 1) {
      run.run("resources/keycharts/megustastu.kc", window);
   }
   else {
      std::string chart = "resources/keycharts/";
      chart += argv[1];
      run.run(chart, window);
   }
   return EXIT_SUCCESS;
}
