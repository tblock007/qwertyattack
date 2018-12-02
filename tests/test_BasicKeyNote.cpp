#include "../BasicKeyNote.hpp"
#include "../common.hpp"
#include "catch.hpp"

namespace qa {

TEST_CASE("BasicKeyNote Creation", "[keynote]")
{
   auto dummyTexture = std::make_shared<sf::Texture>();
   dummyTexture->loadFromFile(explodeGreatTextureFile);
   sf::Int64 sampleTargetHitTime = 1000000;

   BasicKeyNote eut('A', keyNoteSpeed, sampleTargetHitTime, dummyTexture, dummyTexture, dummyTexture, dummyTexture);

   REQUIRE(eut.getState() == KeyNoteState::SCROLLING);
}

TEST_CASE("BasicKeyNote Receive Correct Key Outside Zone", "[keynote]")
{
   auto dummyTexture = std::make_shared<sf::Texture>();
   dummyTexture->loadFromFile(explodeGreatTextureFile);
   std::bitset<NUM_KEYS> pressed;
   sf::Int64 sampleTargetHitTime = 1000000;

   BasicKeyNote eut('A', keyNoteSpeed, sampleTargetHitTime, dummyTexture, dummyTexture, dummyTexture, dummyTexture);
   pressed.set('A' - 'A');

   REQUIRE(!eut.sendKey(pressed, sampleTargetHitTime - 500000).has_value());
   REQUIRE(eut.getState() == KeyNoteState::SCROLLING);
   REQUIRE(!eut.sendKey(pressed, sampleTargetHitTime - 200000).has_value());
   REQUIRE(eut.getState() == KeyNoteState::SCROLLING);
   REQUIRE(!eut.sendKey(pressed, sampleTargetHitTime + 200000).has_value());
   REQUIRE(eut.getState() == KeyNoteState::SCROLLING);
   REQUIRE(!eut.sendKey(pressed, sampleTargetHitTime + 500000).has_value());
   REQUIRE(eut.getState() == KeyNoteState::SCROLLING);
}

TEST_CASE("BasicKeyNote Receive Correct Key Inside Zone Perfect", "[keynote]")
{
   auto dummyTexture = std::make_shared<sf::Texture>();
   dummyTexture->loadFromFile(explodeGreatTextureFile);
   std::bitset<NUM_KEYS> pressed;
   sf::Int64 sampleTargetHitTime = 1000000;

   BasicKeyNote eut('A', keyNoteSpeed, sampleTargetHitTime, dummyTexture, dummyTexture, dummyTexture, dummyTexture);
   pressed.set('A' - 'A');

   REQUIRE(eut.sendKey(pressed, sampleTargetHitTime).value() == Judgement::GREAT);
   REQUIRE(eut.getState() == KeyNoteState::DISAPPEARING);
}

TEST_CASE("BasicKeyNote Receive Correct Key Inside Zone Great", "[keynote]")
{
   auto dummyTexture = std::make_shared<sf::Texture>();
   dummyTexture->loadFromFile(explodeGreatTextureFile);
   std::bitset<NUM_KEYS> pressed;
   sf::Int64 sampleTargetHitTime = 1000000;

   // compute the time interval for GREATs based on judgement configuration
   // then, ensure that presses that fall just outside this window register as GOOD, while those inside register as
   // GREAT

   sf::Int64 minGreatTime = sampleTargetHitTime + (-1 * qa::diffFrameGreat) * qa::diffMicrosecondInterval;
   sf::Int64 maxGreatTime = sampleTargetHitTime + (1 * qa::diffFrameGreat + 1) * qa::diffMicrosecondInterval;

   BasicKeyNote eut('A', keyNoteSpeed, sampleTargetHitTime, dummyTexture, dummyTexture, dummyTexture, dummyTexture);
   pressed.set('A' - 'A');

   REQUIRE(eut.sendKey(pressed, minGreatTime - 1).value() == Judgement::GOOD);
   REQUIRE(eut.getState() == KeyNoteState::DISAPPEARING);

   BasicKeyNote eut2('B', keyNoteSpeed, sampleTargetHitTime, dummyTexture, dummyTexture, dummyTexture, dummyTexture);
   pressed.reset('A' - 'A');
   pressed.set('B' - 'A');

   REQUIRE(eut2.sendKey(pressed, minGreatTime).value() == Judgement::GREAT);
   REQUIRE(eut2.getState() == KeyNoteState::DISAPPEARING);

   BasicKeyNote eut3('C', keyNoteSpeed, sampleTargetHitTime, dummyTexture, dummyTexture, dummyTexture, dummyTexture);
   pressed.reset('B' - 'A');
   pressed.set('C' - 'A');

   REQUIRE(eut3.sendKey(pressed, maxGreatTime).value() == Judgement::GREAT);
   REQUIRE(eut3.getState() == KeyNoteState::DISAPPEARING);

   BasicKeyNote eut4('D', keyNoteSpeed, sampleTargetHitTime, dummyTexture, dummyTexture, dummyTexture, dummyTexture);
   pressed.reset('C' - 'A');
   pressed.set('D' - 'A');

   REQUIRE(eut4.sendKey(pressed, maxGreatTime + 1).value() == Judgement::GOOD);
   REQUIRE(eut4.getState() == KeyNoteState::DISAPPEARING);
}

TEST_CASE("BasicKeyNote Receive Correct Key Inside Zone Good", "[keynote]")
{
   auto dummyTexture = std::make_shared<sf::Texture>();
   dummyTexture->loadFromFile(explodeGreatTextureFile);
   std::bitset<NUM_KEYS> pressed;
   sf::Int64 sampleTargetHitTime = 1000000;

   // compute the time interval for GREATs based on judgement configuration
   // then, ensure that presses that fall just outside this window do not register as hits, while those inside register
   // as GOOD

   sf::Int64 minGoodTime = sampleTargetHitTime + (-1 * qa::diffFrameGood) * qa::diffMicrosecondInterval;
   sf::Int64 maxGoodTime = sampleTargetHitTime + (1 * qa::diffFrameGood + 1) * qa::diffMicrosecondInterval;

   BasicKeyNote eut('A', keyNoteSpeed, sampleTargetHitTime, dummyTexture, dummyTexture, dummyTexture, dummyTexture);
   pressed.set('A' - 'A');

   REQUIRE(!eut.sendKey(pressed, minGoodTime - 1).has_value());
   REQUIRE(eut.getState() == KeyNoteState::SCROLLING);

   BasicKeyNote eut2('B', keyNoteSpeed, sampleTargetHitTime, dummyTexture, dummyTexture, dummyTexture, dummyTexture);
   pressed.reset('A' - 'A');
   pressed.set('B' - 'A');

   REQUIRE(eut2.sendKey(pressed, minGoodTime).value() == Judgement::GOOD);
   REQUIRE(eut2.getState() == KeyNoteState::DISAPPEARING);

   BasicKeyNote eut3('C', keyNoteSpeed, sampleTargetHitTime, dummyTexture, dummyTexture, dummyTexture, dummyTexture);
   pressed.reset('B' - 'A');
   pressed.set('C' - 'A');

   REQUIRE(eut3.sendKey(pressed, maxGoodTime).value() == Judgement::GOOD);
   REQUIRE(eut3.getState() == KeyNoteState::DISAPPEARING);

   BasicKeyNote eut4('D', keyNoteSpeed, sampleTargetHitTime, dummyTexture, dummyTexture, dummyTexture, dummyTexture);
   pressed.reset('C' - 'A');
   pressed.set('D' - 'A');

   REQUIRE(!eut4.sendKey(pressed, maxGoodTime + 1).has_value());
   REQUIRE(eut4.getState() == KeyNoteState::SCROLLING);
}

}  // namespace qa
