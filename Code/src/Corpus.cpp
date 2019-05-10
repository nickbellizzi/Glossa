#include "Corpus.h"

Corpus::Corpus() {
	total_word_count_ = 0;
}

Corpus::Corpus(std::string text) {
	text = ToLower(CleanText(text));
	std::vector<std::string> words = ofSplitString(text, " ", true, true);
	total_word_count_ = words.size();

	for (std::string s : words) {
		if (frequencies_.find(s) == frequencies_.end()) {
			frequencies_[s] = 1;
		} else {
			frequencies_[s]++;
		}
	}

	sorted_frequencies_ = SortMapByValue();

}

std::map<std::string, int> Corpus::GetFrequencies() {
	return frequencies_;
}

std::vector<pairs> Corpus::GetSortedFrequencies() {
	return sorted_frequencies_;
}

std::string Corpus::CleanText(std::string text) {
		ofStringReplace(text, "…", "");
		ofStringReplace(text, "&", "");
		ofStringReplace(text, "\"", "");
		ofStringReplace(text, "“", "");
		ofStringReplace(text, "”", "");
		ofStringReplace(text, ",", "");
		ofStringReplace(text, "–", "");
		ofStringReplace(text, "-", "");
		ofStringReplace(text, "—", "");
		ofStringReplace(text, ":", "");
		ofStringReplace(text, ";", "");
		ofStringReplace(text, "«", "");
		ofStringReplace(text, "»", "");
		ofStringReplace(text, "(", "");
		ofStringReplace(text, ")", "");
		ofStringReplace(text, "!", "");
		ofStringReplace(text, "¡", "");;
		ofStringReplace(text, "?", "");;
		ofStringReplace(text, "¿", "");;
		ofStringReplace(text, ".", "");
		return text;
}

std::string Corpus::ToLower(std::string text) {
	std::map<char, char> uppercase_accents =
	{
		{'Á', 'á'},
		{'À', 'à'},
		{'Ä', 'ä'},
		{'Å', 'å'},
		{'Â', 'â'},
		{'Ã', 'ã'},
		{'Æ', 'æ'},
		{'É', 'é'},
		{'È', 'è'},
		{'Ë', 'ë'},
		{'Ê', 'ê'},
		{'Î', 'î'},
		{'Í', 'í'},
		{'Ì', 'ì'},
		{'Ï', 'ï'},
		{'Ô', 'ô'},
		{'Ó', 'Ó'},
		{'Ò', 'ò'},
		{'Ö', 'ö'},
		{'Õ', 'õ'},
		// {'Ø', 'ø'}, ø not allowed as character
		{'Û', 'û'},
		{'Ú', 'ú'},
		{'Ù', 'ù'},
		{'Ü', 'ü'},
		{'Ÿ', 'ÿ'},
		{'Ç', 'ç'},
		{'Ñ', 'ñ'}	
	};
	// More can be added as needed for the orthography of Polish, Czech, etc.

	std::string str = "";
	for (char c : text) {
		int char_value = (int)c;
		if (char_value >= 60 && char_value <= 90) {
			char add = (char)(char_value + 32);
			str += add;
		} else if (uppercase_accents.find(c) != uppercase_accents.end()) {
			str += uppercase_accents[c];
		} else {
			str += c;
		}
	}
	return str;
}

std::vector<pairs> Corpus::SortMapByValue() {
	// From https://www.techiedelight.com/sort-map-values-cpp/

	std::vector<pairs> vec;

	// copy key-value pairs from the map to the vector
	std::copy(frequencies_.begin(), frequencies_.end(), std::back_inserter<std::vector<pairs>>(vec));

	// sort the vector by increasing order of its pair's second value
	// if second value are equal, order by the pair's first value
	std::sort(vec.begin(), vec.end(),
		[](const pairs & l, const pairs & r) {
			if (l.second != r.second) {
				return l.second > r.second;
			}

			return l.first < r.first;
		});

	return vec;
}

std::vector<std::string> Corpus::GetMostCommonWords(double learning_rate) {
	if (learning_rate <= 0 || learning_rate > 1) {
		learning_rate = 0.95;
	}

	double cumulative = 0;
	std::vector<std::string> words;

	for (auto const& pair : sorted_frequencies_) {
		if (cumulative > learning_rate) {
			break;
		} else {
			cumulative += ((double)pair.second) / total_word_count_;
			words.push_back(pair.first);
		}
	}

	return words;
}