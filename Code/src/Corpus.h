#pragma once

#include "ofUtils.h"

#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <functional>


typedef std::pair<std::string, int> pairs;

class Corpus {
private:
	std::map<std::string, int> frequencies_;
	std::vector<pairs> sorted_frequencies_;
	int total_word_count_;

	std::vector<pairs> SortMapByValue();

public:
	Corpus();
	Corpus(std::string text);

	std::map<std::string, int> GetFrequencies();
	std::vector<pairs> GetSortedFrequencies();

	static std::string CleanText(std::string text);
	static std::string ToLower(std::string text);

	std::vector<std::string> GetMostCommonWords(double learning_rate = 0.95);
};

