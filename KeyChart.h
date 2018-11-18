#pragma once
#include <cstdlib>
#include <ctime>
#include <optional>
#include <queue>
#include "BasicKeyNote.h"


// --------------------------------------------------------------------------------
/// <summary>
/// Represents a KeyChart, a collection of KeyNotes to be pressed in a SongRun
/// </summary>
// --------------------------------------------------------------------------------
class KeyChart {
public:
	void loadFromFile(std::string fileName, KeyNote::TextureMap& pulseTextures);
	std::optional<std::shared_ptr<KeyNote>> getKeyNote(sf::Int64 timeElapsed);


private:
	// TODO: move these to the appropriate place
	static sf::Int64 constexpr pixelThreshold = 640; // buffer half a screen of KeyNotes (technically a problem if KeyNotes start travelling too fast)
	static sf::Int64 constexpr fullscreenWidth = 1280;

	using TimePointerPair = std::pair<sf::Int64, std::shared_ptr<KeyNote>>;
	std::priority_queue<TimePointerPair, std::vector<TimePointerPair>, std::greater<TimePointerPair>> _keyNoteQueue;

};