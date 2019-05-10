#include "Deck.h"


Deck::Deck() {
	deck_name_ = "";
}

Deck::Deck(std::string file_name, std::vector<std::pair<std::string, std::string>> word_pairs) {
	deck_name_ = file_name;
	ofStringReplace(deck_name_, ".txt", "");

	card_index_ = 0;

	RemoveBlanks(word_pairs);

	for (std::pair<std::string, std::string> word_pair : word_pairs) {
		Card c(word_pair.first, word_pair.second);
		cards_.push_back(c);
	}	
}

Deck::Deck(std::string save_file_name) {
	card_index_ = 0;

	ofxJSONElement result;

	bool success = result.open(save_file_name);
	
	if (!success) {
		std::cout << "Couldn't open save file" << std::endl;
	} else {
		deck_name_ = result["deck_name_"].asString();
		cards_.clear();
		Json::Value card_array = result["cards_"];

		for (Json::Value::ArrayIndex i = 0; i != card_array.size(); i++) {
			if (card_array[i].isMember("front_")) {
				cards_.push_back(Card(card_array[i]["front_"].asString(), card_array[i]["back_"].asString()));
			}
		}
	}
}

Card Deck::GetFlashcard() {
	card_index_ %= cards_.size();
	return cards_[card_index_++];
}

std::string Deck::GetDeckName() {
	return deck_name_;
}

std::vector<Card> Deck::GetCards() {
	return cards_;
}

void Deck::SaveToFile() {
	Json::Value root;
	Json::Value cards(Json::arrayValue);
	Json::StyledStreamWriter writer;

	root["deck_name_"] = deck_name_;

	for (Card c : cards_) {
		cards.append(Json::Value(SaveCard(c)));
	}

	root["cards_"] = cards;

	std::ofstream save_file(".\\data\\" + deck_name_ + ".json");
	writer.write(save_file, root);
	save_file.close();
}

Json::Value Deck::SaveCard(Card c) {
	Json::Value result;
	result["front_"] = c.GetFront();
	result["back_"] = c.GetBack();
	return result;
}

void Deck::RemoveBlanks(std::vector<std::pair<std::string, std::string>> &word_pairs) {
	for (unsigned int i = 0; i < word_pairs.size(); i++) {
		if (word_pairs[i].second == "") {
			word_pairs.erase(word_pairs.begin() + i);
			i--;
		}
	}
}
