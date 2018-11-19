#pragma once
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
	// TODO: move these to the appropriate place eventually
	static sf::Int32 constexpr NUM_KEYS = 26;
	static sf::Int32 constexpr width = 80;
	static sf::Int32 constexpr height = 80;
	static sf::Int32 constexpr leftOffset = 25;
	static sf::Int32 constexpr topOffset = 24;
	static sf::Int32 constexpr pixelsBetweenSprites = 128;
	static sf::Int32 constexpr pulseFrames = 125;
	static sf::Int32 constexpr explodeFrames = 37;
	static float constexpr zoneLeftBound = 40.0f;
	static float constexpr deathBound = -80.0f;

	static sf::Int32 constexpr diffFrameGood = 5;
	static sf::Int32 constexpr diffFrameGreat = 1;
	static sf::Int64 constexpr diffMicrosecondInterval = 17000;

	static float constexpr trackOffset = 100.0f;
	static float constexpr trackDistance = 150.0f;
	static sf::Int64 constexpr microsecondsPerFrame = 16667;

public:
	using TextureMap = std::unordered_map<std::string, sf::Texture>;
	enum class State { SCROLLING, HIT, DEAD, SEQUENCE_IN_PROGRESS };

	virtual ~KeyNote() {}

	virtual State getState() const = 0; // TODO: consider making this a base class non-virtual, with corresponding base class member variable
	virtual void sendKey(std::bitset<NUM_KEYS> pressed, sf::Int64 timeElapsed, TextureMap const& explodeTextures) = 0;
	virtual void updateFrame(sf::Int64 timeElapsed) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

};