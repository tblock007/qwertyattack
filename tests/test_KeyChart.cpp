#include "catch.hpp"
#include "../KeyChart.h"



TEST_CASE("Importing and extracting from KeyChart file #1", "[keychart]") {
		
	KeyChart kut;
	kut.importFile("testdata/test1.kc");
	
	REQUIRE(kut.getSongFile() == "alphabet.ogg");
	REQUIRE(kut.getTitle() == "Alphabet Song");
	REQUIRE(kut.getArtist() == "Misc");
	REQUIRE(kut.getGenre() == "Variety");
	
	REQUIRE(!kut.getKeyNote(0).has_value());
	REQUIRE(kut.getKeyNote(10000000).has_value());
}