#pragma once
#include <bitset>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "KeyNote.h"


// --------------------------------------------------------------------------------
/// <summary>
/// Represents a basic KeyNote, which only requires a single keypress from the player
///
/// Implements the Drawable interface, allowing it to be drawn on a RenderTarget
/// </summary>
// --------------------------------------------------------------------------------
class BasicKeyNote : public KeyNote {
public:

	BasicKeyNote(char c, float speed, sf::Int64 targetHitTime, TextureMap const& pulseTextures);
	
	State getState() const override;
	void sendKey(std::bitset<NUM_KEYS> pressed, sf::Int64 timeElapsed, TextureMap const& explodeTextures) override;
	void updateFrame(sf::Int64 timeElapsed) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:


	State _state;
	char _key;

	float _speed;
	float _y;

	sf::Sprite _image;
	sf::Int64 _hitTime;
	sf::Int64 _targetHitTime;

};