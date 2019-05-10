#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	main_menu_ = true;
	flashcard_mode_ = false;
	front_side_ = false;
	back_side_ = false;

	ofTrueTypeFont::setGlobalDpi(72);

	verdana_small_.load(".\\extras\\verdana.ttf", 30, true, true);
	verdana_small_.setLineHeight(34.0f);
	verdana_small_.setLetterSpacing(1.035);

	verdana_medium_.load(".\\extras\\verdana.ttf", 45, true, true);
	verdana_medium_.setLineHeight(34.0f);
	verdana_medium_.setLetterSpacing(1.035);

	verdana_big_.load(".\\extras\\verdana.ttf", 60, true, true);
	verdana_big_.setLineHeight(34.0f);
	verdana_big_.setLetterSpacing(1.035);

	correct_sound_.load(".\\extras\\correct.mp3");
	incorrect_sound_.load(".\\extras\\incorrect.mp3");

	logo_.load(".\\extras\\glossa_logo.png");
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	double quarter = ofGetWidth() / 4;

	if (main_menu_) {
		ofBackgroundGradient(ofColor::aquamarine, ofColor::navy);

		int height = 460;
		
		verdana_small_.drawString("Press L to load a saved deck.", quarter, height + 50);
		verdana_small_.drawString("Press N to add a new file.", quarter, height + 100);
		verdana_small_.drawString("Press S to save a deck.", quarter, height + 150);
		verdana_small_.drawString("Press F to start flashcard mode.", quarter, height + 200);

		logo_.draw(180, 30);
	}

	if (flashcard_mode_) {
		ofColor orange(255, 72, 22);
		ofBackgroundGradient(ofColor::deepPink, orange);
	}
	
	if (front_side_) {
		std::string card_front = ConvertStringToUnicodeString(current_card_.GetFront());
		verdana_big_.drawString(card_front, 512 - 19 * card_front.length(), 100);
	}

	if (back_side_) {
		std::string card_back = ConvertStringToUnicodeString(current_card_.GetBack());
		verdana_big_.drawString(card_back, 512 - 56 / 3 * card_back.length(), ofGetHeight() * 3 / 8 + 70);
		ofDrawLine(30, 230, ofGetWidth() - 30, 230);

		verdana_small_.drawString("1", quarter, ofGetHeight() - 100);
		verdana_small_.drawString("2", ofGetWidth() - quarter, ofGetHeight() - 100);

		verdana_medium_.drawString("Incorrect", quarter - 100, ofGetHeight() - 150);
		verdana_medium_.drawString("Correct", ofGetWidth() - quarter - 75, ofGetHeight() - 150);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == 'n') {
		ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a text file containing L2 text");

		if (openFileResult.bSuccess) {
			processOpenFileSelection(openFileResult);
		}
	} else if (key == 's' && deck_.GetDeckName() != "") {
		deck_.SaveToFile();
	} else if (key == 'l') {
		ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a save file containing deck data");

		if (openFileResult.bSuccess) {
			processOpenFileSelection(openFileResult);
		}
	} else if (key == 'f' && deck_.GetDeckName() != "") {
		flashcard_mode_ = true;
		main_menu_ = false;
		front_side_ = true;
		current_card_ = deck_.GetFlashcard();
		correct_responses_[current_card_.GetFront()] = 0;
	} else if (key == ' ' && flashcard_mode_) {
		back_side_ = true;
	} else if ((key == '1' || key == '2') && !main_menu_ && back_side_) {
		if (key == '1') {
			incorrect_sound_.play();
			correct_responses_[current_card_.GetFront()] = 0;
		} else {
			correct_sound_.play();
			correct_responses_[current_card_.GetFront()]++;
		}

		if (isDeckFinished()) {
			main_menu_ = true;
			flashcard_mode_ = false;
			front_side_ = false;
			back_side_ = false;
		} else {
			front_side_ = true;
			back_side_ = false;
			current_card_ = deck_.GetFlashcard();

			if (correct_responses_.find(current_card_.GetFront()) != correct_responses_.end()) {
				while (correct_responses_[current_card_.GetFront()] >= 2) {
					current_card_ = deck_.GetFlashcard();
				}
			}
		}
	}
}

// Part of code from openFrameworks examples

void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult) {
	ofLogVerbose("getName(): " + openFileResult.getName());
	ofLogVerbose("getPath(): " + openFileResult.getPath());

	ofFile file(openFileResult.getPath());

	if (file.exists()) {

		ofLogVerbose("The file exists - now checking the type via file extension");
		string fileExtension = ofToUpper(file.getExtension());

		if (fileExtension == "TXT") {

			// From https://stackoverflow.com/questions/26121782/read-unicode-file-with-special-characters-using-stdwifstream

			std::wifstream wif(file.getAbsolutePath(), std::ios::binary);
			std::wstring convert;

			if (wif.is_open()) {
				// Apply BOM-sensitive UTF-16 facet
				wif.imbue(std::locale(wif.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::consume_header>));

				std::wstring wline;
				while (std::getline(wif, wline)) {

					for (auto c : wline) {
						if (c != L'\0')
							convert += c;
					}
				}

				wif.close();
			}

			// From http://www.cplusplus.com/forum/general/243349/#msg1079370

			std::wstring_convert< std::codecvt_utf16<wchar_t>, wchar_t > cvt;
			std::string str_text = cvt.to_bytes(convert);

			std::string simple_text = "";

			for (unsigned int i = 0; i < str_text.length(); i++) { // Every other character in str_text is '\0'
				if (i % 2 != 0 && (int)str_text[i] != '\r') {
					if (str_text[i] == '\r') {
						simple_text += " ";
					} else if (str_text[i] == '\x19') {
						simple_text += "’";
					} else {
						simple_text += str_text[i];
					}
				}
			}

			corpus_ = Corpus(simple_text);
			deck_ = Deck(openFileResult.getName(), getTranslations());
		} else if (fileExtension == "JSON") {
			deck_ = Deck(openFileResult.getPath());
		}
	}

}

std::vector<std::pair<std::string, std::string>> ofApp::getTranslations() {
	std::vector<std::pair<std::string, std::string>> word_pairs;
	std::vector<std::string> words = corpus_.GetMostCommonWords();

	for (std::string word : words) {
		std::string unicode_prompt = ConvertStringToUnicodeString(word) + ":";
		std::string translation = ofSystemTextBoxDialog(unicode_prompt);
		std::pair<std::string, std::string> word_pair(word, translation);
		word_pairs.push_back(word_pair);
	}

	return word_pairs;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

// Modified from https://stackoverflow.com/a/44777607
std::string ofApp::ConvertStringToUnicodeString(const std::string& str) {
	if (str.empty()) {
		return std::string();
	}

	int num_chars = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, str.c_str(), str.length(), NULL, 0);
	std::wstring wstrTo;

	if (num_chars) {
		wstrTo.resize(num_chars);
		if (MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, str.c_str(), str.length(), &wstrTo[0], num_chars)) {
			std::string return_str = "";

			for (unsigned int i = 0; i < wstrTo.size(); i++) {
				ofUTF8Append(return_str, wstrTo[i]);
			}

			return return_str;
		}
	}

	return std::string();
}

bool ofApp::isDeckFinished() {
	for (auto it = correct_responses_.begin(); it != correct_responses_.end(); it++) {
		if (it->second < 2) {
			return false;
		}
	}

	for (auto it = correct_responses_.begin(); it != correct_responses_.end(); it++) {
		it->second = 0;
	}

	return true;
}