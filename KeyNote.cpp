#include "KeyNote.h"



// ********************************************************************************
/// <summary>
/// Constructor for KeyNote
/// </summary>
/// <param name="c">The character</param>
/// <param name="pulseTextures">The map of textures from which to load the "pulse" animation
/// <changed>tblock,11/15/2018</changed>
// ********************************************************************************
KeyNote::KeyNote(char c, float speed, sf::Int64 targetHitTime, TextureMap const& pulseTextures) : _state(KeyNote::State::SCROLLING), _key(c), _speed(speed), _targetHitTime(targetHitTime) {
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
		_track = 0;
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
		_track = 1;
		break;


	case 'Z':
	case 'X': 
	case 'C':
	case 'V':
	case 'B':
	case 'N':
	case 'M':
		_track = 2;
		break;
	}
	
	_image.setTexture(pulseTextures.at(std::string(1, _key)));
	_image.setTextureRect(sf::IntRect(leftOffset, topOffset, width, height));
	_y = 100.0f + (_track * 150.0f);
	_image.setPosition(1200.0f, _y);

	_microsecondsPerFrame = 16667;
}



// ********************************************************************************
/// <summary>
/// Gets the character associated with the KeyNote
/// </summary>
/// <returns>The character associated with the KeyNote</returns>
/// <changed>tblock,11/15/2018</changed>
// ********************************************************************************
char KeyNote::getKey() const {
	return _key;
}



// ********************************************************************************
/// <summary>
/// Gets the state of the KeyNote
/// </summary>
/// <returns>The state of the KeyNote</returns>
/// <changed>tblock,11/15/2018</changed>
// ********************************************************************************
KeyNote::State KeyNote::getState() const {
	return _state;
}



// ********************************************************************************
/// <summary>
/// Gets the current position of the KeyNote
/// </summary>
/// <returns>The current position of the KeyNote</returns>
/// <changed>tblock,11/15/2018</changed>
// ********************************************************************************
sf::Vector2f const& KeyNote::getPosition() const {
	return _image.getPosition();
}



// ********************************************************************************
/// <summary>
/// Indicates that the KeyNote has had its corresponding key pressed while in the hit zone
/// </summary>
/// <param name="timeElapsed">A (relative) time in microseconds that indicates when the KeyNote was hit</param>
/// <param name="explodeTextures">The map of textures from which to load the "explode" animation</param>
/// <changed>tblock,11/15/2018</changed>
// ********************************************************************************
void KeyNote::hit(sf::Int64 timeElapsed, TextureMap const& explodeTextures) {
	_state = State::HIT;
	_hitTime = timeElapsed;
	_image.setTexture(explodeTextures.at(std::string(1, _key)));
	_image.setTextureRect(sf::IntRect(leftOffset, topOffset, width, height));
}



// ********************************************************************************
/// <summary>
/// Indicates that the KeyNote was missed and has moved off-screen
/// </summary>
/// <changed>tblock,11/15/2018</changed>
// ********************************************************************************
void KeyNote::kill() {
	_state = State::DEAD;
}



// ********************************************************************************
/// <summary>
/// Moves the KeyNote by a specified amount
/// </summary>
/// <param name="dx">The offset to move in the x-direction (negative for left)</param>
/// <param name="dy">The offset to move in the y-direction (negative for up)</param>
/// <changed>tblock,11/15/2018</changed>
// ********************************************************************************
void KeyNote::move(float dx, float dy) {
	_image.move(dx, dy);
}



// ********************************************************************************
/// <summary>
/// Updates the image of the KeyNote to the appropriate frame of its animation
/// </summary>
/// <param name="timeElapsed">A (relative) time in microseconds indicating time elapsed since some reference; used to compute frame of the animation</param>
/// <changed>tblock,11/15/2018</changed>
// ********************************************************************************
void KeyNote::updateFrame(sf::Int64 timeElapsed) {
	if (_state == State::SCROLLING) {
		_image.setPosition((_targetHitTime - timeElapsed) * _speed + zoneLeftBound, _y);
		sf::Int32 frame = (static_cast<sf::Int32>(timeElapsed / _microsecondsPerFrame)) % pulseFrames;
		_image.setTextureRect(sf::IntRect(leftOffset, topOffset + frame * pixelsBetweenSprites, width, height));
	}
	else if (_state == State::HIT) {
		_image.setPosition(zoneLeftBound, _y);
		sf::Int32 frame = (static_cast<sf::Int32>((timeElapsed - _hitTime) / _microsecondsPerFrame));
		if (frame >= explodeFrames) {
			_state = State::DEAD;
		}
		else {
			_image.setTextureRect(sf::IntRect(leftOffset, topOffset + frame * pixelsBetweenSprites, width, height));
		}
	}
}





// ********************************************************************************
/// <summary>
/// Draws the KeyNote on a RenderTarget (Drawable interface requirement)
/// </summary>
/// <param name="target">The RenderTarget on which to draw the KeyNote</param>
/// <param name="states">The RenderStates which control the render</param>
/// <changed>tblock,11/15/2018</changed>
// ********************************************************************************
void KeyNote::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_image);
}