#include "KeyChart.h"



// ********************************************************************************
/// <summary>
/// Loads the KeyNotes specified by a KeyChart input file
/// </summary>
/// <param name="fileName">The relative path to the file to be parsed and loaded</param>
/// <param name="pulseTextures">The map of the textures to use for the KeyNote "pulse" animations</param>
/// <changed>tblock,11/17/2018</changed>
// ********************************************************************************
void KeyChart::loadFromFile(std::string fileName, KeyNote::TextureMap& pulseTextures) {
	float bpm = 115.5;
	float defaultSpeed = 0.0005f; // pixels/us
	sf::Int64 microsecondOffset = 1840000;
	sf::Int64 microsecondsPerBeat = static_cast<sf::Int64>(60000000.0f / bpm);
	std::srand(std::time(nullptr));

	// load the keynotes -  for now we will generate
	for (int i = 0; i < 100; i++) {
		sf::Int64 targetHitTime = microsecondOffset + (microsecondsPerBeat / 2) * (i + 1);
		sf::Int64 offscreenLoadTime = targetHitTime - (fullscreenWidth + pixelThreshold) / defaultSpeed;
		_keyNoteQueue.emplace(offscreenLoadTime, std::make_shared<BasicKeyNote>((std::rand() % 26) + 'A', defaultSpeed, targetHitTime, pulseTextures));
	}
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