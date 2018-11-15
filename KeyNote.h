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

	KeyNote(char c, TextureMap const& pulseTextures);

	char getKey() const;
	State getState() const;
	sf::Vector2f const& getPosition() const;

	void hit(sf::Int64 timeElapsed, TextureMap const& explodeTextures);
	void kill();
	void move(float dx, float dy);
	void updateFrame(sf::Int64 timeElapsed);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	static sf::Int32 const width = 80;
	static sf::Int32 const height = 80;
	static sf::Int32 const leftOffset = 25;
	static sf::Int32 const topOffset = 24;
	static sf::Int32 const pixelsBetweenSprites = 128;
	static sf::Int32 const pulseFrames = 125;
	static sf::Int32 const explodeFrames = 37;

	State _state;
	char _key;
	sf::Sprite _image;
	sf::Int32 _track;	
	sf::Int64 _microsecondsPerFrame;
	sf::Int64 _hitTime;

};