#pragma once

#include "ofMain.h"
#include "Corpus.h"
#include "Deck.h"

#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <codecvt>



class ofApp : public ofBaseApp{

	private:
		std::string ConvertStringToUnicodeString(const std::string &str);

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void processOpenFileSelection(ofFileDialogResult openFileResult);
		std::vector<std::pair<std::string, std::string>> getTranslations();
		bool isDeckFinished();
		
		Corpus corpus_;
		Deck deck_;
		Card current_card_;
		std::map<std::string, int> correct_responses_;

		ofTrueTypeFont verdana_small_;
		ofTrueTypeFont verdana_medium_;
		ofTrueTypeFont verdana_big_;

		ofSoundPlayer correct_sound_;
		ofSoundPlayer incorrect_sound_;

		ofImage logo_;

		bool main_menu_, flashcard_mode_, front_side_, back_side_;
};
