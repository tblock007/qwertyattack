#include "KeyChart.hpp"

namespace qa {
// ********************************************************************************
/// <summary>
/// Constructor for KeyChart.  Loads the textures from file.
/// </summary>
/// <changed>tblock,11/20/2018</changed>
// ********************************************************************************
KeyChart::KeyChart()
{
   pulseTexture_.loadFromFile(pulseTextureFile);
   disappearTexture_.loadFromFile(disappearTextureFile);
   explodeGreatTexture_.loadFromFile(explodeGreatTextureFile);
   explodeGoodTexture_.loadFromFile(explodeGoodTextureFile);
}

// ********************************************************************************
/// <summary>
/// Getter method for song file of the KeyChart
/// </summary>
/// <returns>The song file of the KeyChart</returns>
/// <changed>tblock,11/18/2018</changed>
// ********************************************************************************
std::string KeyChart::getSongFile() const
{
   return songFile_;
}

// ********************************************************************************
/// <summary>
/// Getter method for title of the KeyChart
/// </summary>
/// <returns>The title of the KeyChart</returns>
/// <changed>tblock,11/18/2018</changed>
// ********************************************************************************
std::string KeyChart::getTitle() const
{
   return title_;
}

// ********************************************************************************
/// <summary>
/// Getter method for the artist of the KeyChart
/// </summary>
/// <returns>The artist of the KeyChart</returns>
/// <changed>tblock,11/18/2018</changed>
// ********************************************************************************
std::string KeyChart::getArtist() const
{
   return artist_;
}

// ********************************************************************************
/// <summary>
/// Getter method for the genre of the KeyChart
/// </summary>
/// <returns>The genre of the KeyChart</returns>
/// <changed>tblock,11/18/2018</changed>
// ********************************************************************************
std::string KeyChart::getGenre() const
{
   return genre_;
}

// TODO: clean up this interface
void KeyChart::importFile(std::string fileName, bool writeImportable, DataKeyNotes &data, sf::Texture &initTexture)
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
   parseImportable(importableContents, data, initTexture);
}

// ********************************************************************************
/// <summary>
/// Auxiliary function for retrieving an entire section of a .kc file from an input file stream
/// </summary>
/// <param name="sectionName">The section to retrieve (case sensitive)</param>
/// <param name="fin">The input file stream from which to fetch the section</param>
/// <returns>A vector of lines with all the contents of the requested section</returns>
/// <changed>tblock,11/18/2018</changed>
// ********************************************************************************
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

// ********************************************************************************
/// <summary>
/// Appends a KeyChart section to an open output file stream
/// </summary>
/// <param name="fout">An open file stream</param>
/// <param name="section">The title of the section</param>
/// <param name="contents">The contents of the section</param>
/// <changed>tblock,11/18/2018</changed>
// ********************************************************************************
void KeyChart::appendContents(std::ofstream &fout, std::string section, std::vector<std::string> const &contents)
{
   fout << ".BEGIN " << section << std::endl;
   for (auto &&line : contents) {
      fout << line << std::endl;
   }
   fout << ".END " << section << std::endl << std::endl;
}

// --------------------------------------------------------------------------------
/// <summary>
/// Rewrites the KeyChart file with the contents of each section.  This should be used after
/// readable section is parsed to create the importable section.
/// </summary>
// --------------------------------------------------------------------------------
void KeyChart::rewriteKeyChartFile(std::string fileName, std::vector<std::string> const &metaContents,
                                   std::vector<std::string> const &readableContents,
                                   std::vector<std::string> const &importableContents)
{
   std::ofstream keyChartFile(fileName, std::ios_base::trunc);
   appendContents(keyChartFile, "meta", metaContents);
   appendContents(keyChartFile, "readable", readableContents);
   appendContents(keyChartFile, "importable", importableContents);
}

// ********************************************************************************
/// <summary>
/// Parses the contents of the meta section of the KeyChart file to extract song file, title,
/// artist, and genre information
/// </summary>
/// <param name="metaContents">The lines read from the meta section</param>
/// <returns>The song file name, the title, the artist, the genre</returns>
/// <changed>tblock,11/18/2018</changed>
// ********************************************************************************
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

// ********************************************************************************
/// <summary>
/// Parses the contents of the readable section of the KeyChart file to generate the
/// actual importable section
/// </summary>
/// <param name="readableContents">The lines read from the readable section</param>
/// <returns>The contents of the importable section that can be written</returns>
/// <changed>tblock,11/18/2018</changed>
// ********************************************************************************
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

// ********************************************************************************
/// <summary>
/// Parses the contents of the importable section and populates data with all
/// relevant properties of the KeyNotes within the KeyChart
/// </summary>
/// <changed>tblock,04/11/2022</changed>
// ********************************************************************************
void KeyChart::parseImportable(std::vector<std::string> const &importableContents, DataKeyNotes &data,
                               sf::Texture &initTexture)
{
   // TODO: clean up this interface
   // TODO: handle poor input (e.g., negative target hit times, bad characters)
   data.xs_.clear();
   data.ys_.clear();
   data.speeds_.clear();
   data.targetHitTimes_.clear();
   data.appearTimes_.clear();
   data.disappearTimes_.clear();
   data.missTimes_.clear();
   data.states_.clear();
   data.keys_.clear();
   data.sprites_.clear();

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
         data.xs_.emplace_back((targetHitTime - 0) * note_speed + zoneLeftBound);
         data.ys_.emplace_back(charToY(c));
         data.speeds_.emplace_back(note_speed);
         data.targetHitTimes_.emplace_back(targetHitTime);
         data.appearTimes_.emplace_back(offscreenLoadTime);  // TODO: sort by appear times
         data.disappearTimes_.emplace_back(offscreenUnloadTime);
         data.missTimes_.emplace_back(targetHitTime + static_cast<sf::Uint32>(maxMicrosecondGood));
         data.states_.emplace_back(KeyNoteState::LIVE);
         data.keys_.emplace_back(c);
         data.sprites_.emplace_back(
             initTexture, sf::IntRect(leftOffset + ((c - 'A') * pixelsBetweenSprites), topOffset, width, height));
      }
      else {
         // error: invalid line in importable
      }
   }
}

// ********************************************************************************
/// <summary>
/// Maps each character to a y-position, based on the QWERTY keyboard.
/// </summary>
/// <returns>The y-position, in pixels, where the KeyNote with this character
/// should be placed.</returns>
/// <changed>tblock,04/11/2022</changed>
// ********************************************************************************
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
