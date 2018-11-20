#pragma once

#include <SFML/System.hpp>

enum class KeyNoteState { SCROLLING, HIT, DEAD, SEQUENCE_IN_PROGRESS };
enum class Judgement { GREAT, GOOD, MISS };

// TODO: organize these - perhaps an entity that stores global configuration parameters
static sf::Int64 constexpr pixelThreshold = 640; // buffer half a screen of KeyNotes (technically a problem if KeyNotes start travelling too fast)
static sf::Int64 constexpr fullscreenWidth = 1280;
static float constexpr keyNoteSpeed = 0.0005f;

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

static sf::Int32 constexpr diffFrameGood = 3;
static sf::Int32 constexpr diffFrameGreat = 1;
static sf::Int64 constexpr diffMicrosecondInterval = 17000;

static float constexpr trackOffset = 100.0f;
static float constexpr trackDistance = 150.0f;
static sf::Int64 constexpr microsecondsPerFrame = 16667;