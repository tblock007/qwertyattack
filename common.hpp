#pragma once

#include <cctype>
#include <SFML/System.hpp>

namespace qa {
enum class KeyNoteState { SCROLLING, DISAPPEARING, EXPLODING, DEAD, SEQUENCE_IN_PROGRESS };
enum class Judgement { GREAT, GOOD, MISS };

// TODO: organize these - perhaps an entity that stores global configuration parameters
static sf::Int64 constexpr pixelThreshold
    = 640;  // buffer half a screen of KeyNotes (technically a problem if KeyNotes start travelling too fast)
static sf::Int64 constexpr fullscreenWidth = 1280;
static float constexpr keyNoteSpeed = 0.0005f;

static sf::Int32 constexpr NUM_KEYS = 26;
static sf::Int32 constexpr width = 80;
static sf::Int32 constexpr height = 80;
static sf::Int32 constexpr leftOffset = 25;
static sf::Int32 constexpr topOffset = 24;
static sf::Int32 constexpr pixelsBetweenSprites = 128;
static sf::Int32 constexpr pulseFrames = 1;
static sf::Int32 constexpr disappearFrames = 1;
static sf::Int32 constexpr explodeFrames = 33;
static float constexpr zoneLeftBound = 40.0f;
static float constexpr deathBound = -80.0f;

static sf::Int64 constexpr diffFrameGood = 3;
static sf::Int64 constexpr diffFrameGreat = 1;
static sf::Int64 constexpr diffMicrosecondInterval = 16667;
static sf::Int64 constexpr minMicrosecondGood = (-1 * diffFrameGood) * diffMicrosecondInterval;
static sf::Int64 constexpr maxMicrosecondGood = (diffFrameGood + 1) * diffMicrosecondInterval;
static sf::Int64 constexpr minMicrosecondGreat = (-1 * diffFrameGreat) * diffMicrosecondInterval;
static sf::Int64 constexpr maxMicrosecondGreat = (diffFrameGreat + 1) * diffMicrosecondInterval;


static float constexpr trackOffset = 100.0f;
static float constexpr trackDistance = 150.0f;
static sf::Int64 constexpr microsecondsPerFrame = 16667;

static std::string const pulseTextureFile = "resources/keynotes/keynote_pulse.png";
static std::string const disappearTextureFile = "resources/keynotes/keynote_disappear.png";
static std::string const explodeGreatTextureFile = "resources/keynotes/explode_great.png";
static std::string const explodeGoodTextureFile = "resources/keynotes/explode_good.png";

static inline void ltrim(std::string& s)
{
   s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) { return !std::isspace(c); }));
}

static inline void rtrim(std::string& s)
{
   s.erase(std::find_if(s.rbegin(), s.rend(), [](int c) { return !std::isspace(c); }).base(), s.end());
}

static inline void trim(std::string& s)
{
   ltrim(s);
   rtrim(s);
}
}  // namespace qa