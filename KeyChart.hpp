#pragma once
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <vector>
#include "BasicKeyNote.hpp"
#include "common.hpp"
#include "DataKeyNotes.hpp"

namespace qa {
// --------------------------------------------------------------------------------
/// <summary>
/// Represents a KeyChart, a collection of KeyNotes to be pressed in a SongRun
/// </summary>
// --------------------------------------------------------------------------------
class KeyChart {
  public:
   KeyChart();

   std::string getSongFile() const;

   std::string getTitle() const;

   std::string getArtist() const;

   std::string getGenre() const;

   void importFile(std::string fileName, bool writeImportable);
   void importFile(std::string fileName, bool writeImportable, DataKeyNotes& data, sf::Texture& initTexture);

   std::optional<std::shared_ptr<KeyNote>> getKeyNote(sf::Int64 timeElapsed);

   void fillData(DataKeyNotes &data);

  private:
   using TimePointerPair = std::pair<sf::Int64, std::shared_ptr<KeyNote>>;
   std::vector<TimePointerPair> keyNoteStack_;

   std::string songFile_;
   std::string title_;
   std::string artist_;
   std::string genre_;

   std::shared_ptr<sf::Texture> pulseTexture_;
   std::shared_ptr<sf::Texture> disappearTexture_;
   std::shared_ptr<sf::Texture> explodeGreatTexture_;
   std::shared_ptr<sf::Texture> explodeGoodTexture_;

   std::vector<std::string> getSectionContents(std::string section, std::fstream &fin);

   void appendContents(std::ofstream &fout, std::string section, std::vector<std::string> const &contents);

   void rewriteKeyChartFile(std::string fileName, std::vector<std::string> const &metaContents,
                            std::vector<std::string> const &readableContents,
                            std::vector<std::string> const &importableContents);

   std::tuple<std::string, std::string, std::string, std::string> parseMeta(
       std::vector<std::string> const &metaContents);

   std::vector<std::string> parseReadable(std::vector<std::string> const &readableContents);

   void parseImportable(std::vector<std::string> const &importableContents);
   void parseImportable(std::vector<std::string> const &importableContents, DataKeyNotes& data, sf::Texture& initTexture);

   float charToY(char c);
};

}  // namespace qa
