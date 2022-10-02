#pragma once
#include "Room.hpp"

class Intro_0 : public Room {
private:
	sf::Sprite sprite_background;

	sf::Text text_narrator;
	AnimatedString animatedString;
	int textWidth;

	sf::Clock pauseClock;
	bool isBackgroundFadingIn = true;

	//-------------------------------------------------------------

	void updateStringBreaks();

public:
	void initialize();
	void update();
	void draw();

	std::string getName();
};