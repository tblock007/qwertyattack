#include "../KeyChart.hpp"
#include "catch.hpp"

namespace qa {

TEST_CASE("Reading meta from KeyChart file", "[keychart]")
{
   KeyChart kut;
   kut.importFile("testdata/test1.kc", false);

   REQUIRE(kut.getSongFile() == "alphabet.ogg");
   REQUIRE(kut.getTitle() == "Alphabet Song");
   REQUIRE(kut.getArtist() == "Misc");
   REQUIRE(kut.getGenre() == "Variety");
}

TEST_CASE("KeyNote generation from importable", "[keychart]")
{
   KeyChart kut;
   kut.importFile("testdata/test1.kc", false);

   // ensure first KeyNote gets generated exactly when expected
   REQUIRE(!kut.getKeyNote(-1 + 10000000 - static_cast<sf::Int64>((fullscreenWidth + pixelThreshold) / keyNoteSpeed))
                .has_value());
   REQUIRE(kut.getKeyNote(10000000 - static_cast<sf::Int64>((fullscreenWidth + pixelThreshold) / keyNoteSpeed))
               .value()
               ->getState()
           == KeyNoteState::SCROLLING);

   // ensure second KeyNote gets generated exactly when expected
   REQUIRE(!kut.getKeyNote(-1 + 10500000 - static_cast<sf::Int64>((fullscreenWidth + pixelThreshold) / keyNoteSpeed))
                .has_value());
   REQUIRE(kut.getKeyNote(10500000 - static_cast<sf::Int64>((fullscreenWidth + pixelThreshold) / keyNoteSpeed))
               .value()
               ->getState()
           == KeyNoteState::SCROLLING);

   // test case in which four KeyNotes are ready to be added at a given frame
   REQUIRE(kut.getKeyNote(12500000 - static_cast<sf::Int64>((fullscreenWidth + pixelThreshold) / keyNoteSpeed))
               .value()
               ->getState()
           == KeyNoteState::SCROLLING);
   REQUIRE(kut.getKeyNote(12500010 - static_cast<sf::Int64>((fullscreenWidth + pixelThreshold) / keyNoteSpeed))
               .value()
               ->getState()
           == KeyNoteState::SCROLLING);
   REQUIRE(kut.getKeyNote(12500020 - static_cast<sf::Int64>((fullscreenWidth + pixelThreshold) / keyNoteSpeed))
               .value()
               ->getState()
           == KeyNoteState::SCROLLING);
   REQUIRE(kut.getKeyNote(12500030 - static_cast<sf::Int64>((fullscreenWidth + pixelThreshold) / keyNoteSpeed))
               .value()
               ->getState()
           == KeyNoteState::SCROLLING);
   REQUIRE(!kut.getKeyNote(12500040 - static_cast<sf::Int64>((fullscreenWidth + pixelThreshold) / keyNoteSpeed))
                .has_value());
}

TEST_CASE("KeyNote generation from readable", "[keychart]")
{
   KeyChart kut;
   kut.importFile("testdata/test2.kc", false);

   // ensure first KeyNote gets generated exactly when expected
   REQUIRE(!kut.getKeyNote(-1 + 10000000 - static_cast<sf::Int64>((fullscreenWidth + pixelThreshold) / keyNoteSpeed))
                .has_value());
   REQUIRE(kut.getKeyNote(10000000 - static_cast<sf::Int64>((fullscreenWidth + pixelThreshold) / keyNoteSpeed))
               .value()
               ->getState()
           == KeyNoteState::SCROLLING);

   // ensure second KeyNote gets generated exactly when expected
   REQUIRE(!kut.getKeyNote(-1 + 10500000 - static_cast<sf::Int64>((fullscreenWidth + pixelThreshold) / keyNoteSpeed))
                .has_value());
   REQUIRE(kut.getKeyNote(10500000 - static_cast<sf::Int64>((fullscreenWidth + pixelThreshold) / keyNoteSpeed))
               .value()
               ->getState()
           == KeyNoteState::SCROLLING);

   // test case in which four KeyNotes are ready to be added at a given frame
   REQUIRE(kut.getKeyNote(12500000 - static_cast<sf::Int64>((fullscreenWidth + pixelThreshold) / keyNoteSpeed))
               .value()
               ->getState()
           == KeyNoteState::SCROLLING);
   REQUIRE(kut.getKeyNote(12500010 - static_cast<sf::Int64>((fullscreenWidth + pixelThreshold) / keyNoteSpeed))
               .value()
               ->getState()
           == KeyNoteState::SCROLLING);
   REQUIRE(kut.getKeyNote(12500020 - static_cast<sf::Int64>((fullscreenWidth + pixelThreshold) / keyNoteSpeed))
               .value()
               ->getState()
           == KeyNoteState::SCROLLING);
   REQUIRE(kut.getKeyNote(12500030 - static_cast<sf::Int64>((fullscreenWidth + pixelThreshold) / keyNoteSpeed))
               .value()
               ->getState()
           == KeyNoteState::SCROLLING);
   REQUIRE(!kut.getKeyNote(12500040 - static_cast<sf::Int64>((fullscreenWidth + pixelThreshold) / keyNoteSpeed))
                .has_value());
}

}  // namespace qa
