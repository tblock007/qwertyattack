#include "BasicKeyNote.h"



// ********************************************************************************
/// <summary>
/// Constructor for BasicKeyNote
/// </summary>
/// <param name="c">The character</param>
/// <param name="speed">The speed at which the BasicKeyNote will travel (pixels/microsecond)</param>
/// <param name="targetHitTime">The time at which the corresponding key should be pressed</param>
/// <param name="pulseTextures">The map of textures from which to load the "pulse" animation</param>
/// <changed>tblock,11/17/2018</changed>
// ********************************************************************************
BasicKeyNote::BasicKeyNote(char c, float speed, sf::Int64 targetHitTime, TextureMap const& pulseTextures) : _state(KeyNote::State::SCROLLING), _key(c), _speed(speed), _targetHitTime(targetHitTime) {
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
		_y = trackOffset + (0 * trackDistance);
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
		_y = trackOffset + (1 * trackDistance);
		break;


	case 'Z':
	case 'X': 
	case 'C':
	case 'V':
	case 'B':
	case 'N':
	case 'M':
		_y = trackOffset + (2 * trackDistance);
		break;
	}
	
	_image.setTexture(pulseTextures.at(std::string(1, _key)));
	_image.setTextureRect(sf::IntRect(leftOffset, topOffset, width, height));
}



// ********************************************************************************
/// <summary>
/// Gets the state of the BasicKeyNote
/// </summary>
/// <returns>The state of the KeyNote</returns>
/// <changed>tblock,11/15/2018</changed>
// ********************************************************************************
KeyNote::State BasicKeyNote::getState() const {
	return _state;
}




// ********************************************************************************
/// <summary>
/// Handles a key press from the user
/// </summary>
/// <param name="pressed">A bitmask indicating which keys were pressed</param>
/// <param name="timeElapsed">A (relative) time in microseconds that indicates when the key was pressed</param>
/// <param name="explodeTextures">The map of textures from which to load the "explode" animation</param>
/// <changed>tblock,11/17/2018</changed>
// ********************************************************************************
void BasicKeyNote::sendKey(std::bitset<NUM_KEYS> pressed, sf::Int64 timeElapsed, TextureMap const& explodeTextures) {
	if (_image.getPosition().x >= zoneLeftBound - 30 && _image.getPosition().x <= zoneLeftBound + 30) { // TODO: make this zone detection nice w.r.t. frames
		if (_state == State::SCROLLING) {
			if (pressed.test(_key - 'A')) {
				_state = State::HIT;
				_hitTime = timeElapsed;
				_image.setTexture(explodeTextures.at(std::string(1, _key)));
				_image.setTextureRect(sf::IntRect(leftOffset, topOffset, width, height));
			}
		}
	}	
}



// ********************************************************************************
/// <summary>
/// Updates the image of the BasicKeyNote to the appropriate frame of its animation.  This function handles both scrolling and hit animations.
/// </summary>
/// <param name="timeElapsed">A (relative) time in microseconds indicating time elapsed since some reference; used to compute frame of the hit animation, or proper position during scrolling</param>
/// <changed>tblock,11/15/2018</changed>
// ********************************************************************************
void BasicKeyNote::updateFrame(sf::Int64 timeElapsed) {
	if (_state == State::SCROLLING) {
		if (_image.getPosition().x < deathBound) {
			_state = State::DEAD;
		}
		else {
			_image.setPosition((_targetHitTime - timeElapsed) * _speed + zoneLeftBound, _y);
			sf::Int32 frame = (static_cast<sf::Int32>(timeElapsed / microsecondsPerFrame)) % pulseFrames;
			_image.setTextureRect(sf::IntRect(leftOffset, topOffset + frame * pixelsBetweenSprites, width, height));
		}
	}
	else if (_state == State::HIT) {
		_image.setPosition(zoneLeftBound, _y);
		sf::Int32 frame = (static_cast<sf::Int32>((timeElapsed - _hitTime) / microsecondsPerFrame));
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
/// Draws the BasicKeyNote on a RenderTarget (Drawable interface requirement)
/// </summary>
/// <param name="target">The RenderTarget on which to draw the BasicKeyNote</param>
/// <param name="states">The RenderStates which control the render</param>
/// <changed>tblock,11/15/2018</changed>
// ********************************************************************************
void BasicKeyNote::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_image);
}