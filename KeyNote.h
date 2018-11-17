#include <unordered_map>
#include <SFML/Graphics.hpp>


// --------------------------------------------------------------------------------
/// <summary>
/// Represents one KeyNote, the entity that scrolls across the screen during a SongRun, whose key is to be pressed by the player when it enters the hit zone
///
/// Implements the Drawable interface, allowing it to be drawn on a RenderTarget
/// </summary>
// --------------------------------------------------------------------------------
class KeyNote : public sf::Drawable {
public:
	using TextureMap = std::unordered_map<std::string, sf::Texture>;
	enum class State { SCROLLING, HIT, DEAD };

	KeyNote(char c, float speed, sf::Int64 targetHitTime, TextureMap const& pulseTextures);

	char getKey() const;
	State getState() const;
	sf::Vector2f const& getPosition() const;

	void hit(sf::Int64 timeElapsed, TextureMap const& explodeTextures);
	void kill();
	void move(float dx, float dy);
	void updateFrame(sf::Int64 timeElapsed);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	static sf::Int32 constexpr width = 80;
	static sf::Int32 constexpr height = 80;
	static sf::Int32 constexpr leftOffset = 25;
	static sf::Int32 constexpr topOffset = 24;
	static sf::Int32 constexpr pixelsBetweenSprites = 128;
	static sf::Int32 constexpr pulseFrames = 125;
	static sf::Int32 constexpr explodeFrames = 37;
	static float constexpr zoneLeftBound = 40.0f;

	State _state;
	char _key;

	float _speed;
	float _y;

	sf::Sprite _image;
	sf::Int32 _track;	
	sf::Int64 _microsecondsPerFrame;
	sf::Int64 _hitTime;
	sf::Int64 _targetHitTime;

};