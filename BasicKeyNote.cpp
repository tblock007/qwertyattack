#include "BasicKeyNote.h"



// ********************************************************************************
/// <summary>
/// Constructor for BasicKeyNote
/// </summary>
/// <param name="c">The character</param>
/// <param name="speed">The speed at which the BasicKeyNote will travel (pixels/microsecond)</param>
/// <param name="targetHitTime">The time at which the corresponding key should be pressed</param>
/// <param name="pulseTexture">A pointer to the texture to be used for the "pulse" animation</param>
/// <param name="disappearTexture">A pointer to the texture to be used for the "disappear" animation</param>
/// <param name="explodeGreatTexture">A pointer to the texture to be used for the "explode" animation when hit with GREAT timing</param>
/// <param name="explodeGoodTexture">A pointer to the texture to be used for the "explode" animation when hit with GOOD timing</param>
/// <changed>tblock,11/17/2018</changed>
// ********************************************************************************
BasicKeyNote::BasicKeyNote(char c, float speed, sf::Int64 targetHitTime, std::shared_ptr<sf::Texture> pulseTexture, std::shared_ptr<sf::Texture> disappearTexture, std::shared_ptr<sf::Texture> explodeGreatTexture, std::shared_ptr<sf::Texture> explodeGoodTexture) : _state(KeyNoteState::SCROLLING), _key(c), _speed(speed), _targetHitTime(targetHitTime), _pulseTexture(pulseTexture), _disappearTexture(disappearTexture), _explodeGreatTexture(explodeGreatTexture), _explodeGoodTexture(explodeGoodTexture) {
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
	
	_image.setTexture(*_pulseTexture);
	_image.setTextureRect(sf::IntRect(leftOffset + ((_key - 'A') * pixelsBetweenSprites), topOffset, width, height));
}



// ********************************************************************************
/// <summary>
/// Gets the state of the BasicKeyNote
/// </summary>
/// <returns>The state of the KeyNote</returns>
/// <changed>tblock,11/15/2018</changed>
// ********************************************************************************
KeyNoteState BasicKeyNote::getState() const {
	return _state;
}




// ********************************************************************************
/// <summary>
/// Handles a key press from the user
/// </summary>
/// <param name="pressed">A bitmask indicating which keys were pressed</param>
/// <param name="timeElapsed">A (relative) time in microseconds that indicates when the key was pressed</param>
/// <returns>A GREAT or GOOD judgement if the note was hit, otherwise an empty optional</returns>
/// <changed>tblock,11/20/2018</changed>
// ********************************************************************************
std::optional<Judgement> BasicKeyNote::sendKey(std::bitset<NUM_KEYS> pressed, sf::Int64 timeElapsed) {
	std::optional<Judgement> judgement;
	if (_state == KeyNoteState::SCROLLING) {
		if (pressed.test(_key - 'A')) {

			// compute frame differential from ideal
			sf::Int32 diffFrame = static_cast<sf::Int32>((timeElapsed - _targetHitTime) / diffMicrosecondInterval);
			if (diffFrame >= (-1 * diffFrameGood + 1) && diffFrame <= diffFrameGood + 1) {
				_state = KeyNoteState::DISAPPEARING;
				_hitTime = timeElapsed;
				_image.setTexture(*_disappearTexture);
				_image.setTextureRect(sf::IntRect(leftOffset + ((_key - 'A') * pixelsBetweenSprites), topOffset, width, height));

				if (diffFrame >= (-1 * diffFrameGreat + 1) && diffFrame <= diffFrameGreat + 1) {
					judgement = Judgement::GREAT;
					_explodeTexture = _explodeGreatTexture;
				}
				else {
					judgement = Judgement::GOOD;
					_explodeTexture = _explodeGoodTexture;
				}
			}
		}
	}
	return judgement;
}



// ********************************************************************************
/// <summary>
/// Updates the image of the BasicKeyNote to the appropriate frame of its animation.  This function handles both scrolling and hit animations.
/// </summary>
/// <param name="timeElapsed">A (relative) time in microseconds indicating time elapsed since some reference; used to compute frame of the hit animation, or proper position during scrolling</param>
/// <returns>A MISS judgement if the note was missed, otherwise an empty optional</returns>
/// <changed>tblock,11/20/2018</changed>
// ********************************************************************************
std::optional<Judgement> BasicKeyNote::updateFrame(sf::Int64 timeElapsed) {
	std::optional<Judgement> result;
	if (_state == KeyNoteState::SCROLLING) {
		if (_image.getPosition().x < deathBound) {
			_state = KeyNoteState::DEAD;
			result = Judgement::MISS;
		}
		else {
			_image.setPosition((_targetHitTime - timeElapsed) * _speed + zoneLeftBound, _y);
			sf::Int32 frame = (static_cast<sf::Int32>(timeElapsed / microsecondsPerFrame)) % pulseFrames;
			_image.setTextureRect(sf::IntRect(leftOffset + ((_key - 'A') * pixelsBetweenSprites), topOffset + frame * pixelsBetweenSprites, width, height));
		}
	}
	else if (_state == KeyNoteState::DISAPPEARING) {
		sf::Int32 frame = (static_cast<sf::Int32>((timeElapsed - _hitTime) / microsecondsPerFrame));
		if (frame >= disappearFrames) {
			_state = KeyNoteState::EXPLODING;
			_image.setTexture(*_explodeTexture);
			_image.setTextureRect(sf::IntRect(leftOffset + ((_key - 'A') * pixelsBetweenSprites), topOffset, width, height));
		}
		else {
			_image.setTextureRect(sf::IntRect(leftOffset + ((_key - 'A') * pixelsBetweenSprites), topOffset + frame * pixelsBetweenSprites, width, height));
		}
	}
	else if (_state == KeyNoteState::EXPLODING) {
		sf::Int32 frame = (static_cast<sf::Int32>((timeElapsed - _hitTime) / microsecondsPerFrame)) - disappearFrames;
		if (frame >= explodeFrames) {
			_state = KeyNoteState::DEAD;
		}
		else {
			_image.setTextureRect(sf::IntRect(leftOffset, topOffset + frame * pixelsBetweenSprites, width, height));
		}
	}
	return result;
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