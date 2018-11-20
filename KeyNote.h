#pragma once
#include <optional>
#include <unordered_map>
#include <SFML/Graphics.hpp>


// --------------------------------------------------------------------------------
/// <summary>
/// Abstract class representing one KeyNote, the entity that scrolls across the screen during a SongRun, whose key is to be pressed by the player when it enters the hit zone
///
/// Implements the Drawable interface, allowing it to be drawn on a RenderTarget
/// </summary>
// --------------------------------------------------------------------------------
class KeyNote : public sf::Drawable {

protected:
	

public:
	using TextureMap = std::unordered_map<std::string, sf::Texture>;

	virtual ~KeyNote() {}

	virtual KeyNoteState getState() const = 0; // TODO: consider making this a base class non-virtual, with corresponding base class member variable
	virtual std::optional<Judgement> sendKey(std::bitset<NUM_KEYS> pressed, sf::Int64 timeElapsed, TextureMap const& explodeTextures) = 0;
	virtual std::optional<Judgement> updateFrame(sf::Int64 timeElapsed) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

};