/* #define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Corpus.h"
#include "Deck.h"

TEST_CASE("Corpus tests") {

	SECTION("CleanText") {
		std::string original = "Hello, this is a test string! Will this test pass, do you think?";
		std::string expected = "Hello this is a test string Will this test pass do you think";

		REQUIRE(Corpus::CleanText(original) == expected);
	}

	SECTION("ToLower") {
		std::string original = "HÉŸ THÍS ÏS MY TÊST ÕKÅY";
		std::string expected = "héÿ thís ïs my têst õkåy";

		REQUIRE(Corpus::ToLower(original) == expected);
	}

	SECTION("Frequencies") {
		std::string str = "a c A b B c  C B C";
		Corpus c(str);		
		std::map<std::string, int> expected = { {"a", 2}, {"b", 3},  {"c", 4} };

		REQUIRE(c.GetFrequencies() == expected);
	}

	SECTION("Sorted Frequencies") {
		std::string str = "a c A b B c  C B C";
		Corpus c(str);
		std::vector<pairs> expected = { pairs("c", 4), pairs("b", 3),  pairs("a", 2) };

		REQUIRE(c.GetSortedFrequencies() == expected);
	}

	SECTION("Get Most Common") {
		std::string str = "a c A b B c  C B C";
		Corpus c(str);
		std::vector<std::string> expected = { "c", "b" };

		REQUIRE(c.GetMostCommonWords(0.60) == expected);
	}
}

TEST_CASE("Deck tests") {

	SECTION("JSON parsing") {
		ofxJSONElement result;
		std::string file_name = "basic_spanish.json";

		bool success = result.open(file_name);
		REQUIRE(success);

		REQUIRE(result["deck_name_"] == "basic_spanish");

		REQUIRE(result["cards_"][0]["front_"] == "hola");
		REQUIRE(result["cards_"][0]["back_"] == "hello");

		REQUIRE(result["cards_"][0]["front_"] == "hola");
		REQUIRE(result["cards_"][0]["back_"] == "hello");

		REQUIRE(result["cards_"][1]["front_"] == "perro");
		REQUIRE(result["cards_"][1]["back_"] == "dog");

		REQUIRE(result["cards_"][2]["front_"] == "gato");
		REQUIRE(result["cards_"][2]["back_"] == "cat");

		REQUIRE(result["cards_"][3]["front_"] == "sí");
		REQUIRE(result["cards_"][3]["back_"] == "yes");
	}

	SECTION("Removing words to ignore") {
		std::vector<std::pair<std::string, std::string>> word_pairs;
		
		std::pair<std::string, std::string> pair1("hola", "hello");
		word_pairs.push_back(pair1);
		std::pair<std::string, std::string> pair2("yo", "");
		word_pairs.push_back(pair2);
		std::pair<std::string, std::string> pair3("azul", "blue");
		word_pairs.push_back(pair3);

		Deck::RemoveBlanks(word_pairs);

		REQUIRE(word_pairs.size() == 2);
		REQUIRE(word_pairs[0].first == "hola");
		REQUIRE(word_pairs[0].second == "hello");
		REQUIRE(word_pairs[1].first == "azul");
		REQUIRE(word_pairs[1].second == "blue");
	}

	SECTION("Loading from save file") {
		Deck d("basic_spanish.json");
		
		REQUIRE(d.GetDeckName() == "basic_spanish");

		std::vector<Card> cards = d.GetCards();

		REQUIRE(cards.size() == 4);

		REQUIRE(cards[0].GetFront() == "hola");
		REQUIRE(cards[0].GetBack() == "hello");

		REQUIRE(cards[1].GetFront() == "perro");
		REQUIRE(cards[1].GetBack() == "dog");

		REQUIRE(cards[2].GetFront() == "gato");
		REQUIRE(cards[2].GetBack() == "cat");

		REQUIRE(cards[3].GetFront() == "sí");
		REQUIRE(cards[3].GetBack() == "yes");
	}
} */