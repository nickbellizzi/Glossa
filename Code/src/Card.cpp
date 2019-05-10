#include "Card.h"

Card::Card(std::string l2, std::string l1) {
	front_ = l2;
	back_ = l1;
}

std::string Card::GetFront() {
	return front_;
}

std::string Card::GetBack() {
	return back_;
}