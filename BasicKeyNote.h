#pragma once
#include <bitset>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "common.h"
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

	BasicKeyNote(char c, float speed, sf::Int64 targetHitTime, std::shared_ptr<sf::Texture> pulseTexture, std::shared_ptr<sf::Texture> disappearTexture, std::shared_ptr<sf::Texture> explodeGreatTexture, std::shared_ptr<sf::Texture> explodeGoodTexture);
	
	KeyNoteState getState() const override;
	std::optional<Judgement> sendKey(std::bitset<NUM_KEYS> pressed, sf::Int64 timeElapsed) override;
	std::optional<Judgement> updateFrame(sf::Int64 timeElapsed) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:

	KeyNoteState _state;
	char _key;

	float _speed;
	float _y;

	sf::Sprite _image;
	sf::Int64 _hitTime;
	sf::Int64 _targetHitTime;

	std::shared_ptr<sf::Texture> _pulseTexture;
	std::shared_ptr<sf::Texture> _disappearTexture;
	std::shared_ptr<sf::Texture> _explodeTexture;
	std::shared_ptr<sf::Texture> _explodeGreatTexture;
	std::shared_ptr<sf::Texture> _explodeGoodTexture;

};