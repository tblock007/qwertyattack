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
   pulseTexture_ = std::make_shared<sf::Texture>();
   disappearTexture_ = std::make_shared<sf::Texture>();
   explodeGreatTexture_ = std::make_shared<sf::Texture>();
   explodeGoodTexture_ = std::make_shared<sf::Texture>();

   pulseTexture_->loadFromFile(pulseTextureFile);
   disappearTexture_->loadFromFile(disappearTextureFile);
   explodeGreatTexture_->loadFromFile(explodeGreatTextureFile);
   explodeGoodTexture_->loadFromFile(explodeGoodTextureFile);
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

// ********************************************************************************
/// <summary>
/// Loads the KeyNotes specified by a KeyChart input file
/// </summary>
/// <param name="fileName">The relative path to the file to be parsed and loaded</param>
/// <changed>tblock,11/20/2018</changed>
// ********************************************************************************
void KeyChart::importFile(std::string fileName)
{
   std::fstream keyChartFile(fileName);
   auto metaContents = getSectionContents("meta", keyChartFile);
   auto readableContents = getSectionContents("readable", keyChartFile);
   auto importableContents = getSectionContents("importable", keyChartFile);

   std::tie(songFile_, title_, artist_, genre_) = parseMeta(metaContents);
   if (importableContents.empty()) {
      importableContents = parseReadable(readableContents);
      rewriteKeyChartFile(fileName, metaContents, readableContents, importableContents);
   }
   parseImportable(importableContents);
}

// ********************************************************************************
/// <summary>
/// Checks the upcoming KeyNotes to see if the upcoming KeyNotes are soon enough to be loaded
/// </summary>
/// <param name="timeElapsed">A (relative) time in microseconds indicating time elapsed since some reference; used to
/// determine whether a KeyNote should be returned</param> <returns>An optional pointer to KeyNote that points to the
/// KeyNote to be added to the list of entities, if present</returns> <changed>tblock,11/17/2018</changed>
// ********************************************************************************
std::optional<std::shared_ptr<KeyNote>> KeyChart::getKeyNote(sf::Int64 timeElapsed)
{
   std::optional<std::shared_ptr<KeyNote>> result;
   if (!keyNoteStack_.empty()) {
      if (timeElapsed > keyNoteStack_.back().first) {
         result = keyNoteStack_.back().second;
         keyNoteStack_.pop_back();
      }
   }
   return result;
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
   for (auto const &line : contents) {
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

   for (auto const &line : metaContents) {
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
   for (auto const &line : readableContents) {
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
            float keyNoteInterval = (60000000.0f / bpm.value() * bpl.value()) / line.size();
            for (char c : line) {
               if (c >= 'A' && c <= 'Z') {
                  std::ostringstream oss;
                  oss << c << " " << static_cast<sf::Int64>(microsecondTime);
                  result.push_back(oss.str());
               }
               microsecondTime += keyNoteInterval;
            }
         }
      }
   }

   return result;
}

// --------------------------------------------------------------------------------
/// <summary>
/// Parses the contents of the importable section to generate the actual KeyNote entities
/// </summary>
/// <param name="importableContents">The lines read from the importable section</param>
/// <changed>tblock,11/20/2018</changed>
// --------------------------------------------------------------------------------
void KeyChart::parseImportable(std::vector<std::string> const &importableContents)
{
   float defaultSpeedMultiplier = 1.0f;
   for (auto const &line : importableContents) {
      std::istringstream iss(line);
      std::string firstToken;
      iss >> firstToken;
      if (firstToken == "!DEFAULTSPEED") {
         iss >> defaultSpeedMultiplier;
      }
      else if (firstToken.size() == 1 && firstToken[0] >= 'A' && firstToken[0] <= 'Z') {
         char c;
         sf::Int64 targetHitTime;
         float speedMultiplier;

         c = firstToken[0];
         iss >> targetHitTime;
         if (!(iss >> speedMultiplier)) {
            speedMultiplier = defaultSpeedMultiplier;
         }
         sf::Int64 offscreenLoadTime
             = targetHitTime
               - static_cast<sf::Int64>((fullscreenWidth + pixelThreshold) / (speedMultiplier * keyNoteSpeed));
         keyNoteStack_.emplace_back(
             offscreenLoadTime,
             std::make_shared<BasicKeyNote>(c, (speedMultiplier * keyNoteSpeed), targetHitTime, pulseTexture_,
                                            disappearTexture_, explodeGreatTexture_, explodeGoodTexture_));
      }
      else {
         // error: invalid line in importable
      }
   }

   // populate the stack now that we can extract the KeyNotes in targetHitTime order
   std::sort(keyNoteStack_.begin(), keyNoteStack_.end(),
             [](TimePointerPair const &lhs, TimePointerPair const &rhs) -> bool { return lhs.first > rhs.first; });
}

}  // namespace qa
