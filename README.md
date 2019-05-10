# Glossa

## Motivation
This project was made for helping L2 learners easily create specific flashcard decks for a given source in written form, whether it be an article or subtitles of a movie.

## How to use
When running the app, users may either select a text file or load a previously saved deck. If loading a new text file, users will be prompted to fill out translations for the top 95% most common words from the text, entering nothing if users would rather exclude that word from study. Upon entering flashcard mode, users will be prompted with terms in the target language and guess at their meanings. After pressing the spacebar to reveal the answer, users will select whether their guess was Incorrect (1) or Correct (2). Users must get a word correct twice consecutively to remove it from the deck. Once all cards are removed, the deck will be reloaded and the users will be taken back to the main menu. Users may also save this deck for future study, which will be stored in the bin/data folder. Note that *Glossa* is only intended to work with languages with a Latin-based writing system whose words delimited by spaces.

Extras (such as sounds and images) are stored in the bin/data/extras folder, and an example deck is included in bin/data. The required tools are described down below.

## Tools
[openFrameworks] was the main toolkit used for app development. Some libraries used from this include ofTrueTypeFont, ofSoundPlayer, ofImage, ofUtils, and ofSystemUtils.
The only other outside source used (and required to use this app) was the addon [ofxJSON], which allowed for simple storage of flashcard data.

## Tests
![](https://img.shields.io/badge/tests-passing-success.svg)  \
Tests were done on the Corpus and Deck classes, which account for most of the management of language data, such as reformatting, frequency tracking and sorting, and saving and loading from a file.

[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)

   [openFrameworks]: <https://openframeworks.cc/>
   [ofxJSON]: <https://github.com/jeffcrouse/ofxJSON>