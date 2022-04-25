#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>

#include "DataKeyNotes.hpp"
#include "TextNoteQueue.hpp"
#include "constants.hpp"

namespace qa {
// --------------------------------------------------------------------------------
/// <summary>
/// Represents a KeyChart, a collection of KeyNotes to be pressed in a SongRun
/// </summary>
// --------------------------------------------------------------------------------
class KeyChart {
  public:
   // ********************************************************************************
   /// <summary>
   /// Returns the song file path of the KeyChart.
   /// </summary>
   /// <returns>The song file path.</returns>
   // ********************************************************************************
   [[nodiscard]] std::string getSongFile() const;

   // ********************************************************************************
   /// <summary>
   /// Returns the song title of the KeyChart.
   /// </summary>
   /// <returns>The song title of the KeyChart.</returns>
   // ********************************************************************************
   [[nodiscard]] std::string getTitle() const;

   // ********************************************************************************
   /// <summary>
   /// Returns the song artist of the KeyChart.
   /// </summary>
   /// <returns>The song artist of the KeyChart.</returns>
   // ********************************************************************************
   [[nodiscard]] std::string getArtist() const;

   // ********************************************************************************
   /// <summary>
   /// Returns the song genre of the KeyChart.
   /// </summary>
   /// <returns>The song genre of the KeyChart.</returns>
   // ********************************************************************************
   [[nodiscard]] std::string getGenre() const;

   // TODO: split this function up
   // ********************************************************************************
   /// <summary>
   /// Imports a .kc file into a DataKeyNotes object.
   /// </summary>
   /// <param name="fileName">The path to the .kc file.</param>
   /// <param name="writeImportable">True if the "importable" section of the KeyChart
   /// should be written based on the "readable" section.</param>
   /// <param name="keynotes">The DataKeyNotes object into which to import Keynotes.</param>
   /// <param name="textnotes">The TextNoteQueue object into which to import Textnotes.</param>
   /// <param name="initTexture">The Texture used to display KeyNotes.</param>
   // ********************************************************************************
   void importFile(std::string fileName, bool writeImportable, DataKeyNotes &keynotes, TextNoteQueue &textnotes,
                   sf::Texture &initTexture);

  private:
   // Reads in the named section from an fstream.
   std::vector<std::string> getSectionContents(std::string section, std::fstream &fin);

   // Writes a section to an fstream.
   void appendContents(std::ofstream &fout, std::string section, std::vector<std::string> const &contents);

   // Rewrites the KeyChart file with the contents of each section.  This should be used after
   // readable section is parsed to create the importable section.
   void rewriteKeyChartFile(std::string fileName, std::vector<std::string> const &metaContents,
                            std::vector<std::string> const &readableContents,
                            std::vector<std::string> const &importableContents);

   // Parses the contents of the meta section of the KeyChart file to extract song file, title,
   // artist, and genre information.
   std::tuple<std::string, std::string, std::string, std::string> parseMeta(
       std::vector<std::string> const &metaContents);

   // Parses the contents of the readable section of the KeyChart file to generate the
   // actual importable section.
   std::vector<std::string> parseReadable(std::vector<std::string> const &readableContents);

   // Parses the contents of the importable section and populates data with all
   /// relevant properties of the KeyNotes within the KeyChart.
   void parseImportable(std::vector<std::string> const &importableContents, DataKeyNotes &keynotes,
                        TextNoteQueue &textnotes, sf::Texture &initTexture);

   // TODO: move this to a better place?
   // Maps each character to a y-position, based on the QWERTY keyboard.
   float charToY(char c);

   // Meta information about the song.
   std::string songFile_;
   std::string title_;
   std::string artist_;
   std::string genre_;
};

}  // namespace qa
