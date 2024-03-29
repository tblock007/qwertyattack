#include "KeyChart.hpp"

#include <SFML/Graphics.hpp>
#include <fstream>
#include <optional>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include "DataKeyNotes.hpp"
#include "TextNoteQueue.hpp"
#include "constants.hpp"
#include "utility.hpp"

namespace qa {

std::string KeyChart::getSongFile() const
{
   return songFile_;
}

std::string KeyChart::getTitle() const
{
   return title_;
}

std::string KeyChart::getArtist() const
{
   return artist_;
}

std::string KeyChart::getGenre() const
{
   return genre_;
}

void KeyChart::importFile(std::string fileName, bool writeImportable, DataKeyNotes &keynotes, TextNoteQueue &textnotes, sf::Texture &initTexture)
{
   std::fstream keyChartFile(fileName);
   std::vector<std::string> metaContents = getSectionContents("meta", keyChartFile);
   std::vector<std::string> readableContents = getSectionContents("readable", keyChartFile);
   std::vector<std::string> importableContents = getSectionContents("importable", keyChartFile);

   std::tie(songFile_, title_, artist_, genre_) = parseMeta(metaContents);
   if (importableContents.empty()) {
      importableContents = parseReadable(readableContents);
      if (writeImportable) {
         rewriteKeyChartFile(fileName, metaContents, readableContents, importableContents);
      }
   }
   parseImportable(importableContents, keynotes, textnotes, initTexture);
}

std::vector<std::string> KeyChart::getSectionContents(std::string sectionName, std::fstream &fin)
{
   std::vector<std::string> result;

   fin.clear();
   fin.seekg(0, std::ios_base::beg);

   std::string targetBeginLine = ".BEGIN " + sectionName;
   std::string targetEndLine = ".END " + sectionName;
   std::string line;
   while (std::getline(fin, line)) {
      trim(line);
      if (line == targetBeginLine) {
         while (std::getline(fin, line)) {
            trim(line);
            if (line == targetEndLine) {
               break;
            }
            result.push_back(line);
         }
      }
   }
   return result;
}

void KeyChart::appendContents(std::ofstream &fout, std::string section, std::vector<std::string> const &contents)
{
   fout << ".BEGIN " << section << std::endl;
   for (auto &&line : contents) {
      fout << line << std::endl;
   }
   fout << ".END " << section << std::endl << std::endl;
}

void KeyChart::rewriteKeyChartFile(std::string fileName, std::vector<std::string> const &metaContents,
                                   std::vector<std::string> const &readableContents,
                                   std::vector<std::string> const &importableContents)
{
   std::ofstream keyChartFile(fileName, std::ios_base::trunc);
   appendContents(keyChartFile, "meta", metaContents);
   appendContents(keyChartFile, "readable", readableContents);
   appendContents(keyChartFile, "importable", importableContents);
}

std::tuple<std::string, std::string, std::string, std::string> KeyChart::parseMeta(
    std::vector<std::string> const &metaContents)
{
   std::string songFile, title, artist, genre;

   for (auto &&line : metaContents) {
      std::istringstream iss(line);
      std::string firstToken;
      iss >> firstToken;
      if (firstToken == "FILE") {
         songFile = line.substr(5);
      }
      else if (firstToken == "TITLE") {
         title = line.substr(6);
      }
      else if (firstToken == "ARTIST") {
         artist = line.substr(7);
      }
      else if (firstToken == "GENRE") {
         genre = line.substr(6);
      }
   }
   return {songFile, title, artist, genre};
}

std::vector<std::string> KeyChart::parseReadable(std::vector<std::string> const &readableContents)
{
   std::vector<std::string> result;
   result.push_back("!DEFAULTSPEED 1");

   std::optional<float> bpm;
   std::optional<sf::Int32> bpl;
   float microsecondTime = 0.0f;
   for (auto &&line : readableContents) {
      if (!line.empty() && line[0] == '#') {
         continue;  // skip comment
      }
      else if (!line.empty() && line[0] == '!') {
         std::istringstream iss(line);
         std::string firstToken;
         iss >> firstToken;
         if (firstToken == "!OFFSET") {
            float secondsOffset;
            if (iss >> secondsOffset) {
               microsecondTime = secondsOffset * 1000000.0f;
            }
         }
         else if (firstToken == "!BPM") {
            float bpmToken;
            if (iss >> bpmToken) {
               bpm = bpmToken;
            }
         }
         else if (firstToken == "!BPLINE") {
            sf::Int32 bplToken;
            if (iss >> bplToken) {
               bpl = bplToken;
            }
         }
      }
      else {
         if (!bpm.has_value() || !bpl.has_value()) {
            // error: BPM or BPL not yet set
         }
         else {
            // the time in microseconds between KeyNotes represented on the current line
            float dt = (60000000.0f / (*bpm) * (*bpl)) / line.size();

            for (char c : line) {
               if (c >= 'A' && c <= 'Z') {
                  std::ostringstream oss;
                  oss << c << " " << static_cast<sf::Int64>(microsecondTime);
                  result.push_back(oss.str());
               }
               microsecondTime += dt;
            }
         }
      }
   }

   return result;
}

void KeyChart::parseImportable(std::vector<std::string> const &importableContents, DataKeyNotes &keynotes,
                               TextNoteQueue &textnotes, sf::Texture &initTexture)
{
   // TODO: clean up this interface
   // TODO: handle poor input (e.g., negative target hit times, bad characters)
   keynotes.xs_.clear();
   keynotes.ys_.clear();
   keynotes.speeds_.clear();
   keynotes.usHitTarget_.clear();
   keynotes.usAppearance_.clear();
   keynotes.usDisappearance_.clear();
   keynotes.usMiss_.clear();
   keynotes.states_.clear();
   keynotes.keys_.clear();
   keynotes.sprites_.clear();

   float defaultSpeedMultiplier = 1.0f;
   for (auto &&line : importableContents) {
      std::istringstream iss(line);
      std::string firstToken;
      iss >> firstToken;
      if (firstToken == "!DEFAULTSPEED") {
         iss >> defaultSpeedMultiplier;
      }
      else if (firstToken.size() == 1 && firstToken[0] >= 'A' && firstToken[0] <= 'Z') {
         char c;
         sf::Uint32 targetHitTime;
         float speedMultiplier;

         c = firstToken[0];
         iss >> targetHitTime;
         if (!(iss >> speedMultiplier)) {
            speedMultiplier = defaultSpeedMultiplier;
         }

         float note_speed = speedMultiplier * keyNoteSpeed;
         sf::Uint32 prehit_duration = static_cast<sf::Uint32>((fullscreenWidth + pixelThreshold) / note_speed);
         sf::Uint32 postmiss_duration = static_cast<sf::Uint32>(fullscreenWidth / note_speed);

         sf::Uint32 offscreenLoadTime = 0;
         if (targetHitTime > prehit_duration) {
            offscreenLoadTime = targetHitTime - prehit_duration;
         }
         sf::Uint32 offscreenUnloadTime = targetHitTime + postmiss_duration;

         // at t = 0, the note should be placed such that it reaches zoneLeftBound by its targetHitTime
         keynotes.xs_.emplace_back((targetHitTime - 0) * note_speed + zoneLeftBound);
         keynotes.ys_.emplace_back(charToY(c));
         keynotes.speeds_.emplace_back(note_speed);
         keynotes.usHitTarget_.emplace_back(targetHitTime);
         keynotes.usAppearance_.emplace_back(offscreenLoadTime);  // TODO: sort by appear times
         keynotes.usDisappearance_.emplace_back(offscreenUnloadTime);
         keynotes.usMiss_.emplace_back(targetHitTime + static_cast<sf::Uint32>(maxMicrosecondGood));
         keynotes.states_.emplace_back(DataKeyNotes::State::LIVE);
         keynotes.keys_.emplace_back(c);
         keynotes.sprites_.emplace_back(
             initTexture, sf::IntRect(leftOffset + ((c - 'A') * pixelsBetweenSprites), topOffset, width, height));
      }
      else if (firstToken == "[]") {
         sf::Uint32 startTime;
         sf::Uint32 endTime;
         iss >> startTime >> endTime >> std::ws;

         std::string text;
         getline(iss, text);
         textnotes.addTextNote(text, startTime, endTime);
      }
      else {
         // error: invalid line in importable
      }
   }
}

float KeyChart::charToY(char c)
{
   sf::Uint32 track = 0;
   switch (c) {
      case 'Q':
      case 'W':
      case 'E':
      case 'R':
      case 'T':
      case 'Y':
      case 'U':
      case 'I':
      case 'O':
      case 'P':
         track = 0;
         break;

      case 'A':
      case 'S':
      case 'D':
      case 'F':
      case 'G':
      case 'H':
      case 'J':
      case 'K':
      case 'L':
         track = 1;
         break;

      case 'Z':
      case 'X':
      case 'C':
      case 'V':
      case 'B':
      case 'N':
      case 'M':
         track = 2;
         break;
   }

   return trackOffset + (track * trackDistance);
}

}  // namespace qa
