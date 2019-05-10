#pragma once


#include <string>

class Card {
private:
	std::string front_;
	std::string back_;

public:
	Card() {}
	Card(std::string l2, std::string l1);

	std::string GetFront();
	std::string GetBack();
};