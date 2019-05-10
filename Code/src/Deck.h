#pragma once

#include "Corpus.h"
#include "Card.h"
#include "ofxJSON.h"
#include <iostream>
#include <fstream>

class Deck {
private:
	std::string deck_name_;
	std::vector<Card> cards_;
	int card_index_;

	Json::Value SaveCard(Card c);

public:
	Deck();
	Deck(std::string file_name, std::vector<std::pair<std::string, std::string>> word_pairs);
	Deck(std::string save_file_name);

	Card GetFlashcard();

	std::string GetDeckName();
	std::vector<Card> GetCards();

	void SaveToFile();

	static void RemoveBlanks(std::vector<std::pair<std::string, std::string>> &word_pairs);
};