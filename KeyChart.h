#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <queue>
#include "common.h"
#include "BasicKeyNote.h"


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
	void importFile(std::string fileName);
	std::optional<std::shared_ptr<KeyNote>> getKeyNote(sf::Int64 timeElapsed);


private:
	
	using TimePointerPair = std::pair<sf::Int64, std::shared_ptr<KeyNote>>;
	std::priority_queue<TimePointerPair, std::vector<TimePointerPair>, std::greater<TimePointerPair>> _keyNoteQueue;

	std::string _songFile;
	std::string _title;
	std::string _artist;
	std::string _genre;

	std::vector<std::string> getSectionContents(std::string section, std::fstream& fin);
	void appendContents(std::ofstream& fout, std::string section, std::vector<std::string> const& contents);
	void rewriteKeyChartFile(std::string fileName, std::vector<std::string> const& metaContents, std::vector<std::string> const& readableContents, std::vector<std::string> const& importableContents);
	std::tuple<std::string, std::string, std::string, std::string> parseMeta(std::vector<std::string> const& metaContents);
	std::vector<std::string> parseReadable(std::vector<std::string> const& readableContents);
	void parseImportable(std::vector<std::string> const& importableContents);

	std::shared_ptr<sf::Texture> _pulseTexture;
	std::shared_ptr<sf::Texture> _disappearTexture;
	std::shared_ptr<sf::Texture> _explodeGreatTexture;
	std::shared_ptr<sf::Texture> _explodeGoodTexture;

};