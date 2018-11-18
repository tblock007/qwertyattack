#include "KeyChart.h"


std::string KeyChart::getTitle() const {
	return _title;
}



std::string KeyChart::getArtist() const {
	return _artist;
}



std::string KeyChart::getGenre() const {
	return _genre;
}



// ********************************************************************************
/// <summary>
/// Loads the KeyNotes specified by a KeyChart input file
/// </summary>
/// <param name="fileName">The relative path to the file to be parsed and loaded</param>
/// <param name="pulseTextures">The map of the textures to use for the KeyNote "pulse" animations</param>
/// <changed>tblock,11/17/2018</changed>
// ********************************************************************************
void KeyChart::importFile(std::string fileName, KeyNote::TextureMap& pulseTextures) {

	std::ifstream fin(fileName);

	// parse meta contents
	std::string status = "INVALID";
	auto metaContents = getSectionContents("meta", fin);
	for (auto const& line : metaContents) {
		std::istringstream iss(line);
		std::string firstToken;
		iss >> firstToken;
		if (firstToken == "STATUS") {
			status = line.substr(7);
		}
		else if (firstToken == "TITLE") {
			_title = line.substr(6);
		}
		else if (firstToken == "ARTIST") {
			_artist = line.substr(7);
		}
		else if (firstToken == "GENRE") {
			_genre = line.substr(6);
		}
	}

	if (status == "INVALID") {
		// error: could not obtain status
	}
	else if (status == "FRESH") {
		// readable has been edited, so we need to parse it and generate the importable section
		auto readableContents = getSectionContents("readable", fin);
	}
	else if (status == "COMPUTED") {
		// we have computed this in the past, so we only need to import directly from importable section
		auto importableContents = getSectionContents("importable", fin);
		float defaultSpeedMultiplier = 1.0f;
		for (auto const& line : importableContents) {
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
				sf::Int64 offscreenLoadTime = targetHitTime - static_cast<sf::Int64>((fullscreenWidth + pixelThreshold) / (speedMultiplier * keyNoteSpeed));
				_keyNoteQueue.emplace(offscreenLoadTime, std::make_shared<BasicKeyNote>(c, (speedMultiplier * keyNoteSpeed), targetHitTime, pulseTextures));
			}
			else {
				// error: invalid line in importable
			}
		}
	}


	//float bpm = 115.5;
	//float defaultSpeed = 0.0005f; // pixels/us
	//sf::Int64 microsecondOffset = 1840000;
	//sf::Int64 microsecondsPerBeat = static_cast<sf::Int64>(60000000.0f / bpm);
	//std::srand(static_cast<unsigned int>(std::time(nullptr)));

	//// load the keynotes -  for now we will generate
	//for (int i = 0; i < 100; i++) {
	//	sf::Int64 targetHitTime = microsecondOffset + (microsecondsPerBeat / 2) * (i + 1);
	//	sf::Int64 offscreenLoadTime = targetHitTime - static_cast<sf::Int64>((fullscreenWidth + pixelThreshold) / defaultSpeed);
	//	_keyNoteQueue.emplace(offscreenLoadTime, std::make_shared<BasicKeyNote>((std::rand() % 26) + 'A', defaultSpeed, targetHitTime, pulseTextures));
	//}
}




// ********************************************************************************
/// <summary>
/// Checks the priority queue to see if the upcoming KeyNotes are soon enough to be loaded
/// </summary>
/// <param name="timeElapsed">A (relative) time in microseconds indicating time elapsed since some reference; used to determine whether a KeyNote should be returned</param>
/// <returns>An optional pointer to KeyNote that points to the KeyNote to be added to the list of entities, if present</returns>
/// <changed>tblock,11/17/2018</changed>
// ********************************************************************************
std::optional<std::shared_ptr<KeyNote>> KeyChart::getKeyNote(sf::Int64 timeElapsed) {
	std::optional<std::shared_ptr<KeyNote>> result;
	if (!_keyNoteQueue.empty()) {
		if (timeElapsed > _keyNoteQueue.top().first) {
			result = _keyNoteQueue.top().second;
			_keyNoteQueue.pop();
		}
	}
	return result;
}





std::vector<std::string> KeyChart::getSectionContents(std::string sectionName, std::ifstream& fin) {
	
	std::vector<std::string> result;

	fin.clear();
	fin.seekg(0, std::ios_base::beg);
	
	std::string targetBeginLine = ".BEGIN " + sectionName;
	std::string targetEndLine = ".END " + sectionName;
	std::string line;
	while (std::getline(fin, line)) {
		if (line == targetBeginLine) {
			while (std::getline(fin, line) && line != targetEndLine) {
				result.push_back(line);
			}
		}
	}
	return result;
}