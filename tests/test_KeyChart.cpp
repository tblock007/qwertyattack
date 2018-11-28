#include "../KeyChart.hpp"
#include "catch.hpp"

namespace qa {

TEST_CASE("Importing and extracting from KeyChart file #1", "[keychart]")
{
	std::cout << "STARTING" << std::endl;
   		KeyChart kut;
	std::cout << "CONSTRUCTED" << std::endl;
   		kut.importFile("./testdata/test1.kc");
	std::cout << "IMPORTED" << std::endl;

   		REQUIRE(kut.getSongFile() == "alphabet.ogg");
   		REQUIRE(kut.getTitle() == "Alphabet Song");
   		REQUIRE(kut.getArtist() == "Misc");
   		REQUIRE(kut.getGenre() == "Variety");

   		REQUIRE(!kut.getKeyNote(0).has_value());
   		REQUIRE(kut.getKeyNote(10000000).has_value());
}

}  // namespace qa