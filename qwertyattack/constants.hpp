#pragma once

#include <SFML/Config.hpp>
#include <string>

namespace qa {

// TODO: make some of these configurable eventually

static sf::Uint32 constexpr NUM_KEYS = 26;
static sf::Uint32 constexpr frameLimit = 144;

// The default KeyNote speed, in pixels per microsecond.
static float constexpr keyNoteSpeed = 0.0005f;

// Constants describing layout.
static sf::Uint32 constexpr pixelThreshold
    = 640;  // buffer half a screen of KeyNotes (technically a problem if KeyNotes start travelling too fast)
static sf::Uint32 constexpr fullscreenWidth = 1280;
static sf::Uint32 constexpr width = 80;
static sf::Uint32 constexpr height = 80;
static sf::Uint32 constexpr leftOffset = 25;
static sf::Uint32 constexpr topOffset = 24;
static sf::Uint32 constexpr pixelsBetweenSprites = 128;
static float constexpr trackOffset = 100.0f;
static float constexpr trackDistance = 150.0f;
static float constexpr zoneLeftBound = 40.0f;
static float constexpr deathBound = -80.0f;

// Timing window constants. Based on frames at 60 fps.
static sf::Int64 constexpr diffFrameGood = 4;
static sf::Int64 constexpr diffFrameGreat = 2;
static sf::Int64 constexpr diffMicrosecondInterval = 16667;
static sf::Int64 constexpr minMicrosecondGood = (-1 * diffFrameGood) * diffMicrosecondInterval;
static sf::Int64 constexpr maxMicrosecondGood = (diffFrameGood + 1) * diffMicrosecondInterval;
static sf::Int64 constexpr minMicrosecondGreat = (-1 * diffFrameGreat) * diffMicrosecondInterval;
static sf::Int64 constexpr maxMicrosecondGreat = (diffFrameGreat + 1) * diffMicrosecondInterval;

// Texture files for displaying KeyNotes.
// TODO: rename this now that we've removed the pulsing
static std::string const pulseTextureFile = "resources/keynotes/keynote_pulse.png";

// Constants that dictate how judgements are shown on screen.
// They should be shown within the zone, just above each track.
static std::string const judgementGreatTextureFile = "resources/ui/judgement_great.png";
static std::string const judgementGoodTextureFile = "resources/ui/judgement_good.png";
static float constexpr judgementOffsetFromTrack = 20.0f;
static float constexpr judgementFloatSpeed = 0.0001f;           // pixels per microsecond
static sf::Uint32 constexpr judgementDisplayDuration = 200000;  // microseconds

}  // namespace qa
